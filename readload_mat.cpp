#include <opencv2/opencv.hpp>
#include "quickopencv.h"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("E:/pictures/opencv_img/test.jpg");
	//没图输出文字
	if (img.empty()) {
		printf("没图\n");
		;
	}
	//声明quickdemo
	QuickDemo qd;
	qd.MatCreation_Demo();

	//创建窗口
	//namedWindow("imput image", WINDOW_FREERATIO);
	//imshow("imput image", img); //显示窗口
	waitKey(114514);
	destroyAllWindows();
	return 0;


}