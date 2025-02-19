#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }
    map<string, vector<Product*>> cart;
    map<string, User*> amazon_users;
    vector<User*> a_users = ds.get_Users();
    for(unsigned int i =0; i < a_users.size();i++){
      cart[a_users[i]->getName()] = vector<Product*>();
      amazon_users[a_users[i]->getName()] = a_users[i];
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
            else if (cmd == "ADD"){
                string username;
                int search_hit_number;
                if(!(ss >> username)){
                    cout << "Invalid request" << endl;
                }
                else if (!(ss >> search_hit_number)){
                    cout << "Invalid request" << endl;
                }
                else{
                    map<string, vector<Product*>>::iterator it;
                    it = cart.find(username);
                    if(it == cart.end() || search_hit_number > hits.size() || search_hit_number <= 0){
                        cout << "Invalid request" << endl;
                    }else{
                        it -> second.push_back(hits[search_hit_number - 1]);
                    }
                }
            }
            else if (cmd == "VIEWCART"){
                string username;
                if(!(ss >> username)){
                    cout << "Invalid username" << endl;
                }
                else{
                    map<string, vector<Product*>>::iterator it;
                    it = cart.find(username);
                    if(it == cart.end()){
                        cout << "Invalid username" << endl;
                    }else{
                        for(int i = 0; i < it -> second.size(); i++){
                            cout << "Item " << i+1 <<endl;
                            cout << (it -> second)[i] -> displayString() << endl;
                        }                        
                    }
                }
            }
            else if (cmd == "BUYCART"){
                string username;
                if(!(ss >> username)){
                    cout << "Invalid username" << endl;
                }
                else{
                    map<string, vector<Product*>>::iterator it;
                    map<string, User*>::iterator uit;
                    it = cart.find(username);
                    uit = amazon_users.find(username);
                    if(it == cart.end()){
                        cout << "Invalid username" << endl;
                    }else{
                        for(int i = 0; i < it -> second.size(); i++){
                            if(uit->second->getBalance() >= it->second[i] -> getPrice() && it->second[i] -> getQty() >= 1){
                              it->second[i] -> subtractQty(1);
                              uit->second-> deductAmount(it->second[i] -> getPrice());
                              it->second.erase(it->second.begin() + i);
                              i--;
                            }
                        }                        
                    }
                }
            }


            else {
                cout << "Unknown command" << endl;
            }
        }

    }

    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
