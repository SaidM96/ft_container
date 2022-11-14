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

			typedef T				value_type;
			typedef Allocator		allocator_type;
			typedef size_type		std::size_t;
			typedef difference_type	std::ptrdiff_t;
			typedef	reference		value_type&;	
			typedef	const_reference		const value_type&;	
            explicit vector(const allocator_type& alloc = allocator_type()){}
            
};
}

#endif