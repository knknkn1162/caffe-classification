/**
* @file   filterdef.hpp
* @brief separate definition with declaration. see also filter.hpp.
* @author   Kenta Nakajima
* @date   2016.11.16
* @version   1.0
* @bug   nothing, I think.
* @warning  this code may include some wrong descriptions
*/
template <typename ForwardIterator, typename UnaryPredicate>
int count_iterators(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
	int res = 0;
	while (first != last) {
		if (pred(*first))
		{
			res++;
		}
		++first;
	}
	return res;
}