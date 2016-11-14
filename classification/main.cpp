/**
* @file   main.cpp
* @brief show usage how to use the LenetClassifier class.
* @author   Kenta Nakajima
* @date   2016.11.10
* @version   1.0
* @bug   nothing, I think.
* @warning  this code may include some wrong descriptions
*/
#ifdef USE_OPENCV

#include "checker.hpp"
#include "lenetclassifier.hpp"
#include "helper.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>


//usage
int main(void)
{
	const string directory = "C:\\dev\\caffe\\caffe-windows";

	const string model_file = directory + "\\examples\\mytest\\lenet\\deploy.prototxt";
	const string trained_file = directory + "\\examples\\mytest\\lenet\\caffemodel\\mytest_iter_100000.caffemodel";
	const string mean_file = directory + "\\data\\mytest\\mean.binaryproto";

	const string test_file = directory + "\\data\\mytest\\data\\040.bmp";

	//create classifier
	LenetClassifier lenet(model_file, trained_file, mean_file);

	//set env/image
	cv::Mat image = readBitmap(test_file);
	const int cropSize = 30;
	Checker checker(image, cropSize);
	int stride = cropSize / 2;
	//checker.all(stride);
	int backgroundThreshold = 50;
	checker.filter(stride, [=](uchar u) { return u >= backgroundThreshold; }, cropSize * cropSize * 0.25);

	//predict
	lenet.predict(&checker);

	//answer
	auto ans = lenet.getAnswer();
	auto point = checker.getPoints();
	dictionary<cv::Point, int> dict(ans.size());
	for (int i = 0; i < ans.size(); i++)
	{
		dict[i] = std::pair<cv::Point, int>(point[i], ans[i]);
	}

	cv::Mat dst = show(image, dict, checker.getCropSize());

	return 0;
}
#else
int main(int argc, char** argv) {
	LOG(FATAL) << "This example requires OpenCV; compile with USE_OPENCV.";
}
#endif  // USE_OPENCV

