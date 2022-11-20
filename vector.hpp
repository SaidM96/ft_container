/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:06:48 by smia              #+#    #+#             */
/*   Updated: 2022/11/20 03:09:29 by smia             ###   ########.fr       */
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
			typedef ft::random_access_iterator<value_type const>	const_iterator;
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
				size_type		size =  static_cast<size_type>(last - first);
				_size = size;
				_capacity = size;
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
				if (_capacity)
					_alloc.deallocate(_data, _capacity);
				_size = other._size;
				_capacity = other._capacity;
				_data = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_data + i, other._data[i]);
				return *this;
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
			void reserve(size_type new_cap )
			{
				size_type CapacityHold = _capacity;
				if (new_cap > max_size())
					throw std::length_error("The size requested is greater than the maximum size!");
				if (CapacityHold == 0 && _size == 0)
				{
					
					_data = _alloc.allocate(new_cap);
					_capacity = new_cap;
				}
				if (new_cap > CapacityHold && _size == 0)
				{
					
					_alloc.deallocate(_data, CapacityHold);
					_data = _alloc.allocate(new_cap);
					_capacity = new_cap;
				}
				if (new_cap > CapacityHold && _size >= 1)
				{
					pointer hold;
					
					hold = _alloc.allocate(new_cap);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(hold + i, _data[i]);
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_data + i);
					_alloc.deallocate(_data, CapacityHold);
					_data = hold;
					_capacity = new_cap;
				}
			}
			
			// Modifiers
			void clear()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data + i);
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
				_alloc.construct(_data + _size, value);
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

			void assign( size_type count, const T& value )
			{
				clear();
				reserve(count);
				for (size_type i = 0; i < count; i++)
					push_back(value);
			}
			
			template<class InputIt>
			void assign(InputIt first, InputIt last , typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
			{
				size_type diff = static_cast<size_type>(ft::distance(first, last));
				clear();
				reserve(diff);
				InputIt it;
				it = first;
				for (; it != last ; it++)
					push_back(*it);
			}
			
			iterator insert(iterator pos, const T& value )
			{
				size_type  position = static_cast<size_type>(ft::distance(begin(), pos));
				vector<T> tmp;
				tmp.assign(pos, end());
				erase(pos , end());
				push_back(value);
				iterator it = tmp.begin();
				for (; it != tmp.end(); it++)
					push_back(*it);
				return (begin() + position);
			}
			
			iterator insert( iterator pos, size_type count, const T& value )
			{
					size_type  position = static_cast<size_type>(ft::distance(begin(), pos));
					vector<T> tmp;
					tmp.assign(pos, end());
					erase(pos, end());
					for (size_type i = 0; i < count; i++)
						push_back(value);
					iterator it = tmp.begin();
					for (; it != tmp.end(); it++)
						push_back(*it);
					return (begin() + position);
			}

			template< class InputIt > 
			iterator insert( iterator pos, InputIt first, InputIt last , typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
			{
					size_type  position = static_cast<size_type>(ft::distance(begin(), pos));
					vector<T> tmp;
					tmp.assign(pos, end());
					erase(pos, end());
					InputIt it = first;
					for (; it != last; it++)
						push_back(*it);
					it = tmp.begin();
					for (; it != tmp.end(); it++)
						push_back(*it);
					return (begin() + position);
			}
			
			iterator erase( iterator pos )
			{
				size_type diff = static_cast<size_type>(ft::distance(begin(), pos));
				if (end() == pos)
					return pos;
				_alloc.destroy(_data + diff);
				size_t i = diff;
				while (i++ < _size)
				{
					_alloc.construct(_data + i, _data[i + 1]);
					_alloc.destroy(_data + (i + 1));
				}
				_size--;
				pos = (begin() + i);
				return (pos);
			}
			
			iterator erase( iterator first, iterator last )
			{
				size_type diff = static_cast<size_type>(ft::distance(first, last));
				size_type start = static_cast<size_type>(ft::distance(begin(), first));
				if (diff == 0)
					return last;
				size_type i = start;
				while (i++ < diff)
					_alloc.destroy(_data + i);
				if (end() == (begin() + i))
					return end();
				for (; last != end(); last++)
				{
					_alloc.construct(_data + start, *last);
					_alloc.destroy(&(*last));
					start++;
				}
				_size -= diff;
				return last;
			}

			void resize(size_type count, T value = T())
			{
				size_type hold = _size;
				
				if (count > max_size())
					throw std::length_error("The capacity required exceeds max_size()");
				if (hold < count)
					while(_size < count)
						push_back(value);
				if (hold > count)
					while(_size > count)
						pop_back();
			}
			void swap( vector& other )
			{
				size_type SizeTmp = _size;
				_size = other._size;
				other._size = SizeTmp;
				SizeTmp = _capacity;
				_capacity = other._capacity;
				other._capacity = SizeTmp;
				
				pointer ptr = _data;
				_data = other._data;
				other._data = ptr;
			}

			// Element access
			reference at( size_type pos )
			{
				if (pos >= _size)
					throw  std::out_of_range("The element required is not within the range");
				return _data[pos];
			}
			const_reference at( size_type pos ) const
			{
				if (pos >= _size)
					throw  std::out_of_range("The element required is not within the range");
				return _data[pos];
			}
			reference operator[]( size_type pos ){return at(pos);}
			const_reference operator[]( size_type pos ) const {return at(pos);}
			reference front() {at(0);}
			const_reference front() const {return at(0);}
			reference back() {at(_size - 1);}
			const_reference back() const {return at(_size - 1);}
			T* data() {return _data;}
			const T* data() const {return _data;}
	private:
				allocator_type	_alloc;
				size_type		_size;
				size_type		_capacity;
				pointer			_data;
};

	// operator==,!=,<,<=,>,>=,<=>
	template< class T, class Alloc> bool operator==( const ft::vector<T,Alloc>& lhs,const ft::vector<T,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		for (typename ft::vector<T>::size_type i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	}

	template< class T, class Alloc> bool operator!=( const ft::vector<T,Alloc>& lhs,const ft::vector<T,Alloc>& rhs ) 
	{
		return (!(lhs == rhs));
	}

	template< class T, class Alloc > bool operator<( const ft::vector<T,Alloc>& lhs,const ft::vector<T,Alloc>& rhs ) 
	{
		if (!(lhs.size() < rhs.size()))
			return false;
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class T, class Alloc > bool operator>( const ft::vector<T,Alloc>& lhs,const ft::vector<T,Alloc>& rhs ) 
	{
		if (lhs.size() <= rhs.size())
			return false;
		return (!lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class T, class Alloc > bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {return (!(lhs > rhs));}
	template< class T, class Alloc > bool operator>=( const ft::vector<T,Alloc>& lhs,const ft::vector<T,Alloc>& rhs ){ return (!(lhs < rhs));}
};

#endif