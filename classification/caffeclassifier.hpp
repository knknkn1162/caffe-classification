/**
* @file   caffeclassifier.hpp
* @brief rename classification.cpp of classification project. see https://github.com/Microsoft/caffe.
* @author   Microsoft
* @date   2016.11.10
* @version   1.0
* @bug   nothing, I think.
* @warning  this code may include some wrong descriptions
*/
#pragma once
#include <caffe/caffe.hpp>
#ifdef USE_OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif  // USE_OPENCV
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#ifdef USE_OPENCV
using namespace caffe;  // NOLINT(build/namespaces)
using std::string;


class Classifier {
public:

	/*!
	* @brief ctor
	*/
	Classifier(const string& model_file,
		const string& trained_file,
		const string& mean_file);

	//std::vector<Prediction> Classify(const cv::Mat& img, int N = 5);

	/*!
	* @brief predict with regard to img.
	*/
	std::vector<float> Predict(const cv::Mat& img);
private:

	/*!
	* @brief setmean
	*/
	void SetMean(const string& mean_file);



	/*!
	* @brief Wrap the input layer of the network in separate cv::Mat objects
	* (one per channel). This way we save one memcpy operation and we
	* don't need to rely on cudaMemcpy2D. The last preprocessing
	* operation will write the separate channels directly to the input
	* layer.
	*/
	void WrapInputLayer(std::vector<cv::Mat>* input_channels);

	/*!
	* @brief Load the mean file in binaryproto format
	*/
	void Preprocess(const cv::Mat& img,
		std::vector<cv::Mat>* input_channels);

private:
	/*!
	* @brief generated from model_file and trained_file.
	* Net -> Layers -> Blobs.
	*/
	shared_ptr<Net<float> > net_;
	/*!
	* @brief generated from net_
	*/
	cv::Size input_geometry_;
	/*!
	* @brief grayscale : 1, RGB : 3
	*/
	int num_channels_;
	/*!
	* @brief generated from mean_file.
	*/
	cv::Mat mean_;

};

/*!
* @brief printf(Net)
*/
void printNet(caffe::Net<float>* net_);

///*!
//* @brief PairCompare
//*/
//static bool PairCompare(const std::pair<float, int>& lhs,
//	const std::pair<float, int>& rhs);
//static std::vector<int> Argmax(const std::vector<float>& v, int N);

#endif // USE_OPENCV