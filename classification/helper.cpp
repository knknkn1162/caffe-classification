#include "helper.hpp"
#include <fstream> //ifstream, ofstream
#include <istream> //istringstream
#include <algorithm>


cv::Mat ReadHelper::readBitmap(const std::string& test_file)
{
	return cv::imread(test_file, 0);
}

pairs<cv::Point, int> ReadHelper::cheat(const std::string& answer_file, const char linedelimiter)
{
	auto csvTable = readCSV(answer_file, linedelimiter);
	pairs < cv::Point, int > answer;

	for (const auto& x : csvTable)
	{
		auto p = readPoint(x.first);
		answer.push_back(std::pair<cv::Point, int>(p, x.second));
	}

	return answer;
}

pairs<std::string, int> ReadHelper::readCSV(const std::string& answer_file, const char linedelimiter)
{
	std::ifstream reading_file(answer_file, std::ios::in);
	std::string reading_line_buffer;

	pairs<std::string, int> res;

	while (std::getline(reading_file, reading_line_buffer))
	{
		std::string buf1, buf2;
		std::istringstream line_separater(reading_line_buffer);
		std::getline(line_separater, buf1, linedelimiter);
		std::getline(line_separater, buf2, linedelimiter);
		res.push_back(std::pair<std::string, int>(buf1, std::stoi(buf2)));
	}

	return res;
}

cv::Point ReadHelper::readPoint(const std::string& filename)
{
	cv::Point p;
	int x, y;
	std::istringstream iss(filename);
	char ch;
	iss >> ch>> x >> ch >> y;
	return cv::Point(x, y);
}



cv::Mat Visualizer::show(const cv::Mat& src, const pairs<cv::Point, int>& dict, int cropSize)
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
cv::Mat Visualizer::show(const cv::Mat& src, const pairs<cv::Point, int>& pred, const pairs<cv::Point, int>& answer, int cropSize)
{
	cv::Mat dst = src.clone();
	cv::cvtColor(dst, dst, CV_GRAY2RGB);
	auto red = cv::Scalar(0, 0, 200);
	auto blue = cv::Scalar(200, 0, 12);
	auto green = cv::Scalar(11, 218, 81);
	auto drawRectangle = [&](cv::Point point, cv::Scalar color, int thickness){ cv::rectangle(dst, cv::Rect(point.x, point.y, cropSize, cropSize), color, thickness, 8); };

	for (auto it = pred.begin(); it != pred.end(); ++it) {

		cv::Point point = it->first;
		auto draw = [&](cv::Scalar color, int thickness) { drawRectangle(point, color, thickness); };
		//if the answer is 1
		if (std::find(answer.begin(), answer.end(), std::pair<cv::Point, int>(it->first, 1)) != answer.end())
		{
			if (it->second == 1)
			{
				draw(green, 3);
			}
			else
			{
				// if first kind occurs
				draw(blue, 1);
			}
		}
		//answer is 0
		else
		{
			// if second kind occurs
			if (it->second == 1)
			{
				draw(red, 3);
			}
		}
	}

	return dst;
}