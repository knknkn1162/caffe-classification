#include "checker.hpp"
#include "filter.hpp"

Checker::Checker(const cv::Mat& image, int cropSize) : image(image), cropSize(cropSize), flag(false)
{
	point.reserve(10000);
}


cv::Mat Checker::generateCroppedImage(const cv::Point& point)
{
	return image(cv::Rect(point.x, point.y, cropSize, cropSize));
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


void Checker::filter(int stride, std::function<bool(unsigned char)> func, int threshold)
{
	int btm = image.rows - cropSize;
	int right = image.cols - cropSize;
	for (int x = 0; x < right; x += stride)
	{
		for (int y = 0; y < btm; y += stride)
		{
			cv::Point p(x, y);
			cv::Mat croppedImage = generateCroppedImage(p);
			if (count_iterators(croppedImage.begin<unsigned char>(), croppedImage.end<unsigned char>(), func) >= threshold)
			{
				point.push_back(p);
			}
		}
	}
}


std::vector<cv::Point> Checker::getPoints()
{
	point.shrink_to_fit();
	return point;
}


cv::Mat Checker::getImage() { return image; }


const int Checker::getCropSize() const { return cropSize; }
bool Checker::isValidate() const { return flag; }