#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include<Windows.h>
#include<opencv2/xfeatures2d.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<math.h>
using namespace cv;
using namespace std;

class QuickDemo {
public:
	void colorSpace_Demo(Mat& image, Mat* datahsv, Mat* datagray);
	void MatCreation_Demo();
	void pixel_visit_Demo(Mat &image);
	void operator_Demo(Mat &image);
	void adjust_light(Mat &image);
	void tracking_bar_demo(Mat& image);
	void key_demo(Mat& image);
	void color_style_demo(Mat& image);
	void bitwise_demo(Mat& image);
	void channels_demo(Mat& image);
	void inrange_demo(Mat& image);
	void pixel_statistic_demo(Mat& image);
	void drawing_demo(Mat& image);
	void random_drawing(Mat& image);
	void polyline_drawing_demo(Mat& image);
	void mouse_drawing_demo(Mat& image);
	void norm_demo(Mat& image);
	void resize_demo(Mat& image);
	void mouseRolling_demo(Mat& image);
	void flip_demo(Mat& image);
	Mat rotate_demo(Mat& image);
	void video0_demo(Mat& image);
	void video_demo(Mat& image);
	void sift_demo(Mat& image);
	void histogram_demo(Mat& image);
	void temp_match_demo(Mat &image) ;
	void accel_video(Mat& image);
	Mat for_background(Mat  IMG, cv::Point_<int> center, int in_r, int out_r);
	Mat reduce_circle_domin(Mat  img, cv::Point_<int> c_point,int c_r );
	Mat opening_ellipse(Mat  img, cv::Point_<int> kernel_size, int interations);
	Mat closing_ellipse(Mat  img, cv::Point_<int> kernel_size, int interations);
	Mat fill_hole(Mat  img);
	pair<Point2f, float>  find_point(Mat orig_img);
	void sensors_homework();
};