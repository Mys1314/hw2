#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore(){

}
MyDataStore::~MyDataStore(){
  for(int i=0;i<Products_.size();i++){
    delete Products_[i];
  }
  for(int i=0;i<Users_.size();i++){
    delete Users_[i];
  }
}

void MyDataStore::addProduct(Product* p){
  Products_.push_back(p);
}

void MyDataStore::addUser(User* u){
  Users_.push_back(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  std::set<std::string> terms_set;
  for(unsigned int i = 0; i < terms.size(); i++){
    terms_set.insert(terms[i]);
  }
  std::vector<Product*> found_products;
  std::set<std::string> found_words;
  if(type == 0){
    for(unsigned int i = 0; i < Products_.size(); i++){
      std::set<std::string> pkeywords = Products_[i]->keywords();
      found_words = setIntersection(pkeywords, terms_set);
      if(found_words.size() == terms_set.size()){
        found_products.push_back(Products_[i]);
      }
      found_words.clear();
    }
  }else{
    for(unsigned int i = 0; i < Products_.size(); i++){
      std::set<std::string> pkeywords = Products_[i]->keywords();
      found_words = setIntersection(pkeywords, terms_set);
      if(found_words.size() > 0){
        found_products.push_back(Products_[i]);
      }
      found_words.clear();
    }  
  }
  return found_products;  
}

void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>" << std::endl;
  for(unsigned int i = 0; i < Products_.size(); i++){
    Products_[i] -> dump(ofile);
  }
  ofile << "</products>" << std::endl;
  ofile << "<users>" << std::endl;
  for(unsigned int i = 0; i < Users_.size(); i++){
    Users_[i] -> dump(ofile);
  }
  ofile << "</users>" << std::endl;
}

std::vector<User*> MyDataStore::get_Users(){
  return Users_;
}