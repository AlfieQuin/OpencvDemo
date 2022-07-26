#include "opencv2/opencv.hpp"  
#include"opencv2/xfeatures2d.hpp"
#include <opencv2\imgcodecs\imgcodecs_c.h>


using namespace cv;
using namespace std;

int main() {
    Mat img = imread("E:\Pictures\opencv_img/test0.jpg", CV_LOAD_IMAGE_COLOR);
    Ptr<Feature2D> sift = xfeatures2d::SIFT::create();
    vector<KeyPoint> keypoints;
    Mat descriptors;

    sift->detectAndCompute(img, noArray(), keypoints, descriptors);
    drawKeypoints(img, keypoints, descriptors, Scalar(0, 255, 255));
    imshow("Result", descriptors);
    waitKey(0);

    return 0;
}