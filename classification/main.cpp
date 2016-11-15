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

#include <sstream>
#include <iostream>
#include <iomanip>

#include "checker.hpp"
#include "lenetclassifier.hpp"
#include "helper.hpp"

//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/ini_parser.hpp>


//usage
int main(void)
{

	const string directory = "C:\\dev\\caffe\\caffe-windows";

	const string model_file = directory + "\\examples\\mytest\\lenet\\deploy.prototxt";
	const string trained_file = directory + "\\examples\\mytest\\lenet\\caffemodel\\mytest_iter_100000.caffemodel";
	const string mean_file = directory + "\\data\\mytest\\mean.binaryproto";

	//const string test_file = directory + "\\data\\mytest\\data\\040.bmp";
	const int fileNum = 40;
	const string test_dir = directory + "\\data\\mytest\\data";
	//prepare cropped - class number in advance.
	//const string answer_file = directory + "\\data\\mytest\\answer\\answer.txt";

	//create classifier
	LenetClassifier lenet(model_file, trained_file, mean_file);

	for (int i = 1; i <= fileNum; i++)
	{
		ostringstream oss;
		oss << std::setfill('0') << std::setw(5) << std::right << i;
		string test_file = directory + oss.str() + ".bmp";

		//set env/image
		cv::Mat image = ReadHelper::readBitmap(test_file);
		const int cropSize = 30;
		Checker checker(image, cropSize);

		//checker.all(stride);
		// or you can set lambda function:
		int stride = cropSize / 2;
		int backgroundThreshold = 50;
		//Checker::filter(int stride, std::function<bool(unsigned char)> func, int threshold)
		checker.filter(stride, [=](uchar u) { return u >= backgroundThreshold; }, cropSize * cropSize * 0.25);

		//predict
		lenet.predict(&checker);

		//answer
		auto ans = lenet.getAnswer();
		auto point = checker.getPoints();
		pairs<cv::Point, int> pred(ans.size());
		for (int i = 0; i < ans.size(); i++)
		{
			pred[i] = std::pair<cv::Point, int>(point[i], ans[i]);
		}

		//load answer_file(to evalate)
		string answer_file = directory + "\\answer\\" + oss.str() + ".txt";
		auto answer = ReadHelper::cheat(answer_file, ' ');

		//compare  prediction with answer. Check this with ImageWatch!!
		cv::Mat dst = Visualizer::show(image, pred, answer, checker.getCropSize());

	}

	return 0;
}
#else
int main(int argc, char** argv) {
	LOG(FATAL) << "This example requires OpenCV; compile with USE_OPENCV.";
}
#endif  // USE_OPENCV

