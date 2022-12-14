#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <stdexcept>

# include "Utility/iterator/Random_access_iterator.hpp"
# include "Utility/utils/enable_if.hpp"
# include "Utility/iterator/reverse_iterator.hpp"
# include "Utility/utils/Utility_functions.hpp"
# include "Utility/iterator/iterator.hpp"

namespace ft 
{	
	template<	typename T,
				typename Alloc = std::allocator<T>
			>  
	class vector 
	{
		public:
			typedef T 											value_type;
			typedef Alloc										allocator_type;

			typedef T&											reference;
			typedef	const T&									const_reference;
			
			typedef	T*											pointer;
			typedef	const T*									const_pointer;

			typedef	size_t										size_type;
			typedef ptrdiff_t									difference_type;
			
			typedef ft::Random_access_iterator<T>				iterator;
			typedef ft::Random_access_iterator<T, true>			const_iterator;
			
			typedef ft::reverse_iterator<iterator> 				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;	

		// CONSTRUCTORS ------------------------------------------------------------------------------------------------------
explicit	vector (const allocator_type& alloc = allocator_type())
			: _data(NULL), _alloc(alloc), _capacity(0), _size(0) 
			{
				_data = _alloc.allocate(0);
			}
			
explicit	vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: _data(NULL), _alloc(alloc), _capacity(0), _size(0) { resize(n, val); }
			
			template <typename Iterator>
			vector (Iterator first, 
					typename enable_if<!is_integral<Iterator>::value, Iterator>::type last, 
					const allocator_type& alloc = allocator_type() ) 
			: _data(NULL), _alloc(alloc), _capacity(0), _size(0) 
			{
				reserve(ft::distance(first, last) + 1);
				for ( ; first != last; first++, _size++)
					_data[_size] = *first;
			}
			
			vector (const vector& rhs)
			: _alloc(rhs._alloc), _capacity(rhs._capacity), _size(rhs._size)
			{
				_data = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_data[i] = rhs._data[i];
			}
		// DESTRUCTOR --------------------------------------------------------------------------------------------------------
			~vector() 
			{
				clear();
				if (_capacity)
					_alloc.deallocate(_data, _capacity);
			}
		// ASSIGMENT OPERATOR ------------------------------------------------------------------------------------------------
			vector&	operator= (const vector& rhs) 
			{
				if (this != &rhs) 
				{
					clear();
					if (_capacity < rhs.capacity())
						reserve(rhs.capacity());
					assign(rhs.begin(), rhs.end());
				}
  				return (*this);
			}
		// -------------------------------------------------------------------------------------------------------------------
		// ITERATORS ---------------------------------------------------------------------------------------------------------
     		iterator				begin ()			{ return ( iterator(_data) ); }
			const_iterator			begin ()	const	{ return ( const_iterator(_data) ); }

			iterator 				end ()				{ return ( iterator(&_data[ _size ]) ); }
			const_iterator			end ()		const	{ return ( const_iterator(&_data[ _size ]) ); }
			
			reverse_iterator		rbegin ()			{ return ( reverse_iterator( end() ) ); }
			const_reverse_iterator	rbegin ()	const	{ return ( const_reverse_iterator( end() ) ); }

			reverse_iterator		rend ()				{ return ( reverse_iterator( begin() ) ); }
			const_reverse_iterator	rend ()		const	{ return ( const_reverse_iterator( begin() ) ); }
		// -------------------------------------------------------------------------------------------------------------------
		// CAPACITY -----------------------------------------------------------------------------------------------------------
			size_type		size ()				const	{ return (_size); }
			size_type		max_size ()			const	{ return (_alloc.max_size() ); }
			size_type		capacity ()			const	{ return (_capacity); }
			allocator_type	get_allocator ()	const	{ return (_alloc); }
			bool			empty ()			const	{ return (_size == 0); }

			void			reserve (size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector");
				if (n > _capacity) 
				{
					pointer		prev_data 		= _data;
					size_type	prev_capacity	= _capacity;
					
					_data = _alloc.allocate(n);
					if (_data != prev_data)
					{
						for (size_type i = 0; i < _size; i++)
						{
							_alloc.construct(_data + i, prev_data[i]);
							_alloc.destroy(prev_data + i);
						}
					}
					_alloc.deallocate(prev_data, prev_capacity);
					_capacity = n;
				}				
			}

			void			resize (size_type n, value_type val = value_type()) 
			{
				if (n < _size) 
				{
					while (n < _size)
						pop_back();
				}
				else if (n > _size) 
				{
                    size_type prev_size = _size;
                    if (n > _capacity)
                		reserve(n);
                    for (size_type  i = prev_size; i < n; i++)
                        _alloc.construct(_data + i, val);
                    _size = n;
                }
			}
		// -------------------------------------------------------------------------------------------------------------------
		// ELEMENT ACCESS ----------------------------------------------------------------------------------------------------
			reference 			operator[] (size_type n)			{ return ( _data[n] ); }
			const_reference		operator[] (size_type n)	const	{ return ( _data[n] ); }

			reference 			front ()							{ return ( _data[0] ); }
			const_reference		front ()					const	{ return ( _data[0] ); }

			reference			back ()								{ return ( _data[ _size - 1] ); }
			const_reference 	back ()						const	{ return ( _data[ _size - 1] ); }
		
			reference 			at ( size_type n ) 
			{
				if ( n > _size )
					throw std::out_of_range("ft::vector::at");
				return ( _data[n] );
			}

			const_reference 	at ( size_type n ) const 
			{
				if ( n > _size )
					throw std::out_of_range("ft::vector::at");
				return ( _data[n] );
			}
		// -------------------------------------------------------------------------------------------------------------------
		// MODIFIERS ---------------------------------------------------------------------------------------------------------
		// ---------- INSERTION ----------------------------------------------------------------------------------------------
			template <class InputIterator>  
			void		assign (InputIterator first, 
								typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last) 
			{
				clear();
				reserve(ft::distance(first, last) + 1);
				for (size_type i = 0; first != last; first++, i++, _size++)
					_data[i] = *first;
			}
			
			void		assign (size_type n, const value_type& val) 
			{
				clear();
				resize(n, val);
			}

			void		push_back ( const value_type& val ) 
			{
				if ( _capacity <= _size ) 
				{
					if (_size == 0)
						reserve(1);
					else
						reserve(_size * 2);
				}
				_data[_size] = val;
				_size++;
			}

			iterator	insert (iterator position, const value_type& val) 
			{
				size_type	dist		= ft::distance(begin(), position);
				size_type	prev_size	= _size;

				if (_size == 0) 
				{
					resize(1, val);
					return (iterator(_data));
				}

				if (_capacity < _size + 1)
					reserve(_capacity * 2);

				for (; prev_size > dist; prev_size--)
					_data[prev_size] = _data[prev_size - 1];
				_data[prev_size] = val;
				_size += 1;
				return (iterator(_data + dist));
			}

			void		insert (iterator position, size_type n, const value_type& val) 
			{
				size_type	dist		= ft::distance(begin(), position);
				size_type	i 			= _size + n - 1;

				if (_capacity < _size + n)
				{
					if (_capacity * 2 > _size + n)
						reserve(_capacity * 2);
					else
						reserve(_size + n);
				}
				if (n)
				{
					_size += n;
					for (; i - n + 1 > dist; i--)
						_data[i] = _data[i - n];
					for (; n > 0; i--, n--)
						_data[i] = val;
				}
			}

			template <typename InputIterator>    
			void		insert (iterator position, 
								InputIterator first, 
								typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last) 
			{
				size_type	dist		= ft::distance(begin(), position);
				size_type	n 			= ft::distance(first, last);
				size_type	i 			= _size + n - 1;

				if (_capacity < _size + n)
				{
					if (_capacity * 2 > _size + n)
						reserve(_capacity * 2);
					else
						reserve(_size + n);
				}
				if (n)
				{
					_size += n;
					for (; i - n + 1 > dist; i--)
						_data[i] = _data[i - n];
					for (; first != last; i--)
					{
						last--;
						_data[i] = *last;
					}
				}
			}
		// ---------- DELETION -------------------------------------------------------------------------------------------
			iterator	erase (iterator position) 
			{
				iterator ret = position;
				_alloc.destroy(&(*position) );
				_size -= 1;	
				for(; position != end(); position++)
					*position = *(position + 1);
				return (ret);
			}

			iterator	erase (iterator first, iterator last) 
			{
				size_type	start = ft::distance(begin(), first);
				size_type	rem	= _size - ft::distance(first, last);

				for (; first != last; first++, _size--)
					_alloc.destroy(&(*first) );
				for(size_type i = 0; rem > 0; first++, i++, rem--)
					_data[start + i] = *first;
				return (iterator(&_data[start]));
			}

			void		pop_back () 
			{
				_alloc.destroy( &(_data[_size - 1]) );
				_size--;
				if (!_size)
					_data = 0;
			}

			void		clear () 
			{
				for (size_type i = 0; i < _size; i++)
						_alloc.destroy(&(_data[i]));
				_size = 0;
			}
		// ---------- SWAP ------------------------------------------------------------------------------------------------------------------
			void		swap (vector& rhs) 
			{
				pointer			tmp_data		=	_data;
				allocator_type	tmp_alloc		=	_alloc;
				size_type		tmp_capacity	=	_capacity;
				size_type		tmp_size		=	_size;

				_data		= rhs._data;
				_alloc		= rhs._alloc;
				_capacity	= rhs._capacity;
				_size		= rhs._size;

				rhs._data		= tmp_data;
				rhs._alloc		= tmp_alloc;
				rhs._capacity	= tmp_capacity;
				rhs._size		= tmp_size;
			}
		// -------------------------------------------------------------------------------------------------------------------
		// RELATIONAL OPERATORS ----------------------------------------------------------------------------------------------
			friend bool operator== ( const vector& lhs, const vector& rhs )
			{
				if (lhs.size() == rhs.size())
					return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
				return (false);
			}
			
			friend bool operator<  ( const vector& lhs, const vector& rhs )
			{
				return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); 
			}
  
			friend bool operator!= ( const vector& lhs, const vector& rhs ) { return (!(lhs == rhs)); }
			friend bool operator<= ( const vector& lhs, const vector& rhs ) { return (!(rhs < lhs)); }
			friend bool operator>  ( const vector& lhs, const vector& rhs ) { return (rhs < lhs); }
			friend bool operator>= ( const vector& lhs, const vector& rhs ) { return (!(lhs < rhs)); }
		// -------------------------------------------------------------------------------------------------------------------

		private:
			pointer			_data;
			allocator_type	_alloc;
			size_type		_capacity;
			size_type		_size;

	}; // END class vector

	// -------------------------------------------------------------------------------------------
	template <class T, class Alloc>  
	void swap (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs) 
	{ 
		lhs.swap(rhs); 
	}

} // END namespace ft

#endif // VECTOR_HPP