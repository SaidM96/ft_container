#include "map.hpp"

int main()
{
    ft::map<int , char> tree;
    tree.insert(ft::make_pair(1,'S'));
    tree.insert(ft::make_pair(2,'a'));
    tree.insert(ft::make_pair(3,'i'));
    tree.insert(ft::make_pair(4,'d'));
    tree.insert(ft::make_pair(5,'q'));
    // tree.insert(ft::make_pair(6,'M'));
    // tree.insert(ft::make_pair(7,'q'));
    // tree.insert(ft::make_pair(8,'w'));

    tree.print();
    // ft::map<int , char>::iterator it = tree.begin();
    // while(it != tree.end())
    // {
    //     std::cout <<" key: " << it->first << " value: " << it->second << std::endl;
    //     ++it;
    // }
}
