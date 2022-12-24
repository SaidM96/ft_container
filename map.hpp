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
#include <iostream>
#include "iterator.hpp"
#include "AvlTree.hpp"
#include "pair.hpp"
#include "lexicographical_compare.hpp"
namespace ft
{
    template<class Key,class T,class Compare = std::less<Key>,class alloc = std::allocator<ft::pair< Key, T>> > 
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
          typedef  ft::bidirectional_iterator<const T, Compare, alloc>     const_iterator;
			    typedef  ft::reverse_iterator<iterator>					                 reverse_iterator;
			    typedef  ft::reverse_iterator<const_iterator>			               const_reverse_iterator;

          class value_compare  : public std::binary_function<value_type, value_type, bool>
          {
            friend class map;
            protected:
              Compare _cmp;
              value_compare(Compare cmp)
              {
                _cmp = cmp;
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
          explicit map (const key_compare& comp = key_compare(), const allocator_type& Alloc = allocator_type()) : _alloc(Alloc), _compare(comp)
          {
            _avl = NULL;
            _size = 0;
          }
          template <class InputIterator>  
          map (InputIterator first, InputIterator last,const key_compare& comp = key_compare(), const allocator_type& Alloc = allocator_type()) : _alloc(Alloc), _compare(comp)
          {
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
            _compare = other._compare;
            _avl = other._avl;
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
        
        // modifiers
        void clear()
        {
          _avl->Clear();
          _size = 0;
        }

        ft::pair<iterator, bool> insert( const value_type& value )
        {
            bool x;
            node<value_type, alloc>* ptr = _avl->insert(value);
            if (ptr == NULL)
              x = false;
            else
              x = true;
            iterator it(ptr, _avl);
            return (ft::pair<value_type, bool>(it,x));
        }

        iterator insert( iterator pos, const value_type& value )
        {
            (void)pos;
            return iterator(_avl->insert(value));
        }

        template< class InputIt >
        void insert( InputIt first, InputIt last )
        {
            while(first != last)
            {
              _avl->insert(*first);
              ++first;
            }
        }
      
        iterator erase( iterator pos )
        {
          _avl->Delete(*pos);
          _size = _avl->get_size();
        }

        iterator erase( iterator first, iterator last )
        {
          while(first != last)
          {
            _avl->Delete(*first);
            ++first;
          }
          _size = _avl->get_size();
        }

        size_type erase( const Key& key )
        {
          size_type size = _size;
          _avl->Delete(ft::make_pair(key, mapped_key()));
          if (size == _size)
          {
            _size = _avl->get_size();
            return 0;
          }           
          _size = _avl->get_size();
          return 1;
        }

        void swap( map& other )
        {
          tree tmp(_avl);
          key_compare   cmp = _compare;

          _compare = other._compare;
          _avl = other._avl;

          other._compare = cmp;
          other._avl = tmp;
        }

        // element access 
        T& at( const Key& key )
        {
           node<value_type, alloc>* ptr = _avl->helper_search(_avl->get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
           if (ptr != NULL)
            return ptr->_value->second;
           throw std::out_of_range("out of range\n");
        }

        const T& at( const Key& key ) const
        {
           node<value_type, alloc>* ptr = _avl->helper_search(_avl->get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
           value_type a = ptr->_value;
           if (ptr != NULL)
              return a.second;
           throw std::out_of_range("out of range\n");       
        }

        T& operator[]( const Key& key )
        {
           node<value_type, alloc>* ptr = _avl->helper_search(_avl->get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
           value_type a = ptr->_value;
           if (!ptr)
           {

              ptr = _avl->insert(*(ptr->_value));
              a = ptr->_value;
              _size = _avl->get_size();
              return a.second;
           }
           return a.second;
        }

        const T& at( const Key& key ) const
        {
          //  node<value_type, alloc>* ptr = _avl->helper_search(_avl->get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
          //  value_type a = ptr->_value;
          //  if (!ptr)
          //  {

          //     ptr = _avl->insert(*(ptr->_value));
          //     a = ptr->_value;
          //     _size = _avl->get_size();
          //     return a.second;
          //  }
          //  return a.second;
        }

        // capacity
        bool empty() const
        {
          return (_size != 0);
        }
        size_type size() const
        {
          return _size;
        }
        size_type max_size() const
        {
          return (_alloc.max_size());
        }
        // Lookup
        size_type count( const Key& key ) const
        {
           node<value_type, alloc>* ptr = _avl->helper_search(_avl->get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
           if (ptr != NULL)
              return 1;
           return 0;
        }
        iterator find( const Key& key )
        {
           node<value_type, alloc>* ptr = _avl->helper_search(_avl->get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
           if (ptr == NULL)
              return (end());
           value_type a = ptr->_value;
           return (iterator(a, _avl));
        }
        const_iterator find( const Key& key ) const
        {
           node<value_type, alloc>* ptr = _avl->helper_search(_avl->get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
           if (ptr == NULL)
              return (end());
           value_type a = ptr->_value;
           return (const_iterator(a, _avl));
        }
        iterator lower_bound( const Key& key )
        {
           node<value_type, alloc>* ptr = _avl->helper_search(_avl->get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
           if (ptr == NULL)
              return (end());
           ptr = _avl->inorder_predecessor(*(ptr->_value));
          return (iterator(ptr->_value, _avl));
        }

        const_iterator lower_bound( const Key& key ) const
        {
           node<value_type, alloc>* ptr = _avl->helper_search(_avl->get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
           if (ptr == NULL)
              return (end());
           ptr = _avl->inorder_predecessor(*(ptr->_value));
          return (const_iterator(ptr->_value, _avl));
        }

        iterator upper_bound( const Key& key )
        {
            node<value_type, alloc>* ptr = _avl->helper_search(_avl->get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
           if (ptr == NULL)
              return (end());
            ptr = _avl->inorder_successor(*(ptr->_value));
          return (iterator(ptr->_value, _avl));
        }

        const_iterator upper_bound( const Key& key ) const
        {
            node<value_type, alloc>* ptr = _avl->helper_search(_avl->get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
           if (ptr == NULL)
              return (end());
            ptr = _avl->inorder_successor(*(ptr->_value));
          return (const_iterator(ptr->_value, _avl));
        }

        ft::pair<iterator,iterator> equal_range( const Key& key )
        {
            return (make_pair(lower_bound(key), upper_bound(key)));
        }

        ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
        {
            return (make_pair(lower_bound(key), upper_bound(key)));
        }

        // Observers
        key_compare key_comp() const
        {
          return _compare;
        }

        typename ft::map<value_type, key_compare, alloc>::value_compare value_comp() const
        {
            return (value_comp(_compare));
        }
      private:
        tree                  _avl;
        size_type             _size;
        allocator_type        _alloc;
        key_compare           _compare;
          
    };

    template< class Key, class T, class Compare, class Alloc >
    void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs )
    {
          lhs.swap(rhs);
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator==( const typename ft::map<Key,T,Compare,Alloc>& lhs,const typename  ft::map<Key,T,Compare,Alloc>& rhs )
    {
      typename ft::map<Key, T, Compare, Alloc>::const_iterator it = lhs.begin();
      typename  ft::map<Key, T, Compare, Alloc>::const_iterator itt = rhs.begin();

      while(it != lhs.end() && itt != rhs.end())
      {
        if (it != itt)
          return false;
        ++it;
        ++itt;
      }
      if (it == itt)
        return true;
      return false;
    }
    template< class Key, class T, class Compare, class Alloc >
    bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,const ft::map<Key,T,Compare,Alloc>& rhs )
    {
      return (!(lhs == rhs));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return (!(lhs > rhs));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return (!(lhs < rhs));
    }
};