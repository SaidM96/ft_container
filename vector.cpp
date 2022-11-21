/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:48:29 by smia              #+#    #+#             */
/*   Updated: 2022/11/21 18:24:32 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

int main()
{
    ft::vector<int> vec1;
    vec1.push_back(9);
    vec1.push_back(9);
    vec1.push_back(9);
    vec1.push_back(9);
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    ft::vector<int> vec2;
    vec2.push_back(10);
    vec2.push_back(20);
    vec2.push_back(30);
    vec2.push_back(40);

    // vec.insert(vec.begin() + 2,vec1.begin(), vec1.end());
    // vec2.insert(vec2.begin() + 2,vec1.begin(), vec1.end());
    // vec.insert(vec.begin() + 2, 5);
    vec2.insert(vec2.begin() + 2, 5);
    // std::vector<int>::iterator it = vec.begin();
    // ft::vector<int>::iterator it1 = vec2.begin();
    
    // while(it != vec.end())
    // {
    //     std::cout << *it;
    //     it++;
    // }
    // while(it1 != vec2.end())
    // {
    //     std::cout << *it1;
    //     it1++;
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;
    
}