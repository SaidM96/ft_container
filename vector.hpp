/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:06:48 by smia              #+#    #+#             */
/*   Updated: 2022/11/18 03:54:11 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "iterator.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"
namespace ft
{
template < class T, class Allocator = std::allocator<T> > 
class vector
{
    private:
			allocator_type	_alloc;
			size_type		_size;
			size_type		_capacity;
			pointer			_data;
    public:

			typedef T				                                value_type;
			typedef Allocator										allocator_type;
			typedef std::size_t                                     size_type;
			typedef std::ptrdiff_t                                  difference_type;
			typedef	typename allocator_type::reference              reference;	
			typedef	typename allocator_type::const_reference        const_reference;
            typedef typename Allocator::pointer                     pointer;
            typedef typename Allocator::const_pointer               const_pointer;
            typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			// constructors
            explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc) , _size(0), _capacity(0), _data(NULL){}
			explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
			{
				_alloc = alloc;
				_size = count;
				_capacity = count;
				_data = _alloc.allocate(count);
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_data + i, value);
			}

			template< class InputIt >
			vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
			{
				difference_type		size = last - first;
				_size = static_cast<size_type>(size);
				_capacity = static_cast<size_type>(size);
				_alloc = alloc;
				_data = _alloc.allocate(size);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(_data + i, *first);
					first++;	
				}
			}
			// destructor
			~vector()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data + i);
				if (_capacity)
					_alloc.deallocate(_data, _capacity);
			}
			// copy constructor
			vector( const vector& other ) 
			{
				_capacity = 0;
				_size = 0;
				*this = other;
			}
			// assignement operator
			vector& operator=( const vector& other )
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data + i);
				_alloc.deallocate(_data, _capacity);
				_size = other._size;
				_capacity = other._capacity;
				_data = _alloc.allocate(_capacity)
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_data + i, other._data[i]);
				return *this;
			}
			void assign( size_type count, const T& value )
			{
				
			}
			// Returns the allocator associated with the container
			allocator_type get_allocator() const
			{
				return (this->_alloc);
			}

			// iterators
				// begin
			iterator  begin(){return(iterator(_data));}
			const_iterator begin() const {return (const_iterator(_data));}
			reverse_iterator rbegin(){return (reverse_iterator(end()));}
			const_reverse_iterator rbegin() const {return (const_reverse_iterator(end()));}
				// end
			iterator end() {return (iterator(_data + _size));}
			const_iterator end() const {return (const_iterator(_data + _size));}
			reverse_iterator rend(){return (reverse_iterator(begin()));}
			const_reverse_iterator rend() const {return (const_reverse_iterator(begin()));}
			
			// Capacity
			bool empty() const 
			{
				if (begin() == end())
					return true;
				return false;
			}
			size_type size() const {return _size;}
			size_type max_size() const {return (_alloc.max_size());}
			size_type capacity() const {return _capacity;}
			void reserve( size_type new_cap )
			{
				if (_capacity == 0)
				{
					_data = _allocate(new_cap);
					_capacity = new_cap;
				}	
				else if (new_cap > _capacity)
				{
					pointer hold;
					for (size_type i = 0; i < _size; i++)
						*(hold + i) = *(_data + _size);
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_data + i);
					_alloc.deallocate(_data, _capacity);
					_data = _allocate(new_cap);
					_capacity = new_cap;
					for (size_type i = 0; i < _size; i++)
						_data = _alloc.construct(_data + i, *(hold + i));
				}
			}
			
			// Modifiers
			void clear()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data[i]);
				_size = 0;
			}
			
			void push_back( const T& value )
			{
				if (_capacity == 0)
					reserve(2);
				if (_size + 1 > _capacity)
				{
					_capacity *= 2;
					reserve(_capacity);
				}
				_alloc.construct(_data + _size);
				_size++;	
			}
			
			void pop_back()
			{
				if (_size >= 1)
				{
					_alloc.destroy(_data + _size);
					_size--;
				}
			}
			
			iterator insert(const_iterator pos, const T& value )
			{
					
			}
			iterator erase( iterator pos )
			{
				
			}
			

};

}

#endif