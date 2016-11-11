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

```cpp: main.cpp
int main(void)
{
    //set the prototxt, caffemodel, binaryproto files
	const string directory = "C:\\dev\\caffe\\caffe-windows";

	const string model_file = directory + "\\examples\\mytest\\lenet\\deploy.prototxt";
	const string trained_file = directory + "\\examples\\mytest\\lenet\\caffemodel\\mytest_iter_100000.caffemodel";
	const string mean_file = directory + "\\data\\mytest\\mean.binaryproto";
    
    //set the prototxt, caffemodel, binaryproto files
	const string test_file = directory + "\\data\\mytest\\data\\040.bmp";

	//create classifier
	LenetClassifier lenet(model_file, trained_file, mean_file);

	//set env/image 
    //(Image size is too big, so I cropped the mesh(this code meshes 30*30)
	cv::Mat image = readBitmap(test_file);
	const int cropSize = 30;
	Checker checker(image, cropSize);
	checker.all(cropSize / 2);

	//predict
	lenet.predict(&checker);

	//answer
	auto ans = lenet.getAnswer();

    //check the images with ImageWatch.
	cv::Mat dst = show(image, ans, checker.getPoints(), checker.getCropSize());

	return 0;
}
```

