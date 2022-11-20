/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:48:29 by smia              #+#    #+#             */
/*   Updated: 2022/11/20 15:39:36 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

int main()
{
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    ft::vector<int> vec2(vec.begin(), vec.end());
    ft::vector<int>::iterator it = vec2.begin();
    while (it++ != vec2.end())
        std::cout << *it;
   
}