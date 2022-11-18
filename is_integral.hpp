/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 00:48:24 by smia              #+#    #+#             */
/*   Updated: 2022/11/17 21:50:43 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

namespace ft
{

template <class T, T v>struct integral_constant 
{
    static const T          value = v;
    typedef T                               value_type;
    typedef integral_constant<T,v>          type;
    typedef integral_constant<bool, true>   true_type;
    typedef integral_constant<bool, false>  false_type;
    operator value_type(){return value;}
};

template <class T> struct is_integral : integral_constant<bool, false>{};
template <> struct is_integral<bool> : integral_constant<bool, true>{};
template <> struct is_integral<char> : integral_constant<bool, true>{};
template <> struct is_integral<wchar_t> : integral_constant<bool, true>{};
template <> struct is_integral<signed char> : integral_constant<bool, true>{};
template <> struct is_integral<short int> : integral_constant<bool, true>{};
template <> struct is_integral<int> : integral_constant<bool, true>{};
template <> struct is_integral<long int> : integral_constant<bool, true>{};
template <> struct is_integral<long long int> : integral_constant<bool, true>{};
template <> struct is_integral<unsigned char> : integral_constant<bool, true>{};
template <> struct is_integral<unsigned short int> : integral_constant<bool, true>{};
template <> struct is_integral<unsigned int> : integral_constant<bool, true>{};
template <> struct is_integral<unsigned long int> : integral_constant<bool, true>{};
template <> struct is_integral<unsigned long long int> : integral_constant<bool, true>{};

template<bool Cond, class T = void> struct enable_if {};
template<class T> struct enable_if<true, T> { typedef T type; };


};
