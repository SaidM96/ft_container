/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:34:14 by smia              #+#    #+#             */
/*   Updated: 2022/12/29 08:09:37 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "iterator.hpp"
#include "pair.hpp"
#include "lexicographical_compare.hpp"
#include "vector.hpp"
namespace ft
{
    template<class Key,class T,class Compare = std::less<Key>,class alloc = std::allocator<ft::pair< const Key, T> > > 
    class map
    {
      public:
          typedef  Key                                                     Key_type;
          typedef  T                                                       mapped_key;
          typedef  ft::pair< const Key_type, mapped_key>                   value_type;
          typedef  std::size_t                                             size_type;
          typedef  std::ptrdiff_t                                          difference_type;
          typedef  Compare                                                 key_compare;
          typedef  alloc                                                   allocator_type;
          typedef  value_type&                                             reference;
          typedef  const value_type&                                       const_reference;
          typedef  typename allocator_type::pointer                        pointer;
          typedef  typename allocator_type::const_pointer                  onst_pointer;
          typedef  typename ft::bidirectional_iterator<value_type, key_compare, allocator_type>           iterator;
          typedef  typename ft::bidirectional_iterator<const value_type, key_compare, allocator_type>     const_iterator;
			    typedef  typename ft::reverse_iterator<iterator>					                 reverse_iterator;
			    typedef  typename ft::reverse_iterator<const_iterator>			               const_reverse_iterator;

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
              typedef bool          result_type;
              typedef value_type    first;
              typedef value_type    secound;
              bool operator()( const value_type& lhs, const value_type& rhs ) const
              {
                return _cmp(lhs.first, rhs.first);
              }
          };

          ///// constructors
          explicit map (const key_compare& comp = key_compare(), const allocator_type& Alloc = allocator_type()) : _alloc(Alloc), _compare(comp)
          {
            _size = 0;
          } 
          template <class InputIterator>  
          map (InputIterator first, InputIterator last,const key_compare& comp = key_compare(), const allocator_type& Alloc = allocator_type()) : _alloc(Alloc), _compare(comp)
          {
            while(first != last)
            {
              insert(*first);
              ++first;
            }
            _size = _avl.get_size();
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
            return (*this);
          }
          ~map() 
          {
            clear();
          }
          
      // iterators
        iterator begin()
        {
          node<value_type, alloc>* ptr = _avl.min_node(_avl.get_root());
          if (ptr == NULL)
            return (iterator(NULL, &_avl));
          return (iterator(ptr->_value, &_avl));
        }
        const_iterator begin() const
        {
          node<value_type, alloc>* ptr = _avl.min_node(_avl.get_root());
          if (ptr == NULL)
            return (const_iterator(NULL, &_avl));
          return (const_iterator(ptr->_value, &_avl));
        }
        iterator end()
        {
          return (iterator(NULL, &_avl));
        }
        const_iterator end() const
        { 
          return (const_iterator(NULL, &_avl));
        }
        reverse_iterator rbegin()
        {
          return (reverse_iterator(end()));
        }
        const_reverse_iterator rbegin() const
        {
          return (const_reverse_iterator(end()));
        }
        reverse_iterator rend()
        {
          return (reverse_iterator(begin()));
        }
        const_reverse_iterator rend() const
        {
          return(const_reverse_iterator(begin()));
        }
        
        // modifiers
        void clear()
        {
				  _avl.Clear();
				  _size = 0;
        }
    
        ft::pair<iterator, bool> insert( const value_type& value )
        {
            iterator it;
            node<value_type, alloc>* Node = _avl.helper_search(_avl.get_root(), value);
            if(Node != NULL)
            {
              it = iterator(Node->_value, &_avl);
              return (ft::make_pair(it,false));
            }
            else
            {
              node<value_type, alloc>* ptr = _avl.insert(value);
              _size = _avl.get_size();
              it = iterator(ptr->_value, &_avl);
              return (ft::make_pair(it,true));
            }
        }

        iterator insert( iterator pos, const value_type& value )
        {
            (void)pos;
            pair<iterator, bool> p = insert(value);
            return p.first;
        }

        template< class InputIt >
        void insert( InputIt first, InputIt last )
        {
            while(first != NULL && first != last)
            {
              _avl.insert(*first);
              ++first;
            }
            _size = _avl.get_size();
        }
      
        void erase( iterator pos )
        {
          _avl.Delete(*pos);
          _size = _avl.get_size();
          
        }

        void erase( iterator first, iterator last )
        {
            ft::vector<Key> keys;
            while (first != last)
            {
              keys.push_back(first->first);
              ++first;
            }
            for(size_t i = 0; i < keys.size(); i++)
              erase(keys[i]);
        }

        size_type erase( const Key& key )
        {
          size_type size = _size;
          value_type	p = ft::make_pair<const Key, T>(key, T());
          _avl.Delete(p);
          if (size == _size)
            return 0; 
          _size = _avl.get_size();
          return 1;
        }

        void swap( map& other )
        {

          size_t sizeTmp = _size;
          _size = other._size;
          other._size = sizeTmp;
        
          _avl.swap(other._avl);
          std::swap(_compare, other._compare);
        }

        // element access 
        T& at( const Key& key )
        {
           node<value_type, alloc>* ptr = _avl.helper_search(_avl.get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
           if (ptr != NULL)
              return ptr->_value->second;
           throw std::out_of_range("out of range\n");
        }

        const T& at( const Key& key ) const
        {
           node<value_type, alloc>* ptr = _avl.helper_search(_avl.get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
           if (ptr != NULL)
              return ptr->_value->second;
           throw std::out_of_range("out of range\n");       
        }

        T& operator[]( const Key& k )
        {
            value_type	p = ft::make_pair<const Key, T>(k, T());
            node<value_type, alloc>* Node = _avl.helper_search(_avl.get_root(), p);
            if (!Node) {
              Node = _avl.insert(p);
              _size = _avl.get_size();
              return (Node->_value->second);
            }
            return Node->_value->second;
        }

        // capacity
        bool empty() const
        {
          return (_size == 0);
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
           node<value_type, alloc>* ptr = _avl.helper_search(_avl.get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
           if (ptr != NULL)
              return 1;
           return 0;
        }
        
        iterator find( const Key& key )
        {
           node<value_type, alloc>* ptr = _avl.helper_search(_avl.get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
           if (ptr == NULL)
              return (end());
           return (iterator(ptr->_value, &_avl));
        }
        
        const_iterator find( const Key& key ) const
        {
           node<value_type, alloc>* ptr = _avl.helper_search(_avl.get_root(), ft::make_pair<Key_type, mapped_key>(key, mapped_key()));
           if (ptr == NULL)
              return (end());
           return (const_iterator(ptr->_value, &_avl));
        }
        
        iterator lower_bound( const Key& key )
        {
            iterator it = this->begin();
            while(it != this->end())
            {
              if (!_compare((*it).first, key))
                break ;
              ++it;
            }
            return it;
        }

        const_iterator lower_bound( const Key& key ) const
        {
            const_iterator it = this->begin();
            while(it != this->end())
            {
              if (!_compare((*it).first, key))
                break ;
              ++it;
            }
            return it;
        }

        iterator upper_bound( const Key& key )
        {
            iterator it = this->begin();
            while(it != this->end())
            {
              if (_compare(key, (*it).first))
                break ;
              ++it;
            }
            return it;
        }

        const_iterator upper_bound( const Key& key ) const
        {
            const_iterator it = this->begin();
            while(it != this->end())
            {
              if (_compare(key, (*it).first))
                break ;
              ++it;
            }
            return it;
        }

        ft::pair<iterator,iterator> equal_range( const Key& key )
        {
            return (ft::make_pair(lower_bound(key), upper_bound(key)));
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

        value_compare value_comp() const
        {
            return (value_compare(_compare));
        }
        
        void print()
        {
          _avl.printTree(_avl.get_root());
        }
      private:
        AvlTree<value_type, Compare, alloc>                  _avl;
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