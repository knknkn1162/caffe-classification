/**
* @file   helper.hpp
* @brief write helper functions. e.g) transfom various format to cv:Mat.
* @author   Kenta Nakajima
* @date   2016.11.10
* @version   1.0
* @bug   nothing, I think.
* @warning  this code may include some wrong descriptions
*/
#pragma once

#ifdef USE_OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>

template<typename T, typename U>
using dictionary = std::vector<std::pair<T, U>>;

/*!
* @brief read the Bitmap image.(#! force to read grayscale image)
* @param[in] test_file : file of the image which we want to inspect.
* @return cv::Mat format
*/
cv::Mat readBitmap(const std::string& test_file);

/*!
* @brief draw squares with src image where we decide cropImage as label-1.
* @param[in] src : whole images
* @return dict : key : left-up point, value : class number
* @return size of trained or tested images which are cropped.
*/
cv::Mat show(const cv::Mat& src, const dictionary<cv::Point, int>& dict, int cropSize);


#endif  // USE_OPENCV