#include "checker.hpp"

Checker::Checker(const cv::Mat& image, int cropSize) : image(image), cropSize(cropSize), flag(false)
{
	point.reserve(10000);
}


void Checker::all(int stride)
{
	int right = image.cols - cropSize;
	int bottom = image.rows - cropSize;
	printf("%d\n", cropSize);
	for (int y = 0; y < bottom; y += stride)
	{
		for (int x = 0; x < right; x += stride)
		{
			cv::Point p(x, y);
			point.push_back(p);

		}
	}
	flag = true;
}


std::vector<cv::Point> Checker::getPoints()
{
	point.shrink_to_fit();
	return point;
}


cv::Mat Checker::getImage() { return image; }


const int Checker::getCropSize() const { return cropSize; }
bool Checker::isValidate() const { return flag; }