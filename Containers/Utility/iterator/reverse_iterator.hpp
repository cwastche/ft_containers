#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator.hpp"

namespace ft 
{
	template <typename Iterator> 
	class reverse_iterator 
	{
		public:
			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

		// CONSTRUCTORS --------------------------------------------------------------------------------------------------------------------------------------------
			reverse_iterator () : _data() {}

explicit	reverse_iterator (iterator_type it) : _data(it) {}
			
			reverse_iterator (const reverse_iterator& rhs) : _data(rhs._data) {}
			
			template <class Iter>  
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _data(rev_it.base()) {}
		// ---------------------------------------------------------------------------------------------------------------------------------------------------------
		// GETTER --------------------------------------------------------------------------------------------------------------------------------------------------
			iterator_type base () const { return (_data); }
		// ---------------------------------------------------------------------------------------------------------------------------------------------------------
		// ADDING && SUBSTRACTING ----------------------------------------------------------------------------------------------------------------------------------
			reverse_iterator	operator- (difference_type n) const { return (reverse_iterator(_data + n) ); }

			template <typename It>
			difference_type		operator- (const reverse_iterator<It> &rhs) { return (rhs.base() - _data); }

			reverse_iterator	operator+ (difference_type n) const { return (reverse_iterator(_data - n) ); }

			reverse_iterator&	operator-= (difference_type n) 
			{
				_data += n;
				return (*this);
			}
			friend reverse_iterator operator+ (typename reverse_iterator::difference_type n, const reverse_iterator& rhs)
			{ return (reverse_iterator(rhs._data - n) ); }

			reverse_iterator& operator-- () 
			{
				++_data;
				return (*this);
			}

			reverse_iterator  operator-- (int) 
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}

			reverse_iterator& operator++ () 
			{
				--_data;
				return (*this);
			}

			reverse_iterator  operator++ (int) 
			{
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}
			
			reverse_iterator& operator+= (difference_type n) 
			{
				_data -= n;
				return (*this);
			}
		// ---------------------------------------------------------------------------------------------------------------------------------------------------------
		// ACCESS OPERATORS ----------------------------------------------------------------------------------------------------------------------------------------
			reference 	operator* () const 
			{
				iterator_type	tmp = _data;
				return (*(--tmp) );
			}

			pointer		operator-> () const { return &(operator*() ); }

			reference	operator [] (difference_type n) const { return (base()[-n - 1] ); }
		// ---------------------------------------------------------------------------------------------------------------------------------------------------------
		// RELATIONAL OPERATORS ------------------------------------------------------------------------------------------------------------------------------------			
			template <typename It> 
			bool	operator== (const reverse_iterator<It> &rhs)	const { return _data == (rhs.base()); }

			template <typename It> 
			bool	operator!= (const reverse_iterator<It> &rhs)	const { return _data != (rhs.base()); }

			template <typename It> 
			bool	operator< (const reverse_iterator<It> &rhs)		const { return _data >  (rhs.base()); }

			template <typename It> 
			bool	operator<= (const reverse_iterator<It> &rhs)	const { return _data >= (rhs.base()); }

			template <typename It> 
			bool	operator> (const reverse_iterator<It> &rhs)		const { return _data <  (rhs.base()); }

			template <typename It> 
			bool	operator>= (const reverse_iterator<It> &rhs)	const { return _data <= (rhs.base()); }

		// ---------------------------------------------------------------------------------------------------------------------------------------------------------
	
		protected:
			iterator_type	_data;

	}; // END class reverse_iterator
} // END namespace ft

#endif // REVERSE_ITERATOR_HPP