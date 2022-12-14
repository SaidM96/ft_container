/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:32:08 by smia              #+#    #+#             */
/*   Updated: 2022/12/30 05:48:29 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <iostream>
#include "is_integral.hpp"
#include "AvlTree.hpp"
namespace ft
{
  //&&&&&&&&&&&&&&&&&&&&&&& iterator traits

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
        typedef std::ptrdiff_t					          diffrence_type;
        typedef T								                  value_type;
        typedef T*								                pointer;
        typedef T&								                reference;
        typedef std::random_access_iterator_tag	  iterator_category;
    };
    template <class T> class iterator_traits<const T *> {
      public:
        typedef std::ptrdiff_t			        diffrence_type;
        typedef T								            value_type;
        typedef const T*						        pointer;
        typedef const T&						  reference;
        typedef std::random_access_iterator_tag	iterator_category;
    };

    // &&&&&&&&&&&&&&&&&&&&&&& reverse_iterator
    template <class Iterator>
    class reverse_iterator
    {
      protected:
        Iterator current;
      public:
          typedef Iterator							                                    iterator_type;
          typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
          typedef typename ft::iterator_traits<Iterator>::value_type			  value_type;
          typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
          typedef typename ft::iterator_traits<Iterator>::pointer				    pointer;
          typedef typename ft::iterator_traits<Iterator>::reference			    reference;
          
          reverse_iterator(){current = NULL;}
          explicit reverse_iterator(iterator_type it){current = it;}
          template <class Iter>  reverse_iterator ( reverse_iterator<Iter> const & cp){current = cp.base();}
          ~reverse_iterator(){}
          template<class U> reverse_iterator<U>& operator=(reverse_iterator<U> const & other) {current = other.base(); return *this;}
          iterator_type base() const {return current;}
          reference operator*() const {iterator_type tmp = current; return *--tmp;}  // Returns a reference or pointer to the element previous to current.
          pointer operator->() const { return &(operator*());}
          reference operator[] (difference_type n) const {return (base()[-n - 1]);}
          reverse_iterator& operator++() {--current; return (*this);}
          reverse_iterator& operator--() {++current; return (*this);}
          reverse_iterator  operator++(int) {iterator_type tmp = current; current--; return reverse_iterator(tmp);}
          reverse_iterator  operator--(int) {iterator_type tmp = current; current++; return reverse_iterator(tmp);}
          reverse_iterator operator+ (difference_type n) const {
                return reverse_iterator(current - n);
          }
          reverse_iterator operator- (difference_type n) const {
            return reverse_iterator(current + n);
          }
          reverse_iterator& operator+= (difference_type n) {current -= n; return *this;}
          reverse_iterator& operator-= (difference_type n) {current += n; return *this;}
    };

template <class T1, class T2>  bool operator== (const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs){
  return (lhs.base() == rhs.base());
}
template <class T1, class T2>  bool operator!= (const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs){
  return (lhs.base() != rhs.base());
}
template <class T1, class T2>  bool operator< (const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs){
  return (lhs.base() > rhs.base());
}
template <class T1, class T2>  bool operator> (const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs){
  return (lhs.base() < rhs.base());
}
template <class T1, class T2>  bool operator<= (const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs){
  return (lhs.base() >= rhs.base());
}
template <class T1, class T2>  bool operator>= ( reverse_iterator<T1> const & lhs,  reverse_iterator<T2> const & rhs){
  return (lhs.base() <= rhs.base());
}

template< class Iter > reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it )
{
  return reverse_iterator<Iter>(it.base() - n);
}

template< class Iterator1, class Iterator2 > typename reverse_iterator<Iterator1>::difference_type operator-( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
{
  return (rhs.base() - lhs.base());
}

// random_access_iterator
//
      // 
template <typename T>
class random_access_iterator 
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
        random_access_iterator(pointer ptr) : _ptr(ptr) {}
        random_access_iterator( const random_access_iterator& cp) : _ptr(cp._ptr){}
        ~random_access_iterator(){}
        random_access_iterator& operator=( const random_access_iterator& other) {this->_ptr = other.base(); return *this;}
        pointer base(void) const {return _ptr;}
        bool operator==( const random_access_iterator& other){return(this->_ptr == other._ptr);}
        bool operator!=( const random_access_iterator& other){{return(this->_ptr != other._ptr);}}
        bool operator<( const random_access_iterator& other){return(this->_ptr < other._ptr);}
        bool operator>( const random_access_iterator& other){{return(this->_ptr > other._ptr);}}
        bool operator<=( const random_access_iterator& other){return(this->_ptr <= other._ptr);}
        bool operator>=( const random_access_iterator& other){{return(this->_ptr >= other._ptr);}}
        reference operator*()const {return (*_ptr);}
        pointer operator->(void) const {return (_ptr); }
        //user defined conversion function for converting to const it
			  operator random_access_iterator< T const>() const{
				return random_access_iterator< T const>(_ptr);
			}
        random_access_iterator &operator++(){_ptr++;return (*this);}
        random_access_iterator &operator--(){_ptr--;return (*this);}
        random_access_iterator operator++(int){random_access_iterator tmp;tmp._ptr = _ptr;_ptr++;return (tmp); }
        random_access_iterator operator--(int){random_access_iterator tmp;tmp._ptr = _ptr;_ptr--;return (tmp);}
        random_access_iterator  operator+(difference_type n) const{return (random_access_iterator(_ptr + n));}
        random_access_iterator  operator-(difference_type n)const{return (random_access_iterator(_ptr - n));}
        random_access_iterator&  operator+=(difference_type n){_ptr += n; return (*this);}
        random_access_iterator&  operator-=(difference_type n){_ptr -= n; return (*this);}
        reference  operator[](difference_type n) const {return (base()[n]);}
};

	template <class Iter1, class Iter2>  bool operator==(const random_access_iterator<Iter1> &lhs, const random_access_iterator<Iter2> &rhs) 
  {
		return (lhs.base() == rhs.base());
	}
	
  
  template <class Iter1, class Iter2>  bool operator!=(const random_access_iterator<Iter1> &lhs, const random_access_iterator<Iter2> &rhs) {
		return (lhs.base() != rhs.base());
	}
  template <class Iter1, class Iter2>  bool operator<(const random_access_iterator<Iter1> &lhs, const random_access_iterator<Iter2> &rhs) {
		return (lhs.base() < rhs.base());
	}
  
	template <class Iter1, class Iter2>  bool operator<=(const random_access_iterator<Iter1> &lhs, const random_access_iterator<Iter2> &rhs) {
		return (lhs.base() <= rhs.base());
	}
  
	template <class Iter1, class Iter2>  bool operator>(const random_access_iterator<Iter1> &lhs, const random_access_iterator<Iter2> &rhs) {
		return (lhs.base() > rhs.base());
  }

  template <class Iter1, class Iter2>  bool operator>=(const random_access_iterator<Iter1> &lhs, const random_access_iterator<Iter2> &rhs) {
		return (lhs.base() >= rhs.base());
	}
  
	template <class Iterator> random_access_iterator<Iterator> operator+( typename random_access_iterator<Iterator>::difference_type n, const random_access_iterator<Iterator> &it) {
		return (random_access_iterator<Iterator>(it.base() + n));
	}
	template <class Iter1, class Iter2> typename random_access_iterator<Iter1>::difference_type operator-( const random_access_iterator<Iter1> &lhs, const random_access_iterator<Iter2> &rhs) {
		return (lhs.base() - rhs.base());
	}
  
// std::disctance
template< class It >
typename iterator_traits<It>::difference_type distance( It first, It last )
{
	typename iterator_traits<It>::difference_type dis = 0;
	while(first != last)
  {
    first++;
    dis++;
  }
  return dis;
}

//  Bidirectional iterator

template <typename T, class cmp, class alloc>
class bidirectional_iterator
{

    public:
        typedef const AvlTree<T, cmp, alloc>*     tree;
        typedef T                                 value_type;  
        typedef std::bidirectional_iterator_tag   iterator_category;
        typedef T*											          pointer;
        typedef T&											          reference;
        typedef std::ptrdiff_t								    difference_type;
        typedef const T*						              const_pointer;
        typedef const T&						              const_reference;

        bidirectional_iterator(): _data(NULL), _tree(NULL)
        {
        }
        bidirectional_iterator(pointer ptr, tree tr = NULL) : _data(ptr), _tree(tr)
        {}
        bidirectional_iterator(const bidirectional_iterator& cp) : _data(cp._data), _tree(cp._tree) {}
        bidirectional_iterator& operator=(const bidirectional_iterator& cp)
        {
          _data = cp._data;
          _tree = cp._tree;
          return (*this);
        }
        ~bidirectional_iterator(){}

        bool operator==(const bidirectional_iterator& other) const
        {
            return (_data == other._data);
        }
        bool operator!=(const bidirectional_iterator& other) const
        {
            return (_data != other._data);
        }

        reference operator*() const
        {
          return(*_data);
        }

        pointer operator->() const
        {
          return (&(operator*()));
        }

        bidirectional_iterator& operator++(void)
        {
            node<T, alloc>* Node = _tree->helper_search(_tree->get_root(), *_data);
            if (Node)
            {
              node<T, alloc>* ptr = _tree->inorder_successor(*_data);
              if (ptr != NULL)
              {
                _data = ptr->_value;
              }
              else
              {
                _data = NULL;
              }
            }      
          return *this;
        }

        bidirectional_iterator& operator--(void)
        {
          if (_data == NULL)
            _data = _tree->max_node(_tree->get_root())->_value;
          else
          {
              node<value_type, alloc>* ptr = _tree->inorder_predecessor(*_data);
             _data = ptr->_value;
          }
          return *this;
        }

        bidirectional_iterator operator++(int)
        {
          bidirectional_iterator tmp = *this;
          ++(*this);
          return tmp;
        }

        bidirectional_iterator operator--(int)
        {
          bidirectional_iterator tmp = *this;
          --(*this);
          return tmp;
        }
      	operator bidirectional_iterator<const T, cmp, alloc> () const 
        {
				    return bidirectional_iterator<const T, cmp, alloc>(_data, reinterpret_cast<const AvlTree<const value_type, cmp, alloc>*>(_tree));
			  }
    private:
      T*                      _data;
      tree                    _tree;
        
        
};

};
