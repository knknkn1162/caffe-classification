#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <iterator>

/*!
* @brief count with 
* @param[in] point position is top-left.
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