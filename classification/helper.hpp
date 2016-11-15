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
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <map>

template<typename T, typename U>
using pairs = std::vector<std::pair<T, U>>;


class ReadHelper
{
public:
	/*!
	* @brief read the Bitmap image.(#! force to read grayscale image)
	* @param[in] test_file : file of the image which we want to inspect.
	* @return cv::Mat format
	*/
	static cv::Mat readBitmap(const std::string& test_file);

	/*!
	* @brief transform csv file to pairs of cv::Point and integer(0 or 1)
	* @param[in] answer_file answerfile
	* @param[in] linedelimiter (e.g ' ' or ',' or tab)
	* @return pairs<int, pairs<cv::Point, int>>
	*/
	static pairs<cv::Point, int> cheat(const std::string& answer_file, const char linedelimiter);

private:

	/*!
	* @brief transform csv file to pairs.
	* @param[in] answer_file answerfile
	* @param[in] linedelimiter (e.g ' ' or ',' or tab)
	* @return pairs<std::string, int>
	*/
	static pairs<std::string, int> readCSV(const std::string& answer_file, const char linedelimiter);

	/*!
	* @brief transform x([0-9]{3})y([0-9]{3}) format to cv::Point(([0-9]{3}), ([0-9]{3})
	* @param[in] answer_file answerfile
	* @return pairs<std::string, int>
	*/
	static cv::Point readPoint(const std::string& filename);

};




class Visualizer
{
public:
	/*!
	* @brief draw squares with src image where we decide cropImage as label-1.
	* @param[in] src : whole images
	* @return dict : key : left-up point, value : class number
	* @return size of trained or tested images which are cropped.
	*/
	static cv::Mat show(const cv::Mat& src, const pairs<cv::Point, int>& dict, int cropSize);

	/*!
	* @brief evaluate the eval and answer
	* @param[in] src : whole images
	* @return pred : key : left-up point, value : class number(prediction)
	* @return anwser : key : left-up point, value : class number(answer)
	* @return size of trained or tested images which are cropped.
	*/
	static cv::Mat show(const cv::Mat& src, const pairs<cv::Point, int>& pred, const pairs<cv::Point, int>& answer, int cropSize);
};

#endif  // USE_OPENCV