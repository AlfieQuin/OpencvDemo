#include <opencv2/opencv.hpp>
#include "quickopencv.h"
#include <iostream>
#include<Windows.h>
#include<math.h>

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("E://pictures/opencv_img/BIT.jpg");
	//ûͼ�������
	if (img.empty()) {
		printf("ûͼ\n");
			;
	}
	 //namedWindow("imput", WINDOW_AUTOSIZE);
	//imshow("imput", img); //��ʾ����
	//����quickdemo
	QuickDemo qd;
	/*qd.MatCreation_Demo();  Test*/
	qd.sensors_homework();


	waitKey(114514);
	destroyAllWindows();
	return 0;


}