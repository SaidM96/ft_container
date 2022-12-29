/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AvlTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:37:20 by smia              #+#    #+#             */
/*   Updated: 2022/12/29 06:13:49 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#pragma once

#include "iostream"
#include <string>

namespace ft
{
template <typename T, class alloc = std::allocator<T> >
class node
{
    public:
        T*    _value;
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
            _parent = NULL;
            _left = NULL;
            _right = NULL;
            _value = _alloc.allocate(1);
            _alloc.construct(_value, value);
            _height = 1;
            _balance = 0;
        }
        
        node& operator=(const node& x)
        {
            if (_value)
            {
                _alloc.destroy(_value);
                _alloc.deallocate(_value, 1);
            }
            _value = _alloc.allocate(1);
            _alloc.construct(_value, *(x._value));
            _parent = x._parent;
            _left = x._left;
            _right = x._right;
            _height = x._height;
            _balance = x._balance;
            return (*this);
        }

        ~node()
        {
        }

};

template <typename T, class cmp = std::less<T>, class alloc = std::allocator<T> >
class AvlTree
{
    private:
        node<T, alloc>*                                             _root;
        size_t                                                       _size;
        cmp                                                         _compare;
        alloc                                                        _alloc;
        typename alloc::template rebind<node<T, alloc> >::other     _alloc_node;

    public:
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
            
            if (Node != _root)
            {
                if(is_child(Node) == 1)
                    hold->_left = ptr;
                else if (is_child(Node) == 2)
                    hold->_right = ptr;
            }
            else
                _root = ptr;
            Node->_right = tmp;
            if (Node->_right)
                Node->_right->_parent = Node;
            ptr->_parent = hold;
            Node->_parent = ptr;
            ptr->_left = Node;
            
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

            if (Node != _root)
            {
                if(is_child(Node) == 1)
                    hold->_left = ptr;
                else if (is_child(Node) == 2)
                    hold->_right = ptr;
            }
            else
                _root = ptr;

            Node->_left = tmp;
            if (Node->_left)
                Node->_left->_parent = Node;
            ptr->_parent = hold;
            Node->_parent = ptr;
            ptr->_right = Node;

            (Node)->_height = max(get_height((Node)->_right), get_height((Node)->_left)) + 1;
            ptr->_height = max(get_height(ptr->_right), get_height(ptr->_left)) + 1;

            (Node)->_balance = get_balance(Node);
            ptr->_balance = get_balance(ptr);
        }

        void rebalance(node<T, alloc>* Node, const T& value)
        {
            if (Node->_balance > 1)
            {
                if (_compare(value.first, Node->_left->_value->first))
                    right_rotate(Node);
                else
                {
                    left_rotate(Node->_left);
                    right_rotate(Node);
                }
            }
            else if (Node->_balance < -1)
            {
                if (_compare(Node->_right->_value->first, value.first))
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

        void helper_insert(node<T, alloc>** root, const T& value, node<T, alloc>** ret)
        {
            // using recursion we insert new Node like BST insertion
            if (*root == NULL)
            {
                (*root) = _alloc_node.allocate(1);
                _alloc_node.construct((*root), value);
                ++_size;
                *ret = (*root);
            }
            else if (_compare((*root)->_value->first, value.first))
            {
                helper_insert(&((*root)->_right), value, ret);
                (*root)->_right->_parent = (*root);
            }
            else if (_compare(value.first, (*root)->_value->first))
            {
                helper_insert(&((*root)->_left), value, ret);
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
            if (_compare(value.first, (*root)->_value->first))
                helper_delete(&((*root)->_left), value);
            else if (_compare((*root)->_value->first, value.first))
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
                    _size--;
                }
                else if ((*root)->_left != NULL  && (*root)->_right != NULL) // two child
                {
                    node<T, alloc>* ptr = min_node((*root)->_right); // now ptr point to a node with a minimum value in the right subtree
                    _alloc.construct((*root)->_value, *(ptr->_value));
                    helper_delete(&((*root)->_right), *(ptr->_value));
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
                    ptr->_value = NULL;
                    _alloc_node.destroy(ptr);
                    _alloc_node.deallocate(ptr, 1);
                    ptr = NULL;
                    _size--;
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
        void clear_helper(node<T, alloc>** root)
        {
            if ((*root) != NULL) 
            {
                clear_helper(&((*root)->_left));
                if ((*root)->_value != NULL)
                {
                    _alloc.destroy((*root)->_value);
                    _alloc.deallocate((*root)->_value, 1);
                    (*root)->_value = NULL;
                }
                clear_helper(&((*root)->_right));
                _alloc_node.destroy((*root));
                _alloc_node.deallocate((*root), 1);
                (*root) = NULL;
            }
        }

        AvlTree()
        {
            _size = 0;
            _root = NULL;
        }

        AvlTree(const AvlTree& cp)
        {
            *this = cp;
        }
        
        AvlTree& operator=(const AvlTree& x)
        {
            Clear();
            _compare = x._compare;
            Copy(x._root);
            return (*this);
        }
        
        ~AvlTree()
        {
        }
        
        node<T, alloc>* helper_search(node<T, alloc>* Node, const T& value) const
        {
            if (Node == NULL)
                return NULL;
            else if (_compare(value.first, Node->_value->first))
                return helper_search(Node->_left, value);
            else if (_compare(Node->_value->first ,value.first))
                return helper_search(Node->_right, value);
            else
                return Node;    
        }
        
        node<T, alloc>* inorder_successor(node<T, alloc>* Node) const
        {
            if (Node != NULL)
                return (inorder_successor(*(Node->_value)));
            return NULL;
        }
        
        node<T, alloc>* inorder_predecessor(node<T, alloc>* Node) const
        {
            if (Node != NULL)
                return (inorder_predecessor(*(Node->_value)));
            return NULL;
        }

        node<T, alloc>* inorder_successor(const T& value) const
        {
            node<T, alloc>* Node = helper_search(this->_root, value);
            if (Node == NULL)
                return NULL;
            if (Node->_right != NULL)
                return min_node(Node->_right);
            node<T, alloc>*	hold = Node->_parent;
            while(hold != NULL && hold->_left != Node)
            {
                Node = hold;
                hold = Node->_parent;
            }
            return hold;
        }
        
        node<T, alloc>* inorder_predecessor(const T& value) const
        {
            node<T, alloc>* Node = helper_search(this->_root, value);
            if (Node == NULL)
                return Node;
            if (Node->_left)
                return max_node(Node->_left);
            node<T, alloc>*	hold = Node->_parent;
            while(hold != NULL && hold->_right != Node)
            {
                Node = hold;
                hold = Node->_parent;
            }
            return hold;
        }
        
        size_t max_size(void) const
        {
            return (_alloc_node.max_size());
        }

        node<T, alloc>* get_root(void) const
        {
            return (this->_root);
        }
        size_t get_size(void) const
        {
            return _size;
        }
        node<T, alloc>* insert(const T& value)
        {
            node<T, alloc>* ret = NULL;
            helper_insert(&_root, value, &ret);
            return ret;
        }

        bool search(const T& value) const
        {
            if (helper_search(_root, value) != NULL)
                return true;
            return false;
        }

        void Delete(const T&  value)
        {
            helper_delete(&_root, value);
        }
        
		node<T, alloc>* min_node(node<T, alloc>* Node) const  
        {
			if (Node == NULL)
				return NULL;
			node<T, alloc>* ptr = Node;
			while (ptr->_left)
				ptr = ptr->_left;
			return ptr;
		}

		node<T, alloc>* max_node(node<T, alloc>* Node) const 
        {
			if (Node == NULL)
				return NULL;
			node<T, alloc>*	ptr = Node;
			while (ptr->_right)
				ptr = ptr->_right;
			return ptr;
		}
        
        void printTree(node<T, alloc> *root) 
        {
            if (root != NULL) 
            {
                printTree(root->_left);
                printTree(root->_right);
                if (root == _root)
                    std::cout << "this is root :  ";
                std::cout <<" key: " << root->_value->first << " value: " << root->_value->second  << " balance: " << root->_balance << std::endl;
            }
        }
        void Copy(const node<T, alloc> *Node) 
        {
			if (Node == NULL)
				return ;
			Copy(Node->_left);
			if (Node->_value)
				insert(*(Node->_value));
			Copy(Node->_right);
		}

        void swap(AvlTree& tree)
        {
            node<T, alloc>* tmp = _root;
            _root = tree._root;
            tree._root = tmp;

            size_t tmpSize = _size;
            _size = tree._size;
            tree._size = tmpSize;
        }
        void Clear()
        {
            clear_helper(&_root);
            _size = 0;
        }
};

};
