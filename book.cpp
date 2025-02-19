#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

Book::~Book(){
  
}

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author):
Product(category,name,price,qty)
{
  isbn_ = isbn;
  author_ = author;
}

std::set<std::string> Book::keywords() const{
  std::set<std::string> mykw1 = parseStringToWords(getName());
  std::set<std::string> mykw2 = parseStringToWords(author_);
  std::set<std::string> mykw = setUnion(mykw1, mykw2);
  mykw.insert(isbn_);
  return mykw;
}

std::string Book::displayString() const{
  std::string mystring;
  mystring.append(getName());
  mystring += '\n';
  mystring += "Author: ";
  mystring.append(author_); 
  mystring += " ISBN: ";
  mystring.append(isbn_);
  mystring += '\n';
  mystring.append(std::to_string(getPrice()));
  mystring += " ";
  mystring.append(std::to_string(getQty()));
  mystring += " left.";
  return mystring;   
}

void Book::dump(std::ostream& os) const{
  os << "book" << std::endl; 
  os << getName() << std::endl; 
  os << getPrice() << std::endl; 
  os << getQty() << std::endl; 
  os << isbn_ << std::endl; 
  os << author_ << std::endl; 
}