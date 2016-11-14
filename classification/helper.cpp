#include "helper.hpp"

cv::Mat readBitmap(const std::string& test_file)
{
	return cv::imread(test_file, 0);
}

cv::Mat show(const cv::Mat& src, const dictionary<cv::Point, int>& dict, int cropSize)
{
	cv::Mat dst = src.clone();
	cv::cvtColor(dst, dst, CV_GRAY2RGB);

	for (auto it = dict.begin(); it != dict.end(); ++it) {
		if (it->second == 1)
		{
			cv::Point point = it->first;
			cv::Point bottom_right = cv::Point(point.x + cropSize, point.y  + cropSize);

			cv::rectangle(dst, point, bottom_right, cv::Scalar(0, 0, 200), 3, 8);
		}
	}
	return dst;
}