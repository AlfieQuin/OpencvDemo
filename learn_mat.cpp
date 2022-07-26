#include <opencv2/opencv.hpp>
#include "quickopencv.h"
#include <iostream>
#include<Windows.h>
#include<math.h>

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("E://pictures/opencv_img/BIT.jpg");
	//没图输出文字
	if (img.empty()) {
		printf("没图\n");
			;
	}
	 //namedWindow("imput", WINDOW_AUTOSIZE);
	//imshow("imput", img); //显示窗口
	//声明quickdemo
	QuickDemo qd;
	/*qd.MatCreation_Demo();  Test*/
	qd.sensors_homework();


	waitKey(114514);
	destroyAllWindows();
	return 0;


}