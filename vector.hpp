/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:06:48 by smia              #+#    #+#             */
/*   Updated: 2022/11/15 21:44:23 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "iterator.hpp"

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
			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator())
			{
				_alloc = alloc;
				_size = count;
				_capacity = count;
				_data = _alloc.allocate(count);
				for (size_type i = 0; i < count; i++)
					_alloc.construct(&_data[i], value);
			}
			template< class InputIt >
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() )
			{
				
			}
			// destructor
			~vector()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data[i]);
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
					_alloc.destroy(_data[i]);
				if (_capacity)
					_alloc.deallocate(_data, _capacity);
				_size = other._size;
				_capacity = other._capacity;
				_data = _alloc.allocate(_capacity)
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_data[i], other._data[i]);
				return *this;
			}

};
}

#endif