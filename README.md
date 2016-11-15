# caffe Classification in c++

## Preparation
+ Build caffe solution (https://github.com/Microsoft/caffe/tree/master/windows/classification.) in advance and you can get the lib. and obj. files.
+ I want to classify 2-class problem(collect image or not), so I changed the code from 
+ need files "~/windows-live/libcaffe/*"
+ I tried to configrate mininum projects, but you maybe reduce the size or files.

## Comment

1. Add the libcaffe.lib, caffe.lib.
2. For looking into the cv::Mat type images, you can use the VS-addin,ImageWatch(https://visualstudiogallery.msdn.microsoft.com/e682d542-7ef3-402c-b857-bbfba714f78d).

On classification project, you can get the several files and you can see brief turorial from the code, 'main.cpp'.

```cpp

//usage
int main(void)
{

	const string directory = "C:\\dev\\caffe\\caffe-windows";

	const string model_file = directory + "\\examples\\mytest\\lenet\\deploy.prototxt";
	const string trained_file = directory + "\\examples\\mytest\\lenet\\caffemodel\\mytest_iter_100000.caffemodel";
	const string mean_file = directory + "\\data\\mytest\\mean.binaryproto";

	const string test_file = directory + "\\data\\mytest\\data\\040.bmp";

	const string answer_file = directory + "\\data\\mytest\\answer.txt";

	//create classifier
	LenetClassifier lenet(model_file, trained_file, mean_file);

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

	//load answer_file
	auto answer = ReadHelper::cheat(answer_file, ' ');
	//compare  prediction and answer. Check this with ImageWatch!!
	cv::Mat dst = Visualizer::show(image, pred, answer,  checker.getCropSize());

	return 0;
}
```

