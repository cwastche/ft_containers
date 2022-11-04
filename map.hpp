#ifndef MAP_HPP
# define MAP_HPP

# include "utils/map_utils/pair.hpp"
# include "utils/map_utils/Red_black_tree.hpp"
# include "utils/iterators/Random_access_iterator.hpp"
# include "utils/iterators/reverse_iterator.hpp"

//https://github.com/electronicarts/EASTL/blob/master/source/red_black_tree.cpp
// uses bidirectional iterator

namespace ft 
{
	template<	typename Key, 
				typename T, 
				typename Compare = std::less<Key>, 
				typename Alloc = std::allocator< ft::pair<const Key, T> > 
			>
	class map {

		public:
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef ft::pair<const Key, T>									value_type;
			typedef	Compare													key_compare;
			typedef Alloc													allocator_type;

			typedef	typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			
			typedef ft::Random_access_iterator<value_type>					iterator;
			typedef ft::Random_access_iterator<const value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator> 							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;	
			typedef typename iterator_traits<iterator>::difference_type		difference_type;
			typedef size_t 													size_type;

			typedef	Red_black_tree<Key, T, Compare, Alloc>					RBTree;
			
			class value_compare
			{   
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
				
					bool operator() (const value_type& x, const value_type& y) const 
					{ return comp(x.first, y.first); }

				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
			};
			
		// CONSTRUCTORS
explicit	map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {}
			
// 			template <class InputIterator>  
// 			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
// 			: ...
// 			{}
			
// 			map (const map& x) {}

			// ~map() {}
			// map& operator= (const map& rhs) {}


			// ITERATORS
			// iterator begin() {}
			// const_iterator begin() const {}

			// iterator end() {}
			// const_iterator end() const {}

			// reverse_iterator rbegin() {}
			// const_reverse_iterator rbegin() const {}

			// reverse_iterator rend() {}
			// const_reverse_iterator rend() const {}
			
			

			// CAPACITY
			bool 		empty()		const	{ return (_tree.empty() ); } 

			size_type 	size()		const	{ return (_tree.size() ); }

			size_type 	max_size()	const	{ return (_tree.max_size() ); }

			//ELEMENT ACCESS
			// mapped_type& operator[] (const key_type& k);
		

			// MODIFIERS
			
			pair<iterator,bool> insert (const value_type& val) 
			{
				iterator ret(_tree.insert(val) );
		
				return (make_pair(ret, true));
			}

			// iterator insert (iterator position, const value_type& val) {}
			// template <class InputIterator>  void insert (InputIterator first, InputIterator last) {}

			// void erase (iterator position) {}
			// size_type erase (const key_type& k) {}
			// void erase (iterator first, iterator last) {}

			// void swap (map& x);

			// void clear();
			

			// OBSERVERS
			// key_compare key_comp() const;
			// value_compare value_comp() const;

			// OPERATIONS
			// iterator find (const key_type& k);
			// const_iterator find (const key_type& k) const;

			// size_type count (const key_type& k) const;

			// iterator lower_bound (const key_type& k);
			// const_iterator lower_bound (const key_type& k) const;

			// iterator upper_bound (const key_type& k);
			// const_iterator upper_bound (const key_type& k) const;

			// pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
			// pair<iterator,iterator>             equal_range (const key_type& k);

		// GET ALLOCATOR
			allocator_type get_allocator() const { return (_alloc ); }
		
			

			private:
				RBTree				_tree;

				// size_type		_size;
				
				allocator_type	_alloc;

				// key_compare		_comp;

	}; // END class map


// parsing through tree
// Go as far left from this node as you can.
// i.e. find the minimum node in this subtree
// Node* Leftmost(Node* node)
// {
//     if (node == nullptr)
//         return nullptr;
//     while (node->left != nullptr)
//         node = node->left;
//     return node;
// }

// // Start iterating from a root node
// Node* First(Node* root)
// {
//     return Leftmost(root);
// }

// // The iteration is current at node.  Return the next node
// // in value order.
// Node* Next(Node* node)
// {
//     // Make sure that the caller hasn't failed to stop.
//     assert(node != nullptr);

//     // If we have a right subtree we must iterate over it,
//     // starting at its leftmost (minimal) node.

//     if (node->right != nullptr)
//         return Leftmost(node->right);
    
//     // Otherwise we must go up the tree

//     Node* parent = node->parent;
//     if (parent == nullptr)
//         return nullptr;

//     // A node comes immediately after its left subtree

//     if (node == parent->left)
//         return parent;

//     // This must be the right subtree!
//     assert(node == parent->right);

//     // In which case we need to go up again, looking for a node that is
//     // its parent's left child.

//     while (parent != nullptr && node != parent->left)
//     {
//         node = parent;
//         parent = node->parent;
//     }

//     // We should be at a left child!
//     assert(parent == nullptr || node == parent->left);

//     // And, as we know, a node comes immediately after its left subtree

//     return parent;
// }
// *********************************************************************************

} // END namespace ft

#endif // MAP_HPP