#include "map.hpp"

int main()
{
    ft::map<int , char> tree;


    tree.insert(ft::make_pair(13,'S'));
    tree.insert(ft::make_pair(14,'a'));
    tree.insert(ft::make_pair(16,'i'));
    tree.insert(ft::make_pair(15,'d'));
    tree.insert(ft::make_pair(10,' '));
    tree.insert(ft::make_pair(12,'M'));
    tree.insert(ft::make_pair(11,'i'));
    tree.insert(ft::make_pair(9,'a'));

    ft::map<int , char>::iterator it = tree.begin();
    std::cout << *it;
}
