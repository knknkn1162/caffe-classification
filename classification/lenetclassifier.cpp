#include "lenetclassifier.hpp"


LenetClassifier::LenetClassifier(const string& model_file,
	const string& trained_file,
	const string& mean_file)
	: classifier(model_file, trained_file, mean_file)
{
	answer.reserve(10000);
}


void LenetClassifier::predict(Checker* checker)
{
	reset();
	int size = checker->getCropSize();
	auto img = checker->getImage();

	auto point = checker->getPoints();
	for (const auto p : point)
	{
		// cf) cv::Rect(int _x, int _y, int _width, int _height)
		cv::Mat croppedImage = img(cv::Rect(p.x, p.y, size, size));
		std::vector<float> output = classifier.Predict(croppedImage);

		int argMax = output[0] > output[1] ? 0 : 1;
		printf("(%d, %d), prob => (%f,%f) :: eval => # %d\n", p.x, p.y, output[0], output[1], argMax);
		answer.push_back(argMax);
	}
	answer.shrink_to_fit();
}

std::vector<int> LenetClassifier::getAnswer() { return answer; }

void LenetClassifier::reset()
{
	answer = vector<int>();
	answer.reserve(10000);
}
