#ifndef ENABLE_IF
# define ENABLE_IF

namespace ft 
{
	template <bool Cond, class T = void> 
	struct enable_if {};

	template<class T> 
	struct enable_if<true, T> 
	{ 
		typedef T type; 
	};
//-------------------------------------------------------------------
// Base template, defaults to false
	template <typename T> 
	struct is_integral { static const bool value = false; };

// Specializations for integral types
	template <>
	struct is_integral<bool> { static const bool value = true; };

	template <>
	struct is_integral<char> { static const bool value = true; };

	template <>
	struct is_integral<signed char> { static const bool value = true; };

	template <>
	struct is_integral<short int> { static const bool value = true; };

	template <>
	struct is_integral<int> { static const bool value = true; };

	template <>
	struct is_integral<long int> { static const bool value = true; };

	template <>
	struct is_integral<long long int> { static const bool value = true; };

	template <>
	struct is_integral<unsigned char> { static const bool value = true; };

	template <>
	struct is_integral<unsigned short int> { static const bool value = true; };

	template <>
	struct is_integral<unsigned int> { static const bool value = true; };

	template <>
	struct is_integral<unsigned long int> { static const bool value = true; };

	template <>
	struct is_integral<unsigned long long int> { static const bool value = true; };

} // END namespace ft

#endif //ENABLE_IF