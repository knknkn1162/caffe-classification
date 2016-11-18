/**
* @file   checker.hpp
* @brief buffering the left-upper points of image which we want to classify.
* @author   Kenta Nakajima
* @date   2016.11.10
* @version   1.0
* @bug   nothing, I think.
* @warning  this code may include some wrong descriptions
*/
#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <functional>
#include "filter.hpp" //for Checker::filter

class Checker
{
private:
	cv::Mat image;
	std::vector<cv::Point> point;
	const int cropSize;
	bool flag;

	/*!
	* @brief generate shape of rectangle which top-left point is given.
	* @param[in] point position is top-left.
	*/
	cv::Mat generateCroppedImage(const cv::Point& point);

public:

	/*!
	* @brief ctor
	* @param[in] image 
	* @param[in] cropSize
	*/
	Checker(const cv::Mat& image, int cropSize);

	/*!
	* @brief stride the ROI, so we get the left-top point of cropped rectangles.
	* @param[in] stride
	*/
	void all(int stride);


	/*!
	* @brief stride the ROI, filter with the function "func" and we get the integer value.
	  After all, we compare this with the given threshold.
	* @tparam Pred signature is bool(T), T is type parameter.
	* @param[in] stride
	* @param[in] pred
	* @param[in] count threshold (e.g. 30*30 sized cropped Image consists of 900pixels)
	*/
	template<typename T>
	void filter(int stride, std::function<bool(T)> func, int threshold);

	/*!
	* @brief getPoint
	* @return vector of cv::Point
	*/
	std::vector<cv::Point> getPoints();

	/*!
	* @brief get whole Image.
	* @param[in] vector of cv::Point
	*/
	cv::Mat getImage();

	/*!
	* @brief get cropSize.
	*/
	const int getCropSize() const;

	/*!
	* @brief check whether image is cropped or not.
	*/
	bool isValidate() const;
};

template<typename T>
void Checker::filter(int stride, std::function<bool(T)> func, int threshold)
{
	int btm = image.rows - cropSize;
	int right = image.cols - cropSize;
	for (int x = 0; x < right; x += stride)
	{
		for (int y = 0; y < btm; y += stride)
		{
			cv::Point p(x, y);
			cv::Mat croppedImage = generateCroppedImage(p);
			if (count_iterators(croppedImage.begin<T>(), croppedImage.end<T>(), func) >= threshold)
			{
				point.push_back(p);
			}
		}
	}
}