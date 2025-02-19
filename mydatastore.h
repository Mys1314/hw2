#include "datastore.h"
#include "util.h"


class MyDataStore : public DataStore{
public:
  MyDataStore();
  ~MyDataStore();
  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);
  std::vector<User*> get_Users();
private:
  std::vector<Product*> Products_;
  std::vector<User*> Users_;
};