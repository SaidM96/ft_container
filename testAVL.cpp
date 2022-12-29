/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testAVL.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 00:01:55 by smia              #+#    #+#             */
/*   Updated: 2022/12/27 19:27:19 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "iterator.hpp"
#include "AvlTree.hpp"
int main()
{

    ft::AvlTree<int> b;
    ft::AvlTree<int> tree;
    std::string str("");

        tree.insert(63);
        tree.insert(9);
        tree.insert(19);
        tree.insert(27);
        tree.insert(18);
        tree.insert(108);
        tree.insert(99);
        tree.insert(81);
        tree.printTree(tree.get_root());
        b = tree;

    
    // if (tree.search(63))
    //     puts("63 found");
    // else
    //     puts("63 not found");
    // if (tree.search(9))
    //     puts("9 found"); 
    // else
    //     puts("9 not found");    
    // if (tree.search(19))
    //     puts("19 found");  
    // else
    //     puts("19 not found");
    //  if (tree.search(27))
    //     puts("27 found");  
    // else
    //     puts("27 not found");
    // if (tree.search(18)) 
    //     puts("18 found");
    // else
    //     puts("18 not found");  
    // if (tree.search(108))
    //     puts("108 found"); 
    // else
    //     puts("108 not found");  
    // if (tree.search(99))
    //     puts("99 found");  
    // else
    //     puts("99 not found");  
    // if (tree.search(81))
    //     puts("81 found");
    // else
    //     puts("81 not found");  
    // tree.printTree(tree.get_root(), str, true);


    // b.Clear();
    b.printTree(b.get_root(), str, true);


}

		// Node<T, Alloc>* successor(const T& var) const {
		// 	Node<T, Alloc>*	node = search(root, var);
		// 	if (node == NULL)
		// 		return NULL;
		// 	if (node->right)
		// 		return minNode(node->right);
		// 	Node<T, Alloc>*	succ = node->parent;
		// 	while (succ && succ->left != node) {
		// 		node = succ;
		// 		succ = node->parent;
		// 	}
		// 	return succ;
		// }
		// Node<T, Alloc>* predecessor(const T& var) const {
		// 	Node<T, Alloc>*	node = search(root, var);
		// 	if (node == NULL)
		// 		return NULL;
		// 	if (node->left)
		// 		return maxNode(node->left);
		// 	Node<T, Alloc>*	succ = node->parent;
		// 	while (succ && succ->right != node) {
		// 		node = succ;
		// 		succ = node->parent;
		// 	}
		// 	return succ;
		// }