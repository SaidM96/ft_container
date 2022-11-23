/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:36:38 by smia              #+#    #+#             */
/*   Updated: 2022/11/23 20:33:46 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

int main()
{
    ft::vector<int> v;
    v.assign(10, 3);
    v.erase(v.begin(), v.begin() + 3);
    
    
}