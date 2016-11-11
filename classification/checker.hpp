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

class Checker
{
private:
	cv::Mat image;
	std::vector<cv::Point> point;
	const int cropSize;
	bool flag;
public:

	/*!
	* @brief ctor
	* @param[in] image 
	* @param[in] cropSize
	*/
	Checker(const cv::Mat& image, int cropSize);

	/*!
	* @brief stride the ROI, so we get
	* @param[in] stride
	*/
	void all(int stride);

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

