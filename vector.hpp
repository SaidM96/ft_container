/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:06:48 by smia              #+#    #+#             */
/*   Updated: 2022/12/19 23:00:56 by smia             ###   ########.fr       */
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
				if (count)
					_data = _alloc.allocate(count);
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_data + i, value);
			}

			template< class InputIt >
			vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
			{
				size_type		size =  static_cast<size_type>(std::distance(first, last));
				_size = size;
				_capacity = size;
				_alloc = alloc;
				_data = _alloc.allocate(size);
				for (size_type i = 0; first != last; first++, i++)
					_alloc.construct(_data + i, *first);
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
			iterator  begin(){return(iterator(this->_data));}
			const_iterator begin() const {return (const_iterator(this->_data));}
			reverse_iterator rbegin(){return (reverse_iterator(end()));}
			const_reverse_iterator rbegin() const {return (const_reverse_iterator(end()));}
				// end
			iterator end() {return (iterator(this->_data + this->_size));}
			const_iterator end() const {return (const_iterator(this->_data + this->_size));}
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
				else if (new_cap > CapacityHold && _size == 0)
				{
					
					_alloc.deallocate(_data, CapacityHold);
					_data = _alloc.allocate(new_cap);
					_capacity = new_cap;
				}
				else if (new_cap > CapacityHold && _size >= 1)
				{
					// vector<value_type> tmp(*this);
					// clear();
					// reserve(new_cap);
					// assign(tmp.begin(), tmp.end());
					//
					pointer hold;
					
					hold = _alloc.allocate(CapacityHold);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(hold + i, _data[i]);
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_data + i);
					_alloc.deallocate(_data, CapacityHold);
					_data = _alloc.allocate(new_cap);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(_data + i, *(hold + i));
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(hold + i);
					_alloc.deallocate(hold,CapacityHold);
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
					reserve(1);
				else if (_size + 1 > _capacity)
				{
					reserve(_capacity * 2);
				}
				_alloc.construct(_data + _size, value);
				_size++;
			}
			
			void pop_back()
			{
				if (_size >= 1)
				{
					_alloc.destroy(_data + _size - 1);
					_size--;
				}
			}

			void assign( size_type count, const T& value )
			{
				clear();
				if (_capacity < count)
					reserve(count);
				for (size_type i = 0; i < count; i++)
					push_back(value);
			}
			template<class InputIt>
			void assign(InputIt first, InputIt last , typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
			{
				size_type diff = static_cast<size_type>(std::distance(first, last));
				clear();   
				if (_size + diff > _capacity)
					reserve(diff);
				while(first != last)
				{
					push_back(*first);
					++first;
				}
			}
			
			iterator insert(iterator pos, const T& value )
			{
				size_type  BeginPos = static_cast<size_type>(std::distance(begin(), pos));
				size_type  PosEnd = static_cast<size_type>(std::distance(pos, end()));
				
				pointer hold = _alloc.allocate(_size - BeginPos);
				iterator it = pos;
				for (size_type i = 0; i < PosEnd; i++)
				{
					_alloc.construct(hold + i, *it);
					++it;
				}
				erase(pos, end());
				push_back(value);
				for (size_type i = 0; i < PosEnd; i++)
				{
					push_back(*(hold + i));
					_alloc.destroy(hold + i);
				}
				_alloc.deallocate(hold, PosEnd);
				return (begin() + BeginPos);
			}

			iterator insert( iterator pos, size_type count, const T& value )
			{
				size_type  BeginPos = static_cast<size_type>(std::distance(begin(), pos));
				size_type  PosEnd = static_cast<size_type>(std::distance(pos, end()));

				pointer hold = _alloc.allocate(_size - BeginPos);
				iterator it = pos;
				for (size_type i = 0; i < PosEnd; i++)
				{
					_alloc.construct(hold + i, *it);
					++it;
				}
				erase(pos, end());
				for (size_t i = 0; i < count; i++)
					push_back(value);
				for (size_type i = 0; i < PosEnd; i++)
				{
					push_back(*(hold + i));
					_alloc.destroy(hold + i);
				}
				_alloc.deallocate(hold, PosEnd);
				return (begin() + BeginPos);
			}

			template< class InputIt > 
			iterator insert( iterator pos, InputIt first, InputIt last , typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
			{

				size_type  p1 = static_cast<size_type>(std::distance(begin(), pos));
				size_type  p2 = static_cast<size_type>(std::distance(pos, end()));
				size_type  p3 = static_cast<size_type>(std::distance(first, last));
				if (!p3)
					return (begin());
				reserve(_size + p3);
				pointer hold = _alloc.allocate(p2);
				iterator it = begin() + p1; // which is pos
				for (size_type i = 0; i < p2; i++)
				{
					_alloc.construct(hold + i, *it);
					++it;
				}
				erase(begin() + p1, this->end());
				for (InputIt it1 = first; it1 != last; it1++)					
					push_back(*it1);
				for (size_type i = 0; i < p2; i++)
				{
					push_back(*(hold + i));
					_alloc.destroy(hold + i);
				}
				_alloc.deallocate(hold, p2);
				return (begin() + p1);
			}

			iterator erase( iterator pos )
			{
				size_type diff = static_cast<size_type>(std::distance(begin(), pos));
				if (end() == pos && diff < 0)
					return end();
				iterator it = pos;
				iterator end = this->end();
				_alloc.destroy(&(*pos));
				while(pos + 1 != end)
				{
					_alloc.construct(&(*pos), *(pos+1));
					++pos;
				}
				_size--;
				return (it);
			}
			
			iterator erase( iterator first, iterator last )
			{
				size_type start = static_cast<size_type>(std::distance(begin(), first));
				size_type lenght = static_cast<size_type>(std::distance(first, last));
				if (!lenght)
					return end();
				iterator frst = first;
				iterator lst = last;
				iterator end = this->end();
				while (frst != lst)
				{
					_alloc.destroy(&(*frst));
					++frst;
				}
				frst = first;
				lst = last;
				while (frst != lst && lst != end)
				{
					_alloc.construct(&(*frst), *lst);
					++frst;
					++lst;
				}
				_size -= lenght;
				return first;
				
			}

			void resize(size_type count, T value = T())
			{
				size_type sizeHold = _size;
				size_type capacityHold = _capacity;
				
				if (count > max_size())
					throw std::length_error("The capacity required exceeds max_size()");
				if (count > capacityHold && count <= capacityHold * 2)
					reserve(capacityHold * 2);
				if (count >= capacityHold && count > capacityHold * 2)
					reserve(count);
				if (sizeHold < count)
					while(_size < count)
						push_back(value);
				if (sizeHold > count)
					while(_size > count)
						pop_back();
			}
			void swap( vector& other )
			{
				vector tmp(*this);
				*this = other;
				other = tmp;
			}

			// Element access
			reference at( size_type pos )
			{
				if (pos < 0 || pos >= _size)
					throw std::out_of_range("vector");
				return _data[pos];
			}
			const_reference at( size_type pos ) const
			{
				if (pos < 0 || pos >= _size)
					throw std::out_of_range("vector");
				return _data[pos];
			}
			reference operator[]( size_type pos ){return _data[pos];}
			const_reference operator[]( size_type pos ) const {return _data[pos];}
			reference front() {return at(0);}
			const_reference front() const {return at(0);}
			reference back() {return at(_size - 1);}
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

	template< class T, class Alloc > bool operator!=( const ft::vector<T,Alloc>& lhs,const ft::vector<T,Alloc>& rhs ) 
	{
		return (!(lhs == rhs));
	}

	template< class T, class Alloc > bool operator<( const ft::vector<T,Alloc>& lhs,const ft::vector<T,Alloc>& rhs ) 
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && lhs != rhs);
	}

	template< class T, class Alloc > bool operator>( const ft::vector<T,Alloc>& lhs,const ft::vector<T,Alloc>& rhs ) 
	{
		return (!lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && lhs != rhs);
	}
	
	template< class T, class Alloc > void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs )
	{
		ft::vector<T, Alloc> tmp(lhs);
		lhs = rhs;
		rhs = tmp;
	}
	template< class T, class Alloc > bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) 
	{
		return ((lhs == rhs) || (lhs < rhs));
	}
	template< class T, class Alloc > bool operator>=( const ft::vector<T,Alloc>& lhs,const ft::vector<T,Alloc>& rhs )
	{
		return ((lhs == rhs) || (lhs > rhs));
	}
};

#endif