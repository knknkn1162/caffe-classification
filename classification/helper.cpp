#include "helper.hpp"

cv::Mat readBitmap(const std::string& test_file)
{
	return cv::imread(test_file, 0);
}

cv::Mat show(const cv::Mat& src, const std::vector<int>& answer, const std::vector<cv::Point> point, int cropSize)
{
	cv::Mat dst = src.clone();
	cv::cvtColor(dst, dst, CV_GRAY2RGB);
	int size = answer.size();
	for (int i = 0; i < size; i++)
	{
		if (answer[i] == 1)
		{
			cv::Point bottom_right = cv::Point(point[i].x + cropSize, point[i].y + cropSize);
			cv::rectangle(dst, point[i], bottom_right, cv::Scalar(0, 0, 200), 3, 8);
		}
	}
	return dst;
}