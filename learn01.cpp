#include <opencv2/opencv.hpp>
#include "quickopencv.h"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("E:/pictures/opencv_img/test0.jpg");
	//ûͼ�������
	if (img.empty()) {
		printf("ûͼ\n");
		return -1
		;
	}

	//����quickdemo
	QuickDemo qd;
	qd.colorSpace_Demo(img);

	//��������
	//namedWindow("imput image", WINDOW_FREERATIO);
	//imshow("imput image", img); //��ʾ����
	waitKey(114514);
	destroyAllWindows();
	return 0 ;


}