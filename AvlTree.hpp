/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AvlTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:37:20 by smia              #+#    #+#             */
/*   Updated: 2022/12/20 02:21:32 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#pragma once

#include "iostream"
#include <string>

template <typename T, class alloc = std::allocator<T> >
class node
{
    public:
        T* _value;
        alloc _alloc;
        node* _parent;
        node* _right;
        node* _left;
        size_t _height;
        int _balance;
        
        node()
        {
            _value = NULL;
            _parent = NULL;
            _left = NULL;
            _right = NULL;
            _height = 0;
            _balance = 0;
        }
        
        node(const T& value)
        {
            _value = _alloc.allocate(1);
            _alloc.construct(_value, value);
            _parent = NULL;
            _left = NULL;
            _right = NULL;
            _height = 1;
            _balance = 0;
        }
        
        node& operator=(const node& x)
        {
            if (_value)
                _alloc.destroy(_value);
            else
                _value = _alloc.allocate(1);
            _alloc.construct(_value, *(x._value));
            _parent = x._parent;
            _left = x._left;
            _right = x._right;
            _height = x._height;
            _balance = x._balance;
            return (*this);
        }

        ~node(){}
};

template <typename T, class cmp = std::less<T>, class alloc = std::allocator<T> >
class AvlTree
{
    private:
        node<T, alloc>*                                             _root;
        size_t                                                       _size;
        alloc                                                        _alloc;
        cmp                                                         _compare;
        typename alloc::template rebind<node<T, alloc> >::other     _alloc_node;

        size_t is_child(node<T, alloc>* Node)
        {
            if(Node == NULL || Node->_parent == NULL)
                return 0;
            if (Node == Node->_parent->_left) // Node is a left child
                return 1;
            return 2; // Node is a Right child
        }
        
        size_t max(int a, int b)
        {
            if (a > b)
                return a;
            return b;
        }
        
        size_t get_height(node<T, alloc>* Node)
        {
            if (Node == NULL)
                return 0;
            return (Node->_height);
        }        
        
        int get_balance(node<T, alloc>* Node)
        {
            if (Node == NULL)
                return 0;
            return (get_height(Node->_left) - get_height(Node->_right));
        }

        void left_rotate(node<T, alloc>* Node)
        {
            node<T, alloc>* hold = (Node)->_parent;
            node<T, alloc>* ptr = (Node)->_right;
            node<T, alloc>* tmp = ptr->_left;


            Node->_parent = ptr;
            ptr->_left = Node;
            Node->_right = tmp;
            ptr->_parent = hold;
            if (Node != _root)
            {
                if(is_child(Node) == 1)
                    hold->_left = ptr;
                else if (is_child(Node) == 2)
                    hold->_right = ptr;
            }
            else
                _root = ptr;
            (Node)->_height = max(get_height((Node)->_right), get_height((Node)->_left)) + 1;
            ptr->_height = max(get_height(ptr->_right), get_height(ptr->_left)) + 1;

            (Node)->_balance = get_balance(Node);
            ptr->_balance = get_balance(ptr);
        }

        void right_rotate(node<T, alloc>* Node)
        {
            node<T, alloc>* hold = Node->_parent;
            node<T, alloc>* ptr = Node->_left;
            node<T, alloc>* tmp = ptr->_right;

            Node->_parent = ptr;
            ptr->_right = Node;
            Node->_left = tmp;
            ptr->_parent = hold;
            if (Node != _root)
            {
                if(is_child(Node) == 1)
                    hold->_left = ptr;
                else if (is_child(Node) == 2)
                    hold->_right = ptr;
            }
            else
                _root = ptr;
            (Node)->_height = max(get_height((Node)->_right), get_height((Node)->_left)) + 1;
            ptr->_height = max(get_height(ptr->_right), get_height(ptr->_left)) + 1;

            (Node)->_balance = get_balance(Node);
            ptr->_balance = get_balance(ptr);
        }
    
        void rebalance(node<T, alloc>* Node, const T& value)
        {
            if (Node->_balance > 1)
            {
                if (_compare(value, *(Node->_left->_value)))
                    right_rotate(Node);
                else
                {
                    left_rotate(Node->_left);
                    right_rotate(Node);
                }
                    
            }
            else if (Node->_balance < -1)
            {
                if (_compare(*(Node->_right->_value), value))
                {
                    left_rotate(Node);
                }
                else
                {
                    right_rotate(Node->_right);
                    left_rotate(Node);
                }
            }
        }
        
        void helper_insert(node<T, alloc>** root, const T& value)
        {
            // using recursion we insert new Node like BST insertion
            if (*root == NULL)
            {
                (*root) = _alloc_node.allocate(1);
                _alloc_node.construct((*root), value);
            }
            else if (_compare(*((*root)->_value),value))
            {
                helper_insert(&((*root)->_right), value);
                (*root)->_right->_parent = (*root);
            }
            else if (_compare(value, *((*root)->_value)))
            {
                helper_insert(&((*root)->_left), value);
                (*root)->_left->_parent = (*root);
            }
            else
                return ;
            // update height factor 
            (*root)->_height = max(get_height((*root)->_left), get_height((*root)->_right)) + 1;      
            (*root)->_balance = get_balance((*root));
            // rebalance
            rebalance(*root, value);
        }
        
        node<T, alloc>* inorder_successor(node<T, alloc>* Node)
        {
            if (Node == NULL || Node->_left == NULL)
                return Node;
            while(Node != NULL && Node->_left != NULL)
            {
                Node = Node->_left;
            }
            return Node;
        }
        void rebalance_delete(node<T, alloc>* Node)
        {
            if (Node->_balance > 1)
            {
                if (Node->_left->_balance >= 0)
                {
                    right_rotate(Node);
                }
                else
                {
                    left_rotate(Node->_left);
                    right_rotate(Node);
                }
            }
            if (Node->_balance < -1)
            {
                if (Node->_right->_balance <= 0)
                {
                    left_rotate(Node);
                }
                else
                {
                    right_rotate(Node->_right);
                    left_rotate(Node->_left);
                }               
            }
        }

        void helper_delete(node<T, alloc>** root, const T& value)
        {
            if ((*root) == NULL)
                return ;
            if (_compare(value, *((*root)->_value)))
                helper_delete(&((*root)->_left), value);
            else if (_compare(*((*root)->_value), value))
                helper_delete(&((*root)->_right), value);
            else
            {
                if ((*root)->_left == NULL  && (*root)->_right == NULL) // no child
                {
                    _alloc.destroy((*root)->_value);
                    _alloc.deallocate((*root)->_value, 1);
                    (*root)->_value = NULL;
                    _alloc_node.destroy((*root));
                    _alloc_node.deallocate((*root), 1);
                    (*root) = NULL;
                }
                else if ((*root)->_left != NULL  && (*root)->_right != NULL) // two child
                {
                    node<T, alloc>* ptr = inorder_successor((*root)->_right); // now ptr point to a node with a minimum value in the right subtree
                    *((*root)->_value) = *(ptr->_value);
                    helper_delete(&((*root)->_right), value);
                }
                else // one child
                {
                    node<T, alloc>* hold = (*root)->_parent;
                    node<T, alloc>* ptr;
                    if ((*root)->_left != NULL)
                        ptr = (*root)->_left;
                    else
                        ptr = (*root)->_right;
                    ptr->_parent = hold;
                    *(*root) = *ptr;
                    _alloc.destroy(ptr->_value);
                    _alloc.deallocate(ptr->_value, 1);
                    _alloc_node.destroy(ptr);
                    _alloc_node.deallocate(ptr, 1);
                }
            }
            if ((*root) == NULL)
                return ;
            // update height factor 
            (*root)->_height = max(get_height((*root)->_left), get_height((*root)->_right)) + 1;      
            (*root)->_balance = get_balance((*root));
            // rebalance
            rebalance_delete(*root);
        }
        
    public:
        AvlTree()
        {
            _root = NULL;
        }

        AvlTree(const AvlTree& cp)
        {
            *this = cp;
        }
        
        AvlTree& operator=(const AvlTree& x)
        {
            _root = x._root;
            _compare = x._compare;

            return (*this);
        }
        
        ~AvlTree(){}

        size_t max_size(void) const
        {
            return (_alloc_node.max_size());
        }

        node<T, alloc>* get_root(void) const
        {
            return (this->_root);
        }
        
        void insert(const T& value)
        {
            helper_insert(&_root, value);
        }

        bool search(const T& value)
        {
            if (helper_search(_root, value) != NULL)
                return true;
            return false;
        }

        void Delete(const T&  value)
        {
            helper_delete(&_root, value);
        }

        void printTree(node<T, alloc> *root, std::string indent, bool last) 
        {
            if (root != NULL) 
            {
                std::cout << indent;
                if (last) {
                std::cout << "R----";
                indent += "   ";
                } else {
                std::cout << "L----";
                indent += "|  ";
                }
                std::cout << *(root->_value) << std::endl;
                printTree(root->_left, indent, false);
                printTree(root->_right, indent, true);
            }
        }
        
        
};
