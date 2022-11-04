#ifndef STACK_HPP
# define STACK_HPP

# include "vector"

namespace ft 
{

	template <	typename T,
				typename Container = ft::vector<T>
			 >
	class stack 
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		// Constructor
			// explicit keyword : cannot be used for implicit conversions and copy-initialization. 
			// More info https://en.cppreference.com/w/cpp/language/explicit
			explicit stack (const container_type& ctnr = container_type () ) : _c(ctnr) {}
		
		// Member Functions 
			bool 				empty ()	const				{ return (_c.empty() ); }
			size_type 			size ()		const				{ return (_c.size() ); }

			value_type& 		top ()							{ return (_c.back() ); }
			const value_type& 	top ()		const 				{ return (_c.back() ); }

			void 				push (const value_type& val)	{ _c.push_back(val); }
			void 				pop () 							{ _c.pop_back(); }
		// --------------------------------------------------------------------------------------------------------

		// RELATIONAL OPERATORS 
			// Friend keyword: grants operator overloads access to private/protected members of underlying container
			template <class Tx, class Containerx>
			friend  bool operator== (const stack<Tx,Containerx>& lhs, const stack<Tx,Containerx>& rhs);

			template <class Tx, class Containerx>
			friend  bool operator!= (const stack<Tx,Containerx>& lhs, const stack<Tx,Containerx>& rhs);

			template <class Tx, class Containerx>
			friend  bool operator<  (const stack<Tx,Containerx>& lhs, const stack<Tx,Containerx>& rhs);

			template <class Tx, class Containerx>
			friend  bool operator<= (const stack<Tx,Containerx>& lhs, const stack<Tx,Containerx>& rhs);
			
			template <class Tx, class Containerx>
			friend  bool operator>  (const stack<Tx,Containerx>& lhs, const stack<Tx,Containerx>& rhs);

			template <class Tx, class Containerx>
			friend  bool operator>= (const stack<Tx,Containerx>& lhs, const stack<Tx,Containerx>& rhs);
		// --------------------------------------------------------------------------------------------------------
		
		protected:
			container_type	_c;

	}; // END class stack

// Non-member RELATIONAL OPERATORS
// Calls the relational operator between the underlying containers
	template <class T, class Container>  
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{ return (lhs._c == rhs._c); }

	template <class T, class Container>  
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{ return (lhs._c != rhs._c); }

	template <class T, class Container>  
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{ return (lhs._c < rhs._c); }

	template <class T, class Container>  
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{ return (lhs._c <= rhs._c); }
	
	template <class T, class Container>  
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{ return (lhs._c > rhs._c); }

	template <class T, class Container>  
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{ return (lhs._c >= rhs._c); }
// ------------------------------------------------------------------------------------------------------------------

}  // END namespace ft

#endif // STACK_HPP