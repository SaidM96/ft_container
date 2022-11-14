/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:42:12 by smia              #+#    #+#             */
/*   Updated: 2022/11/12 23:50:45 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft{
// pair , make Pair
template<class T1, class T2> 
struct pair
{
    T1 first;
    T2 secound;

    typedef T1 first_type;
    typedef T2 secound_type;
    pair(){}
    pair (const first_type& a, const secound_type& b){first = a; secound = b;}
    template<class U, class V> pair (const pair<U,V>& pr){*this = pr}
    pair& operator=( const pair& other ){this->first = other.first; this->secound = other.secound; return *this}
    
};
template< class T1, class T2 > 
ft::pair<T1, T2> make_pair( T1 t, T2 u )
{
    pair<T1, T2> p(t, u);
    return p;
}
template< class T1, class T2 >
bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return (lhs.first == rhs.first && lhs.secound == rhs.secound );}
template< class T1, class T2 >
bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return (lhs.first != rhs.first || lhs.secound != rhs.secound );}

template< class T1, class T2 >
bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return (lhs.first < rhs.first && lhs.secound < rhs.secound ) ;}
template< class T1, class T2 >
bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return (lhs.first > rhs.first && lhs.secound > rhs.secound );}
template< class T1, class T2 >
bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return !(lhs < rhs);}
template< class T1, class T2 >
bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return !(lhs > rhs);}

// enable if
template<bool B, class T = void> struct enable_if {};
template<class T> struct enable_if<true, T> { typedef T type; };


}
