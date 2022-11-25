/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:37:20 by smia              #+#    #+#             */
/*   Updated: 2022/11/25 11:41:04 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#pragma once

#include "iostream"
#define RED 1
#define BLACK 0

struct node
{
    int value;
    int color;
    node* right;
    node* left;
    node* parent;
};

typedef node *ptr;

