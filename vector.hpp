/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:06:48 by smia              #+#    #+#             */
/*   Updated: 2022/11/14 02:53:23 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "iterator.hpp"

namespace ft
{
template < class T, class Alloc = std::allocator<T> > 
class vector
{
    private:
			allocator_type	_alloc;
			size_type		_size;
			size_type		_capacity;
			pointer			_ptr;
    public:

			typedef T				                                value_type;
			typedef Allocator										allocator_type;
			typedef std::size_t                                     size_type;
			typedef std::ptrdiff_t                                  difference_type;
			typedef	typename allocator_type::reference              reference;	
			typedef	typename allocator_type::const_reference        const_reference;
            typedef typename allocator::pointer                     pointer;
            typedef typename allocator::const_pointer               const_pointer;
            typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
            explicit vector(const allocator_type& alloc = allocator_type()){}
            
};
}

#endif