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


/*!
* @brief read the Bitmap image.(#! force to read grayscale image)
* @param[in] test_file : file of the image which we want to inspect.
* @return cv::Mat format
*/
cv::Mat readBitmap(const std::string& test_file);

cv::Mat show(const cv::Mat& src, const std::vector<int>& answer, const std::vector<cv::Point> point, int cropSize);

#endif  // USE_OPENCV