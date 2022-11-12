/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:32:08 by smia              #+#    #+#             */
/*   Updated: 2022/11/08 14:51:09 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>


namespace ft
{
  // &&&&&&&&&&&&&&&&&&&&&&& iterator
  template <class Category, class T, class Distance = ptrdiff_t,
            class Pointer = T*, class Reference = T&>
    class iterator
    {
      public:
          typedef T         value_type;
          typedef Distance  difference_type;
          typedef Pointer   pointer;
          typedef Reference reference;
          typedef Category  iterator_category;
    };

    // &&&&&&&&&&&&&&&&&&&&&&& iterator traits

    template <class T>
    class iterator_traits
    {
      public:
        			typedef typename Iterator::difference_type		difference_type;
			        typedef typename Iterator::value_type			value_type;
			        typedef typename Iterator::pointer				pointer;
			        typedef typename Iterator::reference			reference;
			        typedef typename Iterator::iterator_category	iterator_category;  
    }

    template <class T>
    class iterator_traits<T *>
    {
      public:
        		typedef std::ptrdiff_t					diffrence_type;
            typedef T								value_type;
            typedef T*								pointer;
            typedef T&								reference;
            typedef std::random_access_iterator_tag	    iterator_category;
    }

    template <class T>
    class iterator_traits<const T *>
    {
      public:
        		typedef std::ptrdiff_t					diffrence_type;
            typedef T								value_type;
            typedef const T*								pointer;
            typedef const T&								reference;
            typedef std::random_access_iterator_tag	    iterator_category;
    }

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
template <class Iterator>  reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)

}





  #endif