#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <iterator>
#include "filterdef.hpp"

/*!
* @brief count with 
* @param[in] first ForwardIterator
* @param[in] last ForwardIterator
* @param[in] pred predicate function
*/
template <typename ForwardIterator, typename UnaryPredicate>
int count_iterators(ForwardIterator first, ForwardIterator last, UnaryPredicate pred);