/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testAVL.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 00:01:55 by smia              #+#    #+#             */
/*   Updated: 2022/12/20 09:32:10 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AvlTree.hpp"

int main()
{
    AvlTree<int> tree;
    
    tree.insert(63);
    tree.insert(9);
    tree.insert(19);
    tree.insert(27);
    tree.insert(18);
    tree.insert(108);
    tree.insert(99);
    tree.insert(81);
    std::string str("");
    tree.printTree(tree.get_root(), str, true);
    tree.Delete(63);
    tree.Delete(9);
    tree.Delete(19);
    tree.Delete(27);
    tree.Delete(18);
    tree.Delete(108);
    tree.Delete(99);
    // tree.Delete(81);
    puts("aw");
    tree.printTree(tree.get_root(), str, true);

}