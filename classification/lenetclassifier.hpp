/**
* @file   lenetclassifier.hpp
* @brief Classifiy images what you inspect with lenet model.
* @author   Kenta Nakajima
* @date   2016.11.10
* @version   1.0
* @bug   nothing, I think.
* @warning  this code may include some wrong descriptions
*/
#pragma once
#include "caffeclassifier.hpp"
#include "checker.hpp"

class LenetClassifier
{
private:
	Classifier classifier;
	std::vector<int> answer;

	/*!
	* @brief reset answer that was buffered.
	*/
	void reset();
public:
	/*!
	* @brief ctor
	* @param[in] model_file : format 'deploy.prototxt'
	* @param[in] trained_file : format 'out.caffemodel'
	* @param[in] mean_file : format 'mean.binaryproto'
	*/
	LenetClassifier(const string& model_file,
		const string& trained_file,
		const string& mean_file);

	/*!
	* @brief predict the cropped Images.
	*/
	void predict(Checker* checker);

	/*!
	* @brief get the answers  correspoinding to checker->getPoints().
	* @return vector of answers correspoinding to checker->getPoints().
	*/
	std::vector<int> getAnswer();
};
