/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:01:49 by smia              #+#    #+#             */
/*   Updated: 2022/11/08 15:08:15 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// member	definition in reverse_iterator	description
// iterator_type	Iterator	Iterator's type
// iterator_category	iterator_traits<Iterator>::iterator_category	Preserves Iterator's category
// value_type	iterator_traits<Iterator>::value_type	Preserves Iterator's value type
// difference_type	iterator_traits<Iterator>::difference_type	Preserves Iterator's difference type
// pointer	iterator_traits<Iterator>::pointer	Preserves Iterator's pointer type
// reference	iterator_traits<Iterator>::reference	Preserves Iterator's reference type
#pragma once
#include <iostream>
template <class Iterator> 
class reverse_iterator
{
    private:
        Iterator  iterator_type;
        iterator_traits<Iterator>::iterator_category   iterator_category;
        iterator_traits<Iterator>::value_type       value_type;
        iterator_traits<Iterator>::difference_type  difference_type;
        iterator_traits<Iterator>::pointer      pointer;
        iterator_traits<Iterator>::reference    reference;
    public:
        reverse_iterator()
        {
            
        }
        

        
};