/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:58:42 by smia              #+#    #+#             */
/*   Updated: 2022/11/24 16:25:49 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

namespace ft{
template <class T, class Container = ft::vector<T> >
class stack
{
    protected:
        Container cont;
    public:
        typedef    Container                             container_type	;
        typedef    typename Container::value_type        value_type;
        typedef    typename Container::size_type         size_type;
        typedef    typename Container::reference         reference;
        typedef    typename Container::const_reference   const_reference;
        explicit stack( const container_type& Cont = container_type()) : cont(Cont){}
        stack(const stack& other) { this->cont = other.cont;}
        stack& operator=( const stack& other )
        {
            this->cont = other.cont;
            return (*this);
        }
        reference top() { return (cont.back());}
        const_reference top() const { return cont.back();}
        bool empty() const {return (cont.empty());}
        size_type size() const { return (cont.size());}
        void push( const value_type& value ) {cont.push_back(value);}
        void pop() { cont.pop_back();}
        
        // freind
        template< class T1, class T2 >
        friend bool operator==( const ft::stack<T1,T2>& lhs, const ft::stack<T1,T2>& rhs );
        template< class T1, class T2 >
        friend bool operator!=( const ft::stack<T1,T2>& lhs, const ft::stack<T1,T2>& rhs );
        template< class T1, class T2 >
        friend bool operator<=( const ft::stack<T1,T2>& lhs, const ft::stack<T1,T2>& rhs );
        template< class T1, class T2 >
        friend bool operator>=( const ft::stack<T1,T2>& lhs, const ft::stack<T1,T2>& rhs );
        template< class T1, class T2 >
        friend bool operator>( const ft::stack<T1,T2>& lhs, const ft::stack<T1,T2>& rhs );
        template< class T1, class T2 >
        friend bool operator<( const ft::stack<T1,T2>& lhs, const ft::stack<T1,T2>& rhs );
        
        
};  
template< class T, class Container >
bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{
    return (lhs.cont == rhs.cont);
}

template< class T, class Container >
bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{
    return (lhs.cont != rhs.cont);
}

template< class T, class Container > // ?
bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{
    return (lhs.cont > rhs.cont);
}

template< class T, class Container >
bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{
    return (lhs.cont < rhs.cont);
}

template< class T, class Container >
bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{
    return (lhs.cont >= rhs.cont);
}

template< class T, class Container >
bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{
    return (lhs.cont <= rhs.cont);
}

};
