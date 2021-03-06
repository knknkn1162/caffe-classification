# caffe Classification in c++

## Preparation
+ Build caffe solution (https://github.com/Microsoft/caffe/tree/master/windows/classification.) in advance and you can get the lib. and obj. files.
+ I want to classify 2-class problem(collect image or not), so I changed the code from classification project.
+ I tried to configrate mininum projects, but you maybe reduce the size or files.

## Requirements
+ boost/property_tree(1.60.0) [read setting.ini]
+ need files "~/windows-live/libcaffe/*"

## Directory configuration

```yml
caffe-windows:
  data:
    mytest:
	  - mean.binaryproto
	  - param.json # for setting cropping image by crop.py
	  - crop.py
      answer:
        - 00001.txt # see content
		- 00002.txt
		- ..
		- 00040.txt
      data: # All images are W*H size
	    - 00001.bmp
		- 00002.bmp
		- ..
		- 00040.bmp
  windows-live:
    classification:
	- setting.ini
  example:
    lenet:
	  - deploy.prototxt
	caffemodel:
	  - mytest_iter_100000.caffemodel
	  - mytest_iter_100000.solverstate
```

### content

```txt:
x000y000.bmp 0
x015y000.bmp 0
x030y000.bmp 0
x045y000.bmp 0
x060y000.bmp 0
x075y000.bmp 0
x090y000.bmp 0
x105y000.bmp 0
x120y000.bmp 0
x135y000.bmp 0
x150y000.bmp 0
x165y000.bmp 0
```

Note) this images are all 30*30 cropped image files.

## Comment

1. Add the libcaffe.lib, caffe.lib.
2. For looking into the cv::Mat type images, you can use the VS-addin,ImageWatch(https://visualstudiogallery.msdn.microsoft.com/e682d542-7ef3-402c-b857-bbfba714f78d).

On classification project, you can get the several files and you can see brief turorial from the code, 'main.cpp'.

```cpp
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
```

