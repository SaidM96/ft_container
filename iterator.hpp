/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:32:08 by smia              #+#    #+#             */
/*   Updated: 2022/11/19 05:40:21 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include "is_integral.hpp"

namespace ft
{
  // Iterator tags
  typedef std::input_iterator_tag				input_iterator_tag;
	typedef std::random_access_iterator_tag		random_access_iterator_tag;
  
  // Iterator
  template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator {
		public:
			typedef Category		iterator_category;
			typedef T				value_type;
			typedef Distance		difference_type;
			typedef Pointer			pointer;
			typedef Reference		reference;
	};
  // &&&&&&&&&&&&&&&&&&&&&&& iterator traits

    template <class Iterator> class iterator_traits {
      public:
        typedef typename Iterator::difference_type		difference_type;
        typedef typename Iterator::value_type			value_type;
        typedef typename Iterator::pointer				pointer;
        typedef typename Iterator::reference			reference;
        typedef typename Iterator::iterator_category	iterator_category;
    };
    template <class T> class iterator_traits<T *> {
      public:
        typedef std::ptrdiff_t					diffrence_type;
        typedef T								value_type;
        typedef T*								pointer;
        typedef T&								reference;
        typedef std::random_access_iterator_tag	iterator_category;
    };
    template <class T> class iterator_traits<const T *> {
      public:
        typedef std::ptrdiff_t			diffrence_type;
        typedef T								    value_type;
        typedef const T*						pointer;
        typedef const T&						reference;
        typedef ft::random_access_iterator_tag	iterator_category;
    };

    // &&&&&&&&&&&&&&&&&&&&&&& reverse_iterator
    template <class Iterator>
    class reverse_iterator
    {
      protected:
        Iterator current;
      public:
          typedef Iterator													                        iterator_type;
          typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
          typedef typename ft::iterator_traits<Iterator>::value_type			  value_type;
          typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
          typedef typename ft::iterator_traits<Iterator>::pointer				    pointer;
          typedef typename ft::iterator_traits<Iterator>::reference			    reference;
          reverse_iterator(){}
          explicit reverse_iterator( iterator_type x ){current = x;}
          template <class Iter>  reverse_iterator (const reverse_iterator<Iter>& rev_it){*this = rev_it;}
          iterator_type base() const {return current;}
          reference operator*() const {iterator_type tmp = current; return *--tmp;}  // ???
          reverse_iterator operator+ (difference_type n) const {return reverse_iterator(current - n);}
          reverse_iterator operator- (difference_type n) const {return reverse_iterator(current + n);}
          reverse_iterator& operator++() {--current; return (*this);}
          reverse_iterator  operator++(int) {iterator_type tmp = current--; return tmp;}
          reverse_iterator& operator--() {++current; return (*this);}
          reverse_iterator  operator--(int) {iterator_type tmp = current++; return tmp;}
          reverse_iterator& operator+= (difference_type n) {current -= n; return *this;}
          reverse_iterator& operator-= (difference_type n) {current += n; return *this;}
          pointer operator->() const {return &(operator*());}
          reference operator[] (difference_type n) const {return (base()[n -1]);}
    };

template <class Iterator>  bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
  return (lhs.base() == rhs.base());
}
template <class Iterator>  bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
  return (lhs.base() != rhs.base());
}
template <class Iterator>  bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
  return (lhs.base() < rhs.base());
}
template <class Iterator>  bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
  return (lhs.base() <= rhs.base());
}
template <class Iterator>  bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
  return (lhs.base() > rhs.base());
}
template <class Iterator>  bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
  return (lhs.base() >= rhs.base());
}
template <class Iterator>  reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it){return (rev_it - n);}
template <class Iterator>  reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it){return (rev_it + n);}

// random_access_iterator

template <typename T>
class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
{
    protected:
        T*  _ptr;
    public:
        typedef T											                value_type;
			  typedef std::random_access_iterator_tag				iterator_category;
			  typedef T*											              pointer;
			  typedef T&											              reference;
			  typedef std::ptrdiff_t								        difference_type;
        
        random_access_iterator(){ _ptr = NULL;}                           
        random_access_iterator(T* ptr){_ptr = ptr;}
        random_access_iterator( const random_access_iterator& cp) {*this = cp;}
        ~random_access_iterator(){}
        random_access_iterator& operator=( const random_access_iterator& other) {this->_ptr = other._ptr; return *this;}
        bool operator==( const random_access_iterator& other){return(this->_ptr == other._ptr);}
        bool operator!=( const random_access_iterator& other){{return(this->_ptr != other._ptr);}}
        reference operator*()const {return (*_ptr);}
        pointer operator->(void){return (_ptr); }
        random_access_iterator operator++(void){_ptr++;return (*this); }
        random_access_iterator operator--(void){_ptr--;return (*this); }
        random_access_iterator operator++(int){random_access_iterator tmp;tmp._ptr = _ptr;_ptr++;return (tmp); }
        random_access_iterator operator--(int){random_access_iterator tmp;tmp._ptr = _ptr;_ptr--;return (tmp);}
        random_access_iterator  operator+(int n){return (this->_ptr + n);}
        random_access_iterator  operator-(int n){return (this->_ptr - n);}
        random_access_iterator  operator+(const random_access_iterator other){return (this->_ptr + other._ptr); }
        random_access_iterator  operator-(const random_access_iterator other){return (this->_ptr - other._ptr);}
        random_access_iterator  operator+=(int n){return (this->_ptr + n);}
        random_access_iterator  operator-=(int n){return (this->_ptr - n);}
        reference  operator[](unsigned int n){return (_ptr[n]);}
};


// std::disctance
template< class InputIt >
typename iterator_traits<InputIt>::difference_type distance( InputIt first, InputIt last )
{
	typename iterator_traits<InputIt>::difference_type dis = 0;
	while(first++ != last)
		dis++;
  return dis;
}

//  Bidirectional iterator

}

  #endif 