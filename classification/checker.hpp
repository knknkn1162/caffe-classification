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

	/*!
	* @brief decide whether top-left point of the croppedImage is contained or not.
	* @param[in] image (already cropped)
	* @param[in] transform image pointer to int.
	*/
	template<typename Iterator>
	int isContain(const cv::Mat& image, std::function<Iterator(int)> func);
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
	* @param[in] stride
	* @param[in] pred
	* @param[in] count threshold (e.g. 30*30 sized cropped Image consists of 900pixels)
	*/
	void filter(int stride, std::function<bool(unsigned char)> func, int threshold);

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

