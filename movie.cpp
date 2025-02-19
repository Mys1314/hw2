#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

Movie::~Movie(){

}

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating):
Product(category,name,price,qty)
{
  genre_ = genre;
  rating_ = rating;
}

std::set<std::string> Movie::keywords() const{
  std::set<std::string> mykw = parseStringToWords(getName());
  mykw.insert(convToLower(genre_));
  return mykw;
}

std::string Movie::displayString() const{
  std::string mystring;
  mystring.append(getName());
  mystring += '\n';
  mystring += "Genre: ";
  mystring.append(genre_); 
  mystring += " Rating: ";
  mystring.append(rating_);
  mystring += '\n';
  mystring.append(std::to_string(getPrice()));
  mystring += " ";
  mystring.append(std::to_string(getQty()));
  mystring += " left.";
  return mystring;
}

void Movie::dump(std::ostream& os) const{
  os << "movie" << std::endl; 
  os << getName() << std::endl; 
  os << getPrice() << std::endl; 
  os << getQty() << std::endl; 
  os << genre_ << std::endl; 
  os << rating_ << std::endl; 
}
