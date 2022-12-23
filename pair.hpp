/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:42:12 by smia              #+#    #+#             */
/*   Updated: 2022/12/21 23:00:01 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {
	template <class T1, class T2> struct pair {
		T1	first;
		T2	second;

		typedef T1	first_type;
		typedef T2	second_type;

		pair() : first(first_type()), second(second_type()) {}
		template<class U, class V> pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
		pair (const first_type& a, const second_type& b) : first(a) , second(b) {}
		pair& operator= (const pair& pr) {first = pr.first; second = pr.second; return *this;}
	};
	template< class T1, class T2 > ft::pair<T1, T2> make_pair( T1 t, T2 u ) {
		return ft::pair<T1 , T2>(t, u);
	}
	template <class T1, class T2> bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}
	template <class T1, class T2> bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return !(lhs == rhs);
	}
	template <class T1, class T2> bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
	}
	template <class T1, class T2> bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return !(rhs < lhs);
	}
	template <class T1, class T2> bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return rhs < lhs;
	}
	template <class T1, class T2> bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return !(lhs < rhs);
	}
}

// namespace ft{
// // pair , make Pair
// template<class T1, class T2> 
// struct pair
// {
//     T1 first;
//     T2 secound;

//     typedef T1 first_type;
//     typedef T2 secound_type;
//     pair(){}
//     pair (const first_type& a, const secound_type& b){first = a; secound = b;}
//     template<class U, class V> pair (const pair<U,V>& pr){*this = pr}
//     pair& operator=( const pair& other ){this->first = other.first; this->secound = other.secound; return *this}
    
// };
// template< class T1, class T2 > 
// ft::pair<T1, T2> make_pair( T1 t, T2 u )
// {
//     pair<T1, T2> p(t, u);
//     return p;
// }
// template< class T1, class T2 >
// bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return (lhs.first == rhs.first && lhs.secound == rhs.secound );}
// template< class T1, class T2 >
// bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return (lhs.first != rhs.first || lhs.secound != rhs.secound );}

// template< class T1, class T2 >
// bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return (lhs.first < rhs.first && lhs.secound < rhs.secound ) ;}
// template< class T1, class T2 >
// bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return (lhs.first > rhs.first && lhs.secound > rhs.secound );}
// template< class T1, class T2 >
// bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return !(lhs < rhs);}
// template< class T1, class T2 >
// bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return !(lhs > rhs);}


// }
