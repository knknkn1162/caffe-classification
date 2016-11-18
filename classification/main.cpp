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

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>


//usage
int main(void)
{
	//read setting.ini and put the data.
	boost::property_tree::ptree pt;
	read_ini("..\\setting.ini", pt);

	string directory = pt.get_optional<std::string>("Root.directory").get();

	const string model_file = directory + pt.get<std::string>("Model.path");
	const string trained_file = directory + pt.get<std::string>("Train.path");
	const string mean_file = directory + pt.get<std::string>("Mean.path");


	const string test_dir = directory + pt.get<std::string>("Check.test");
	const string answer_dir = directory + pt.get<std::string>("Check.answer");

	const string save_dir = directory + pt.get<std::string>("Check.save");

	const int fileNum = pt.get<int>("Check.number");

	//create classifier
	LenetClassifier lenet(model_file, trained_file, mean_file);

	for (int i = 1; i <= fileNum; i++)
	{
		ostringstream oss;
		oss << std::setfill('0') << std::setw(5) << std::right << i;
		string test_file = test_dir + "\\" +oss.str() + ".bmp";

		//set env/image
		cv::Mat image = ReadHelper::readBitmap(test_file);
		const int cropSize = 30;
		Checker checker(image, cropSize);

		//checker.all(stride);
		// or you can set lambda function:
		int stride = cropSize / 2;
		int backgroundThreshold = 50;
		//type of std::function<bool(unsigned char)>
		using Type = unsigned char;
		checker.filter<Type>(stride, [=](Type u) { return u >= backgroundThreshold; }, cropSize * cropSize * 0.25);

		//predict
		lenet.predict(&checker);

		//answer
		auto ans = lenet.getAnswer();
		auto point = checker.getPoints();
		pairs<cv::Point, int> prediction(ans.size());
		for (int i = 0; i < ans.size(); i++)
		{
			prediction[i] = std::pair<cv::Point, int>(point[i], ans[i]);
		}

		//load answer_file(to evalate)
		std::string answer_file = answer_dir + "\\" + oss.str() + ".txt";
		auto answer = ReadHelper::cheat(answer_file, ' ');

		//compare  prediction with answer. Check this with ImageWatch!!
		cv::Mat dst = Visualizer::show(image, prediction, answer, checker.getCropSize());

		// save the image
		const string save_file = save_dir +"\\" + oss.str() + ".bmp";
		cv::imwrite(save_file, dst);
	}

	return 0;
}
#else
int main(int argc, char** argv) {
	LOG(FATAL) << "This example requires OpenCV; compile with USE_OPENCV.";
}
#endif  // USE_OPENCV

