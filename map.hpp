/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:34:14 by smia              #+#    #+#             */
/*   Updated: 2022/12/23 16:44:32 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"
#include "AvlTree.hpp"
#include "pair.hpp"

namespace ft
{
    template<class Key,class T,class Compare = std::less<Key>,class alloc = std::allocator<std::pair<const Key, T>> > 
    class map
    {
        
      public:
          typedef  Key                                                     Key_type;
          typedef  T                                                       mapped_key;
          typedef  ft::pair< const Key_type, mapped_key>                   value_type;
          typedef  AvlTree<value_type, Compare, alloc>*                    tree;
          typedef  std::size_t                                             size_type;
          typedef  std::ptrdiff_t                                          difference_type;
          typedef  Compare                                                 key_compare;
          typedef  alloc                                                   allocator_type;
          typedef  value_type&                                             reference;
          typedef  const value_type&                                       const_reference;
          typedef  value_type*                                             pointer;
          typedef  const value_type*                                       const_pointer;
          typedef  ft::bidirectional_iterator<T, Compare, alloc>           iterator;
          typedef  ft::bidirectional_iterator<const T, Compare, alloc>     const_iterator
			    typedef  ft::reverse_iterator<iterator>					                 reverse_iterator;
			    typedef  ft::reverse_iterator<const_iterator>			               const_reverse_iterator;

          class value_type  : public std::binary_function<value_type, value_type, bool>
          {
            friend class map;
            protected:
              Compare _cmp;
              value_compare(Compare cmp)
              {
                cmp = cmp;
              }
            public:
              bool          result_type;
              value_type    first;
              value_type    secound;
              bool operator()( const value_type& lhs, const value_type& rhs ) const
              {
                return _cmp((lhs.first,rhs.first));
              }
          };
          
              ///// constructors
          explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
          {
            _avl = NULL;
            _size = 0;
            _compare = comp;
            _alloc = alloc;
          }
          template <class InputIterator>  
          map (InputIterator first, InputIterator last,const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
          {
            _compare = comp;
            _alloc = alloc;
            while(first != last)
            {
              _avl->insert(*first);
              ++first;
            }
            _size = _avl->get_size();
          }

          map( const map& other )
          {
            _avl = other._avl;
            _compare = other._compare;
            _size = other._size;
          }
          
          allocator_type get_allocator() const
          {
            return (_alloc);
          }
          
          map& operator=( const map& other )
          {
            _avl = other._avl;
            _compare = other._compare;
            _size = other._size;
          }
      // iterators
        iterator begin()
        {
          return (iterator(_avl->min_node(_avl->get_root()), _avl));
        }
        const_iterator begin() const
        {
          return (iterator(_avl->min_node(_avl->get_root()), _avl));
        }
        iterator end()
        {
          return (iterator(NULL, _avl));
        }
        const_iterator end() const
        { 
          return (iterator(NULL, _avl));
        }
        
        reverse_iterator rbegin()
        {
          return (reverse_iterator(end()));
        }
        const_reverse_iterator rbegin() const
        {
          return (reverse_iterator(end()));
        }
        reverse_iterator rend()
        {
          retrun (reverse_iterator(begin()));
        }
        const_reverse_iterator rend() const
        {
          return(const_reverse_iterator(begin()));
        }
        
      private:
        tree  _avl;
        size_type             _size;
        allocator_type        _alloc;
        key_compare           _compare;
          
    };
    
};