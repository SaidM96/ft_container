/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:32:01 by smia              #+#    #+#             */
/*   Updated: 2022/11/08 14:51:45 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <iostream>
#include "iterator.hpp"

template <typename T , typename alloc = std::allocator<T> >
class random_access_iterator : public iterator
{
    private:
        T*  _ptr;
    public:
        random_access_iterator()
        {
            _ptr = NULL;
        }

        random_access_iterator(T* ptr)
        {
            _ptr = ptr;
        }

        ~random_access_iterator()
        {   
        }

        random_access_iterator(random_access_iterator& const cp)
        {
            *this = cp;
        }

        void operator=(random_access_iterator& const other)
        {
            this->_ptr = other._ptr;
        }
    
        bool operator==(random_access_iterator& const other)
        {
            if(this->_ptr == other._ptr)
                return true;
            return false;
        }

        bool operator!=(random_access_iterator& const other)
        {
            if(this->_ptr != other._ptr)
                return true;
            return false;
        }

        T& operator*(random_access_iterator& const other)
        {
            return (*_ptr);
        }

        T* operator->(random_access_iterator& const other)
        {
            return (_ptr);
        }

        T& operator++(void)
        {
            _ptr++;
            return (*this); 
        }

        T& operator--(void)
        {
            _ptr--;
            return (*this); 
        }

        T operator++(int)
        {
            T tmp;
            tmp._ptr = this->_ptr;
            this->_ptr++;
            return (tmp); 
        }

        T operator--(int)
        {
            T tmp;
            tmp._ptr = this->_ptr;
            this->_ptr--;
            return (tmp);
        }

        T&  operator+(int n)
        {
            return (this->_ptr + n);
        }

        T&  operator-(int n)
        {
            return (this->_ptr - n);
        }

        T&  operator+(T& const other)
        {
            return (this->_ptr + other._ptr);
        }

        T&  operator-(T& const other)
        {
            return (this->_ptr - other._ptr);
        }

        T&  operator+=(int n)
        {
            return (this->_ptr + n);
        }

        T&  operator-=(int n)
        {
            return (this->_ptr - n);
        }

        T&  operator[](int n)
        {
            return (_ptr + n);
        }
};