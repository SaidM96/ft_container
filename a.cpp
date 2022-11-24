/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:36:38 by smia              #+#    #+#             */
/*   Updated: 2022/11/24 10:29:49 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

int main()
{
 {
    std::vector<int> x;
    x.push_back(10);
    x.push_back(20);
    std::vector<int>::iterator i1 = x.erase(x.begin());
    ft::vector<int> m;
    m.push_back(10);
    m.push_back(20);
    ft::vector<int>::iterator i2 = m.erase(m.begin());
    assert(x.capacity() == m.capacity());
    assert(x.size() == m.size());
    assert(x[0] == m[0]);
    assert(i1 == x.begin());
    assert(i2 == m.begin());
  }
  {
    std::vector<int> x;
    x.push_back(10);
    x.push_back(20);
    std::vector<int>::iterator i1 = x.erase(x.end() - 1);
    ft::vector<int> m;
    m.push_back(10);
    m.push_back(20);
    ft::vector<int>::iterator i2 = m.erase(m.end() - 1);
    assert(x.capacity() == m.capacity());
    assert(x.size() == m.size());
    assert(x[0] == m[0]);
    assert(i1 == (x.end()));
    assert(i2 == (m.end()));
  }
  {
    std::vector<int> x;
    x.push_back(10);
    x.push_back(20);
    x.push_back(30);
    x.push_back(40);
    std::vector<int>::iterator i1 = x.erase(x.begin() + 2);
    ft::vector<int> m;
    m.push_back(10);
    m.push_back(20);
    m.push_back(30);
    m.push_back(40);
    ft::vector<int>::iterator i2 = m.erase(m.begin() + 2);
    assert(x.capacity() == m.capacity());
    assert(x.size() == m.size());
    assert(x[0] == m[0]);
    assert(x[1] == m[1]);
    assert(x[2] == m[2]);
    assert(i1 == (x.begin() + 2));
    assert(i2 == (m.begin() + 2));
    std::cerr << "testing erase() :: pass\n";
  }
  {
    std::vector<int> x;
    x.push_back(10);
    x.push_back(20);
    std::vector<int>::iterator i1 = x.erase(x.begin(), x.end());
    ft::vector<int> m;
    m.push_back(10);
    m.push_back(20);
    ft::vector<int>::iterator i2 = m.erase(m.begin(), m.end());
    assert(x.capacity() == m.capacity());
    assert(x.size() == m.size());
    assert(i1 == x.end());
    assert(i2 == m.end());
  }
  {
    std::vector<int> x;
    x.push_back(10);
    x.push_back(20);
    std::vector<int>::iterator i1 = x.erase(x.end() - 1, x.end());
    ft::vector<int> m;
    m.push_back(10);
    m.push_back(20);
    ft::vector<int>::iterator i2 = m.erase(m.end() - 1, m.end());
    assert(x.capacity() == m.capacity());
    assert(x.size() == m.size());
    assert(x[0] == m[0]);
    assert(i1 == x.end());
    assert(i2 == m.end());
  }
  {
    std::vector<int> x;
    x.push_back(10);
    x.push_back(20);
    x.push_back(30);
    x.push_back(40);
    std::vector<int>::iterator i1 = x.erase(x.begin() + 1, x.begin() + 2);
    ft::vector<int> m;
    m.push_back(10);
    m.push_back(20);
    m.push_back(30);
    m.push_back(40);
    ft::vector<int>::iterator i2 = m.erase(m.begin() + 1, m.begin() + 2);
    assert(x.capacity() == m.capacity());
    assert(x.size() == m.size());
    assert(x[0] == m[0]);
    assert(x[1] == m[1]);
    assert(i1 == x.begin() + 1);
    assert(i2 == m.begin() + 1);
    std::cerr << "testing range erase() :: pass\n";
  }
}