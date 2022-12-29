#include "map.hpp"

int main()
{
    ft::map<int , char> tree;
    tree.insert(ft::make_pair(1,'S'));
    tree.insert(ft::make_pair(2,'a'));
    tree.insert(ft::make_pair(3,'i'));
    tree.insert(ft::make_pair(4,'d'));
    tree.insert(ft::make_pair(5,'q'));
    tree.insert(ft::make_pair(6,'M'));
    tree.insert(ft::make_pair(7,'q'));
    tree.insert(ft::make_pair(8,'w'));
    tree[0];
    // tree.print();
    // std::cout << "add " << std::endl;
    tree.insert(ft::make_pair(11,'S'));
    tree.insert(ft::make_pair(12,'a'));
    tree.insert(ft::make_pair(13,'i'));
    tree.insert(ft::make_pair(14,'d'));
    tree.insert(ft::make_pair(15,'q'));
    tree.insert(ft::make_pair(16,'M'));
    tree.insert(ft::make_pair(17,'q'));
    tree.insert(ft::make_pair(18,'w'));
    //  ft::map<int , char> z;
    ft::map<int , char>::iterator it = tree.begin();
    for (size_t i = 0; i < 3; i++)
       it++;

    ft::map<int, char>  a;
    a.swap(tree);
    // tree.erase(it, tree.end());
// std::cout << "erase : " << std::endl;
    // tree.erase(0);
    // tree.erase(3);
    // tree.erase(2);
    // tree.erase(3);
    // tree.erase(4);
    // tree.erase(5);
    // tree.erase(6);
    // tree.erase(7);
    // tree.erase(8);
    a.print();

    // try
    // {
    //    std::cout << tree.at(8) << "\n";
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
    

    // tree.print();

    // ft::map<int , char>::iterator it = tree.begin();
    
    // while(it != tree.end())
    // {
    //     std::cout <<" key: " << it->first << " value: " << it->second << std::endl;
    //     ++it;
    // }
}
