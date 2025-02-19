#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

Clothing::~Clothing(){

}

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand):
Product(category,name,price,qty)
{
  size_ = size;
  brand_ = brand;
}

std::set<std::string> Clothing::keywords() const{
  std::set<std::string> mykw1 = parseStringToWords(getName());
  std::set<std::string> mykw2 = parseStringToWords(brand_);
  std::set<std::string> mykw = setUnion(mykw1,mykw2);
  return mykw;
}

std::string Clothing::displayString() const{
  std::string mystring;
  mystring.append(getName());
  mystring += '\n';
  mystring += "Size: ";
  mystring.append(size_); 
  mystring += " Brand: ";
  mystring.append(brand_);
  mystring += '\n';
  mystring.append(std::to_string(getPrice()));
  mystring += " ";
  mystring.append(std::to_string(getQty()));
  mystring += " left.";
  return mystring;
}

void Clothing::dump(std::ostream& os) const{
  os << "clothing" << std::endl; 
  os << getName() << std::endl; 
  os << getPrice() << std::endl; 
  os << getQty() << std::endl; 
  os << size_ << std::endl; 
  os << brand_ << std::endl; 
}