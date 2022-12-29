#include "map.hpp"
#include <iostream>

int main ()
{
  ft::map<int , char> t;
  int i = 0;

  while(i < 10000)
  {
    t.insert(ft::make_pair(i, 's'));
    i++;
  }
  ft::map<int , char>::iterator it = t.begin();
  while(it != t.end())
  {
    std::cout << "key: " << (*it).first << "value: " << std::endl;
    it++;
  }

}