#include "quickopencv.h"
#include<Windows.h>
#include<opencv2/xfeatures2d.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <list>
#include<algorithm>
#include<math.h>

//01转化图像格式，保存图像//

void QuickDemo::colorSpace_Demo(Mat& image,Mat* datahsv, Mat* datagray) {

	Mat gray, hsv;
	//定义灰度图与hsv图矩阵
	//将输入转化为灰度与HSV并存入矩阵中
	cvtColor(image, hsv, COLOR_BGR2HSV);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	//imshow("origin", image);
	imshow("HSV", hsv);  //显示
	imshow("灰度", gray);
	//保存
	//imwrite("E:/pictures/opencv_img/output灰0.png",gray);
	//imwrite("E:/pictures/opencv_img/outputhsv0.png", hsv);
	
	//利用指针输出多个变量
	*datahsv = hsv;
	*datagray = gray;
}  

//02创建图像 复制图像//
void  QuickDemo::MatCreation_Demo() {
	//mat m1, m2;//clone copy
	//m1 = image.clone();
	//image.copyto(m2);        深拷贝，，   只有=是浅拷贝
	// 
	//创建空白图像 
	Mat m3 = Mat::zeros(Size(400,400),CV_8UC3) ; //8位 无符号 3通道  行=8 列=8*3，
	m3 = Scalar(255,0,0);            //3个通道分别赋值 pure blue
	
										 //求矩阵的 行 列 通道
	cout << "width:" << m3.cols << "  height:" << m3.rows << "  channels:" << m3.channels() << endl;

	//cout << m3 << endl;  //打印
	
	imshow("m3", m3);


}

// 03访问读写图像的像素  /
void QuickDemo::pixel_visit_Demo(Mat& image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();  //灰度1，彩色3
	/*for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			if(dims == 1){ //灰度图
				int pv = image.at<uchar>(row, col); //读取像素值
				image.at<uchar>(row, col)= 255-pv; //
			}

			if(dims == 3){//彩色图像
				Vec3b bgr = image.at<Vec3b>(row, col);
				image.at<Vec3b>(row, col)[0] = 255-bgr[0];
				image.at<Vec3b>(row, col)[1] = 255-bgr[1];
				image.at<Vec3b>(row, col)[2] = 255-bgr[2];
			}
		}
	}*/
	//基于下标
	for (int row = 0; row < h; row++) {
		uchar  *current_row = image.ptr<uchar>(row); //获取当前行指针
		for (int col = 0; col < w; col++) {
			if (dims == 1) { //灰度图
				int pv = *current_row; //读取像素值
				*current_row++ = 255 - pv; //
			}

			if (dims == 3) {//彩色图像
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}  //基于指针  此时col与row的作用不再是寻址（第一个除外），而是计数
	imwrite("E:/pictures/opencv_img/invertest.jpg", image);
	imshow("pixel_change", image);

}

//04图像像素的算术操作
void QuickDemo::operator_Demo(Mat& image) {
	Mat dst;
	//dst = image + Scalar(50, 50, 50); // 图片变亮
	//dst = image/Scalar(2,2,2);// 图片亮度减半
	Mat m = Mat::zeros(image.size(),image.type());  //m定义尺寸
	m = Scalar(2,2,2);        //m赋值
	multiply(image,m,dst);   //dst = image*m
	
	imshow("操作",dst); //

}

//05调整亮度
/*
Mat  src, dst, m;  //输入 输出 数值
int lightness = 50;//定义初始的亮度为50 全局变量
static void ontrack(int,void*){
	m = Scalar(abs(lightness - 50), abs(lightness - 50), abs(lightness - 50));//创建调整亮度的数值
	if(lightness>=50){		
		add(src, m, dst);//定义亮度变化为加
	}
	else {
		subtract(src, m, dst);//定义亮度变化为减
	}
	imshow("亮度调整", dst);//显示调整亮度之后的图片
}
void QuickDemo::adjust_light(Mat &image) {
	namedWindow("亮度调整", WINDOW_FREERATIO);
	dst = Mat::zeros(image.size(), image.type());//图片的初始化创建一个和image大小相等，种类相同的图像
	m = Mat::zeros(image.size(), image.type());//图片的初始化创建一个和image大小相等，种类相同的图像
	int max_light = 100;
	
	src = image;//给src赋值
	createTrackbar("value_bar:","亮度调整", &lightness, max_light,ontrack);
	ontrack(50,0);

}  */ 

//06滚动条调整亮度  *point   回调函数
/*
static void on_lightness(int b, void* userdata)
{
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(b, b, b);
	addWeighted(image, 1.0, m, 0, b, dst);//融合两张图
	imshow("亮度&对比度调整", dst);
}
static void on_contrast(int b, void* userdata)
{
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, dst);//融合两张图
	imshow("亮度&对比度调整", dst);
}
void QuickDemo::tracking_bar_demo(Mat& image) {
	namedWindow("亮度&对比度调整", WINDOW_FREERATIO);
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;
	createTrackbar("Value Bar", "亮度&对比度调整", &lightness, max_value, on_lightness, (void*)(&image));
	createTrackbar("Contrast Bar", "亮度&对比度调整", &contrast_value, 200, on_contrast, (void*)(&image));
	on_lightness(50, &image);
}
*/

//07键盘响应
void QuickDemo::key_demo(Mat& image) {
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true)
	{
		char c = waitKey(100);// 停顿100ms 做视频处理都是1
		if (c == 27) { //esc 退出应用程序
			break;
		}
		if (c == 49)//key#1
		{
			cout << "you enter key #1" << endl;
			cvtColor(image, dst, COLOR_BGR2GRAY);  //按下1转化为灰度
		}
		if (c == 50)//key#1
		{
			cout << "you enter key #2" << endl;
			cvtColor(image, dst, COLOR_BGR2HSV); //按下2转化为HSV
		}
		if (c == 51)//key#1
		{
			cout << "you enter key #3" << endl;
			dst = Scalar(50, 50, 50);
			add(image, dst, dst);  //按下3提高亮度
		}
		imshow("键盘响应", dst);
		cout << c << endl;
	}
}

//08颜色表 操作 延时
void QuickDemo::color_style_demo(Mat& image) {
	int colormap[] = {
		COLORMAP_AUTUMN ,
		COLORMAP_BONE,
		COLORMAP_CIVIDIS,
		COLORMAP_COOL,
		COLORMAP_DEEPGREEN,
		COLORMAP_HOT,
		COLORMAP_HSV,
		COLORMAP_INFERNO,
		COLORMAP_JET,
		COLORMAP_MAGMA,
		COLORMAP_OCEAN,
		COLORMAP_PINK,
		COLORMAP_PARULA,
		COLORMAP_PLASMA,
		COLORMAP_RAINBOW,
		COLORMAP_SPRING,
		COLORMAP_TWILIGHT,
		COLORMAP_TURBO,
		COLORMAP_TWILIGHT,
		COLORMAP_VIRIDIS,
		COLORMAP_TWILIGHT_SHIFTED,
		COLORMAP_WINTER		
	};
	Mat dst;
	int index = 0;
	int t ;  //t为0-21的循环
	while (true)
	{
		t = index % 22; //0-21实现数据的循环
		char c = waitKey(100);// 
		if (c == 27) { //esc 退出应用程序
			break;
		}
		//if (c == 49)//key#1 按下按键1时，保存图片到指定位置
		//{
		//	cout << "you enter key #1" << endl;
		//	imwrite("E:/pictures/opencv_img/colormap0.png", dst);
		//}
		applyColorMap(image, dst, colormap[t]);//循环展示22种图片
		index++;
		imshow("循环播放", dst);
		cout << t << endl;
		Sleep(500); //延时0.5s
	}
}

//09 绘图操作 //10 逻辑操作
void QuickDemo::bitwise_demo(Mat& image) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	/*绘图*/
	 /*  参数1：源图像
	   参数2：(a,b,c,d)
	           a,b:起始位置
			   c.d:末位位置
	   参数3： 颜色
	   参数4： 负数(填充)  ()   正数(绘制)
	   参数5： 反锯齿 4 8 邻域
	   参数6：小数位数
	*/
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0); //BGR 
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0); //
	imshow("m1", m1);
	imshow("m2", m2);

	Mat dst;
	//bitwise_and(m1, m2, dst);//位操作与   *交集绿色
	//bitwise_or(m1, m2, dst);  //位操作或     +交集白色
	//bitwise_not(image, dst);//取反操作     反色
	//bitwise_xor(m1, m2, dst);//异或操作  黑 原色 蓝+红
	dst = ~image;
	imshow("像素位操作", dst);  
}

//11通道分离
void QuickDemo::channels_demo(Mat& image)
{
	vector<Mat>mv;  //创建mat类型数组
	split(image, mv);  //通道分离 BGR
	
	/*0,1,2三个通道分别代表BGR。关闭2个通道意味着开启一个通道。*/
	/* imshow("蓝色0", mv[0]);
	imshow("绿色0", mv[1]);
	imshow("红色0", mv[2]); */
	Mat dst;
	mv[1] = 0;
	mv[0] = 0;
	merge(mv, dst); //dst = 0+0+R
	imshow("红色", dst);

	Mat swapBR = Mat::zeros(image.size(), image.type());
	int from_to[] = { 0,1,1,2,2,0 };
	//赋予通道，第0->第1，第1->第2，第2->第0   
	mixChannels(&image, 1, &swapBR, 1, from_to, 3);//3表示3个通道
	imshow("通道混合", swapBR);
	//通道混合
  /* 参数1：输入矩阵，可有x张
	   参数2：x张图片
	   参数3： 输出矩阵 y张
	   参数4： y张
	   参数5： 执行from_to操作
	   参数6：3通道
	*/
}

//12图像色彩空间转换  抠图必备 copyto()两个参数应用
void QuickDemo::inrange_demo(Mat& image){
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);  //BGR->HSV 辨识度较高
	imshow("hsv", hsv);
	Mat mask;        //遮罩或者掩码
	inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);
	//35,43,46根据图片中绿色最低来确定最小值。
	//77,255,255 提取
	//参数1低范围，参数2高范围
	//将hsv中的由低到高的像素点提取出来并且存储到mask当中。提取的为白，未提取的为黑（绿幕为白）
	Mat redback = Mat::zeros(image.size(), image.type());
	redback = Scalar(40, 40, 200);
	bitwise_not(mask, mask);  //mask中背景为黑
	imshow("mask", mask);

	image.copyTo(redback, mask);//只有mask中为1白的位置的像素，将image拷贝到redback中。
	imshow("roi提取", redback);


}

//13像素统计
void QuickDemo::pixel_statistic_demo(Mat& image) {
	double minv, maxv;//定义最值
	Point minLoc, maxLoc;//定义最值地址 point 坐标类型数组
	/*分离通道*/
	vector<Mat>mv;
	split(image, mv);
	
	/*分别打印各个通道的最值*/
	for (int i = 0; i < mv.size(); i++) {
		/*此函数只能处理单通道图像*/ // 多一个参数是mask
		minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc, Mat());
		cout <<" No.channels："<<i 
			<< " min value: " << minv << " max value " << maxv << endl;
	}
	
	 //求均值 方差
	Mat mean, stddev;
	meanStdDev(image,mean,stddev); //多一个参数是mask
	cout << " mean:" << mean << std::endl;
	cout << " stddev:" << stddev << std::endl;
}

//14几何绘制
void QuickDemo::drawing_demo(Mat& image) {
	
		Rect rect; //定义矩形
		rect.x = 100;
		rect.y = 100;  //位置
		rect.width = 150;
		rect.height = 200;  //大小  
	    //等价于 rect = Rect(100,100,150,200);
		
		Mat bg = Mat::zeros(image.size(), image.type());//生成背景
		/*矩形*/
		rectangle( bg, rect, Scalar(0, 0, 255), 3, 8, 0);
		/*圆形*/
		circle(bg, Point(250, 300), 15, Scalar(255, 0, 0), 3, 8, 0);
		 /*  参数1：源图像
		   参数2： 圆心坐标
		   参数3： 颜色
		   参数4： 负数(填充)     正数(绘制线宽)
		   参数5： 反锯齿 4 8 邻域
		   参数6：小数位数
		*/	
		/*直线*/
		line(bg, Point(100, 100), Point(250, 300), Scalar(0, 255, 0), 3, LINE_AA, 0); //  LINA_AA 反锯齿
		
		RotatedRect rtt;
		rtt.center = Point(100, 100);
		rtt.size = Size(200, 100);
		rtt.angle = 0.0;
		//等价于 rtt = RotatedRect(100,100,100,200,0.0);
		/*椭圆*/
        ellipse(bg, rtt, Scalar(255, 0, 0), 2, 8);
		
		Mat dst;
		addWeighted(image, 0.7, bg, 1, 0, dst); //融合图像	


		
		
		
		imshow("绘制演示", dst);
	

}

//15随机颜色
void QuickDemo::random_drawing(Mat& image)
{
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	int w = canvas.cols;
	int h = canvas.rows;


	RNG rng(12345);
	//随机数
	/*
	    RNG可以产生3种随机数
		RNG(int seed) 使用种子seed产生一个64位随机整数，默认-1	
		RNG::gaussian( ) 产生一个高斯分布的随机数
		RNG::uniform(a, b ) 返回一个[a,b)范围的均匀分布的随机数，
		                    a,b的数据类型要一致，
							而且必须是int、float、double中的一种，
							默认是int。
		RNG::gaussian( σ) 返回一个均值为0，标准差为σ的随机数。
	   λ+ RNG::gaussian( σ) 产生均值为λ，标准差为σ的随机数，可以
	*/	
	while (true)
	{
		int c = waitKey(10);
		if (c == 27)
		{
			break;
		}
		int x1 = rng.uniform(0, w);
		int y1 = rng.uniform(0, h);  //起始位置
		int x2 = rng.uniform(0, w);
		int y2 = rng.uniform(0, h);  //结束位置 point

		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255); //赋予颜色
		canvas = Scalar(0, 0, 0);   //绘画前将画布清黑
		line(canvas, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 5, LINE_AA, 0);//line_AA表示去掉锯齿	
		imshow("随机绘制演示", canvas);
	}
}

//16 绘制多边形
void QuickDemo::polyline_drawing_demo(Mat& image)
{
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	Mat canvas2 = Mat::zeros(Size(512, 512), CV_8UC3);
	Point p1(100, 100);
	Point p2(350, 100);
	Point p3(450, 280);
	Point p4(320, 450);
	Point p5(80, 400);    
	vector<Point>pts;//将5个点装入一个容器内。
	pts.push_back(p1);//未初始化数组容量，只能用pushback操作
					  //如果初始化，可以用数组下标操作。
	pts.push_back(p2);
	pts.push_back(p3);
	pts.push_back(p4);
	pts.push_back(p5);	
	/*填充*/
	fillPoly(canvas, pts, Scalar(0, 0, 255), LINE_AA, 0);
	 /*
	参数1表示画布 / 输入，参数2表示点集，参数3颜色
	参数4表示线型/锯齿，参数5表示小数位数
	 */
	 /*描边*/
	polylines(canvas, pts, true, Scalar(255, 255, 0), 5, LINE_AA, 0);//绘制多边形
	/*
	参数1表示画布/输入，参数2表示点集，参数3表示是否闭合曲线，参数4颜色
	参数5表示线宽，参数6表示线段类型，参数7表示缩放比例 0不缩放 4为1/4
	*/
	
	/*同一个函数描边+填充 */
	vector<vector<Point>>contours;
	contours.push_back(pts);
	drawContours(canvas2, contours, -1, Scalar(0, 0, 255), -1, LINE_AA);
	drawContours(canvas2, contours, -1, Scalar(0, 255, 0), 5, LINE_AA);
	/*
		参数1为画布，参数2表示轮廓在的数组，
		参数3表示绘制第几个轮廓，-1表示全部绘制
		参数4表示颜色
		参数5表示线宽，-1表示填充
		参数6表示线型
		第七个参数为轮廓结构信息，
		第八个参数为maxLevel
	*/
	imshow("多边形绘制", canvas);
	imshow("多边形绘制2", canvas2);
}
 
//17 鼠标操作  //鼠标事件
  
/*
	EVENT_MOUSEMOVE              滑动
	EVENT_LBUTTONDOWN          左键点击
	EVENT_RBUTTONDOWN          右键点击
	EVENT_MBUTTONDOWN          中键点击
	EVENT_LBUTTONUP                 左键放开
	EVENT_RBUTTONUP                 右键放开
	EVENT_MBUTTONUP                 中键放开
	EVENT_LBUTTONDBLCLK          左键双击
	EVENT_RBUTTONDBLCLK         右键双击
	EVENT_MBUTTONDBLCLK         中键双击
	EVENT_MOUSEWHEEL    滚轮上下滑动
	EVENT_MOUSEHWHEEL   滚轮左右滑动 flags +-判断
*/
/*
Point sp(-1, -1);//鼠标的开始的位置
Point ep(-1, -1);
Mat temp; //原图，每次绘制前擦除
static void on_draw(int event, int x, int y, int flags, void* userdata)
{                 // 鼠标事件      位置
	               //所有on_draw输入 均将被setmousecallback识别并按顺序赋予意义
	Mat image = *((Mat*)userdata);

	
	
		if (event == EVENT_LBUTTONDOWN)//如果鼠标的左键按下
		{
			sp.x = x;
			sp.y = y;
			cout << "start point" << sp << endl; //打印开始位置

			namedWindow("勾选区域", WINDOW_AUTOSIZE);
			destroyWindow("勾选区域"); //清零以前的提取窗口	
		}
		else if (event == EVENT_LBUTTONUP) //如果鼠标的左键抬起
		{   			
				ep.x = x;
				ep.y = y;
				if(ep.x > image.cols){ ep.x = image.cols; }
				if (ep.y > image.rows) { ep.y = image.rows; }//越界判断
				int dx = ep.x - sp.x;
				int dy = ep.y - sp.y;  //计算开始与结束的两个方向的距离
				if (dx > 0 && dy > 0)   //判断距离是否大于0
				{
					Rect box(sp.x, sp.y, dx, dy); //矩形参数
					//提取区域
					temp.copyTo(image);
					imshow("勾选区域", image(box)); 
					//绘制矩形
					rectangle(image, box, Scalar(0,255,255), 2, 8, 0);
					imshow("鼠标绘制", image);
					sp.x = -1;
					sp.y = -1;//复位，为下一次做准备
				}
		}
		else if (event == EVENT_MOUSEMOVE) //如果鼠标移动
		{
			if (sp.x > 0 && sp.y > 0)  //鼠标移动 为左上到右下
			{
				ep.x = x;
				ep.y = y;
				if (ep.x > image.cols) { ep.x = image.cols; }
				if (ep.y > image.rows) { ep.y = image.rows; }//越界判断
				int dx = ep.x - sp.x;
				int dy = ep.y - sp.y;
				if (dx > 0 && dy > 0)
				{
					Rect box(sp.x, sp.y, dx, dy);
					temp.copyTo(image);
					rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
					imshow("鼠标绘制", image);
				}
			}
		}
		else if (event == EVENT_RBUTTONDBLCLK) //如果鼠标右键双击
		{
			bitwise_not(image,image);
			imshow("鼠标绘制", image);
		}

	

}
void QuickDemo::mouse_drawing_demo(Mat& image)
{
	namedWindow("鼠标绘制", WINDOW_AUTOSIZE);
	
	setMouseCallback("鼠标绘制", on_draw, (void*)(&image));
	//设置窗口的回调函数。参数1表示名称，参数2表示调用on_draw(绘制方法)
	  //所有on_draw输入参数 均将被setmousecallback识别并按顺序赋予意义与输入值
	imshow("鼠标绘制", image);
	temp = image.clone();
}
*/


//18 像素类型的转换与归一化 0-255->0-1
      //深度学习数据类处理
void QuickDemo::norm_demo(Mat& image)
{    
	//归一化类型 normtype
	/*
	NORM_MINMAX   最常用
	NORM_INF
	NORM_L1
	NORM_L2

	*/
	
	cout << image.type() << endl;//打印出来图片的类型
	image.convertTo(image, CV_32F);
	//将dst数据转换成浮点型float32位数据。**127->127.0
	
		//CV_8UC3   3通道每个通道8位的UC类型
		//CV_32FC3	3通道 每个通道32位的浮点数
	    //CV_32S    3通道 每个通道32位的int整形类型
	cout << image.type() << endl;//打印转换后的数据类型

	//归一化函数 
	Mat dst;
	normalize(image, dst, 1.0, 0, NORM_MINMAX);//进行归一化操作 **127.0->0.5
	/*	
	src   输入数组；
    dst   输出数组，数组的大小和原数组一致；
    alpha  1,用来规范值，2.规范范围，并且是下限；
    beta   只用来规范范围并且是上限；//为0时则为值归一化，否则为范围归一化
    norm_type   归一化选择的数学公式类型；
	dtype  当负，输出在大小深度通道数都等于输入，
	       当正，输出只在深度与输入不同，不同的地方由dtype决定；
	mark   掩码。选择感兴趣区域，选定后只能对该区域进行操作。
	*/	
	cout << dst.type() << endl;//打印归一化操作之后的数据
	imshow("图像的归一化", dst);//显示归一化的图像

}

//19 放缩 插值
void QuickDemo::resize_demo(Mat& image)
{    //插值类型
	/*
	a.最近邻插值——INTER_NEAREST；
　　b.线性插值   ——INTER_LINEAR；（默认值）
　　c.区域插值   ——INTER_AREA；(利用像素区域关系的重采样插值)
　　d.三次样条插值——INTER_CUBIC（超过4*4像素邻域内的双三次插值）
　　e.Lanczos插值——INTER_LANCZOS4（超过8*8像素邻域的Lanczos插值）
　　一般来说要缩小图像用区域插值（INTER_AREA）；
    要放大图像一般用三次样条插值（INTER_CUBIC）或者线性插值（INTER_LINEAR）快；
	*/
	Mat zoomin, zoomout;
	int h = image.rows;
	int w = image.cols;
	//缩放 插值
	resize(image, zoomin, Size(w / 2, h / 2), 0, 0, INTER_LINEAR);
	imshow("zoomin", zoomin);
	/*    第一个参数：为输入图像；
　　	  第二个参数：为输出图像；
　　	  第三个参数：输出图像的大小；
　　	  第四个参数：沿着水平x轴的缩放系数；
　　	  第五个参数：沿着垂直y轴的缩放系数；
　　	  第六个参数：插值方式默认为 INTER_LINEAR  线性插值
	*/	
	resize(image, zoomout, Size(w * 1.5, h * 1.5), 0, 0, INTER_LINEAR);
	imshow("zoomout", zoomout);
}

//ASSIGN 鼠标滚轮实现图片缩放
  char times = 0;
static void on_rolling(int event, int x, int y, int flags, void* userdata)
{                 // 鼠标事件      位置
				   //所有输入 均将被setmousecallback识别并按顺序赋予意义
	Mat image = *((Mat*)userdata);
	if (event == EVENT_MOUSEWHEEL)//如果鼠标滚轮
	{
		int h = image.rows;
		int w = image.cols;
		if (flags < 0) 
		{
			times = times - 1;
			resize(image, image, Size(w + (times*w)/20, h + (times * h) / 20), 0, 0, INTER_LINEAR);
			imshow("鼠标滚轮缩放", image);
		}
		if (flags > 0)
		{
			times = times + 1;
			resize(image, image, Size(w + (times * w) / 20, h + (times * h) / 20), 0, 0, INTER_LINEAR);
			imshow("鼠标滚轮缩放", image);
		}
	}	
}
void QuickDemo::mouseRolling_demo(Mat& image)
{
	namedWindow("鼠标滚轮缩放", WINDOW_AUTOSIZE);
	setMouseCallback("鼠标滚轮缩放", on_rolling, (void*)(&image));
	//设置窗口的回调函数。参数1表示名称，参数2表示调用on_draw(绘制方法)
	  //所有on_draw输入参数 均将被setmousecallback识别并按顺序赋予意义与输入值
	imshow("鼠标滚轮缩放", image);
}

// 20  图像的翻转
void QuickDemo::flip_demo(Mat& image)
{
	Mat dst;
	flip(image, dst, 0);//上下翻转 x对称
	imshow("图像竖直翻转", dst);
	flip(image, dst, 1);//左右翻转 y对称
	imshow("图像水平翻转", dst);
	flip(image, dst, -1);//旋转180°
	imshow("图像旋转180", dst);
}

// 21  图像的旋转  
Mat QuickDemo::rotate_demo(Mat& image)
{
	Mat dst, M;
	int h = image.rows;//定义图片的高度
	int w = image.cols;//定义图片的宽度


	M = getRotationMatrix2D(Point2f(w / 2, h / 2), 45, 1.0);
	/*Point2f center：表示旋转的中心点
	    double angle：表示旋转的角度
		double scale：图像缩放因子*/

	double cos = abs(M.at<double>(0, 0)); //求出|cosθ|
	double sin = abs(M.at<double>(0, 1)); //求出|sinθ|
	int nw = cos * w + sin * h;  //new width
	int nh = sin * w + cos * h;  //new height
	M.at<double>(0, 2) += (nw / 2 - w / 2); //a += b   等价于  a=a+b
	M.at<double>(1, 2) += (nh / 2 - h / 2);//求出矩阵新的旋转中心
	
	/*仿射变换*/
	warpAffine(image, dst, M, Size(nw, nh), INTER_LINEAR, 0, Scalar(0, 0, 0));
	imshow("旋转演示", dst);
	/*
	image - 输入图像。
	dst - 输出
    M - 变换矩阵。
	dsize - 输出图像的大小。
	INTER - 插值方法的组合（int 类型！）
	borderMode - 边界像素模式（int 类型！）
	borderValue - （背景颜色）边界填充值; 默认情况下，它为0。  
	*/
	return dst;
}

//22 视频 调用摄像头
void QuickDemo::video0_demo(Mat& image)
{
	VideoCapture capture("E:/videos/opencv/origin.mp4");  //读取视频的地址 0为摄像头
	Mat frame;//定义一个二值化的 frame
	Mat gray;
	Mat hsv;
	while (true)
	{
		capture.read(frame); //读取视频
		//flip(frame, frame, 1);//图像镜像操作
		if (frame.empty())//如果视频为空的话 跳出操作
		{
			break;
		}
		imshow("frame", frame);//显示视频
		colorSpace_Demo(frame, & hsv, &gray);//对视频调用之前的demo
		int c = waitKey(1);//停顿100ms 做视频处理都是1
		if (c == 27) { //esc 退出应用程序
			break;
		}
	}
	capture.release();//释放相机的资源
}

//23 视频 数据 处理 保存
void QuickDemo::video_demo(Mat& image)
{

	VideoCapture capture("E:/videos/opencv/origin.mp4");
	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);//获取视频的宽度
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);//获取视频的高度
	int count = capture.get(CAP_PROP_FRAME_COUNT);//视频总的帧数	
	double fps = capture.get(CAP_PROP_FPS);//fps是衡量处理视频的能力
	cout << "frame width" << frame_width << endl;
	cout << "frame height" << frame_height << endl;
	cout << "frame FPS" << fps << endl;
	cout << "frame count" << count << endl;
	VideoWriter framewriter("E:/videos/opencv/test.mp4", 
		        capture.get(CAP_PROP_FOURCC), 
		        fps, Size(frame_width, frame_height), true);

	VideoWriter graywriter("E:/videos/opencv/gray1.mp4",
		capture.get(CAP_PROP_FOURCC),
		fps, Size(frame_width, frame_height), true);

	VideoWriter hsvwriter("E:/videos/opencv/hsv1.mp4",
		capture.get(CAP_PROP_FOURCC),
		fps, Size(frame_width, frame_height), true);

	//参数1 保存地址。参数2 获取图片的格式 
	//参数3 图片的帧数 参数4 视频宽高 参数5 真
	Mat frame;
	Mat gray;
	Mat hsv;
	while (true)
	{
		capture.read(frame);
		//flip(frame, frame, 1);//图像镜像操作
		if (frame.empty())
		{
			break;
		}
		imshow("frame", frame);
		colorSpace_Demo(frame,&hsv,&gray); //利用指针输出多个变量

		framewriter.write(frame);
		graywriter.write(gray);
		hsvwriter.write(hsv);

		int c = waitKey(1);//停顿100ms 做视频处理都是1
		if (c == 27) { //esc 退出应用程序
			break;
		}
	}
	framewriter.release();
	graywriter.release();
	hsvwriter.release();
	//释放存放的资源
}

//ASSIGN 特征识别
void QuickDemo::sift_demo(Mat& image)
{
	Mat imageL = imread("E:/pictures/opencv_img/test0.jpg");
	Mat imageR = rotate_demo(imageL);
	/*imshow("1", imageL);
	imshow("2", imageR);
	waitKey();
	return 0;*/



	//提取特征点方法
	//SIFT
	Ptr<SIFT> surf = cv::SIFT::create();
	//ORB
	//cv::Ptr<cv::ORB> orb = cv::ORB::create();
	//SURF
	//cv::Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create();

	//特征点
	std::vector<cv::KeyPoint> keyPointL, keyPointR;
	//单独提取特征点
	surf->detect(imageL, keyPointL);
	surf->detect(imageR, keyPointR);

	//画特征点
	cv::Mat keyPointImageL;
	cv::Mat keyPointImageR;
	drawKeypoints(imageL, keyPointL, keyPointImageL, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	drawKeypoints(imageR, keyPointR, keyPointImageR, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	//显示窗口
	cv::namedWindow("KeyPoints of imageL", WINDOW_FREERATIO);
	cv::namedWindow("KeyPoints of imageR", WINDOW_FREERATIO);

	//显示特征点
	cv::imshow("KeyPoints of imageL", keyPointImageL);
	cv::imshow("KeyPoints of imageR", keyPointImageR);

	//特征点匹配
	cv::Mat despL, despR;
	//提取特征点并计算特征描述子
	surf->detectAndCompute(imageL, cv::Mat(), keyPointL, despL);
	surf->detectAndCompute(imageR, cv::Mat(), keyPointR, despR);

	//Struct for DMatch: query descriptor index, train descriptor index, train image index and distance between descriptors.
	//int queryIdx –>是测试图像的特征点描述符（ descriptor ）的下标，同时也是描述符对应特征点（keypoint)的下标。
	//int trainIdx –> 是样本图像的特征点描述符的下标，同样也是相应的特征点的下标。
	//int imgIdx –>当样本是多张图像的话有用。
	//float distance –>代表这一对匹配的特征点描述符（本质是向量）的欧氏距离，数值越小也就说明两个特征点越相像。
	std::vector<cv::DMatch> matches;

	//如果采用 flannBased 方法 那么 desp通过orb的到的类型不同需要先转换类型
	if (despL.type() != CV_32F || despR.type() != CV_32F)
	{
		despL.convertTo(despL, CV_32F);
		despR.convertTo(despR, CV_32F);
	}

	cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("FlannBased");
	matcher->match(despL, despR, matches);

	//计算特征点距离的最大值 
	double maxDist = 0;
	for (int i = 0; i < despL.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist > maxDist)
			maxDist = dist;
	}

	//挑选好的匹配点
	std::vector< cv::DMatch > good_matches;
	for (int i = 0; i < despL.rows; i++)
	{
		if (matches[i].distance < 0.5 * maxDist)
		{
			good_matches.push_back(matches[i]);
		}
	}

	cv::Mat imageOutput;
	cv::drawMatches(imageL, keyPointL, imageR, keyPointR, good_matches, imageOutput);

	cv::namedWindow("picture of matching", WINDOW_FREERATIO);
	cv::imshow("picture of matching", imageOutput);
	cv::waitKey(114514);
}

//24图像直方图
void QuickDemo::histogram_demo(Mat& image) 
{
	// 三通道分离
	std::vector<Mat> bgr_plane;
	split(image, bgr_plane);
	// 定义参数变量
	const int channels[1] = { 0 };
	const int bins[1] = { 256 };
	float hranges[2] = { 0,255 };
	const float* ranges[1] = { hranges };
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	// 计算Blue, Green, Red通道的直方图
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);

	// 显示直方图
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	// 归一化直方图数据
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	// 绘制直方图曲线
	for (int i = 1; i < bins[0]; i++) {
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	}
	// 显示直方图
	namedWindow("Histogram Demo", WINDOW_AUTOSIZE);
	imshow("Histogram Demo", histImage);
}

void QuickDemo::temp_match_demo(Mat& image) {

	Mat srcImg = imread("E:/pictures/opencv_img/target.jpg" );
	Mat tempImg = imread("E:/pictures/opencv_img/keys.jpg" );
	//1.构建结果图像resultImg(注意大小和类型)
	//如果原图(待搜索图像)尺寸为W x H, 而模版尺寸为 w x h, 则结果图像尺寸一定是(W-w+1)x(H-h+1)
	//结果图像必须为单通道32位浮点型图像
	int width = srcImg.cols - tempImg.cols + 1;
	int height = srcImg.rows - tempImg.rows + 1;
	Mat resultImg(Size(width, height), CV_32FC1);
	//2.模版匹配
	matchTemplate(srcImg, tempImg, resultImg, TM_CCOEFF_NORMED);
	imshow("result", resultImg);
	//3.正则化(归一化到0-1)
	normalize(resultImg, resultImg, 0, 1, NORM_MINMAX, -1);
	//4.遍历resultImg，给定筛选条件，筛选出前几个匹配位置
	int tempX = 0;
	int tempY = 0;
	char prob[10] = { 0 };
	//4.1遍历resultImg
	for (int i = 0; i < resultImg.rows; i++)
	{
		for (int j = 0; j < resultImg.cols; j++)
		{
			//4.2获得resultImg中(j,x)位置的匹配值matchValue
			double matchValue = resultImg.at<float>(i, j);
			//sprintf(prob, "%.2f", matchValue);
			//4.3给定筛选条件
			//条件1:概率值大于0.9
			//条件2:任何选中的点在x方向和y方向上都要比上一个点大5(避免画边框重影的情况)
			if (matchValue > 0.7 && abs(i - tempY) > 5 && abs(j - tempX) > 5)
			{
				//5.给筛选出的点画出边框和文字
				rectangle(srcImg, Point(j, i), Point(j + tempImg.cols, i + tempImg.rows), Scalar(0, 255, 0), 1, 8);
				tempX = j;
				tempY = i;
			}
		}
	}
	imshow("srcImg", srcImg);
	imshow("template", tempImg);


}
//加速视频
void QuickDemo::accel_video(Mat& image)
{

	VideoCapture capture("E:/Videos/SF/output/01.mp4");

	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);//获取视频的宽度
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);//获取视频的高度
	int count = capture.get(CAP_PROP_FRAME_COUNT);//视频总的帧数	
	double fps = capture.get(CAP_PROP_FPS);//fps是衡量处理视频的能力


	VideoWriter framewriter("E:/Videos/SF/output/tt01b.mp4",
		capture.get(CAP_PROP_FOURCC),
		fps*10.0, Size(frame_width, frame_height), true);


	Mat frame;

	while (1)
	{
		capture.read(frame);

		if (frame.empty())
		{
			break;
		}
		imshow("frame", frame);
		framewriter.write(frame);


		//按Esc键退出while
		int c = waitKey(1);// 做视频处理都是1
		if (c == 27) 
		{ //esc 退出应用程序
			break;
		}

	}
		framewriter.release();

	//getchar();
}

//分割程序

Mat QuickDemo::for_background(Mat  IMG, cv::Point_<int> center, int in_r,int out_r)
{    

	// 置黑inner
	Mat in_roi = Mat::zeros(IMG.size(), IMG.type());
	in_roi.setTo(255);
	Mat copy_img;
	IMG.copyTo(copy_img);
	const cv::Scalar color = (0,0,0);
	circle(in_roi, center, in_r, color, -1);
	Mat black_in;
	bitwise_and (in_roi,copy_img,black_in);
	// 置黑outer
	Mat out_roi = Mat::zeros(IMG.size(), IMG.type());
	out_roi.setTo(0);
	circle(out_roi, center, out_r, Scalar(255, 255, 255), -1);
	Mat ring;
	bitwise_and(out_roi,black_in,ring);
	return ring;
}
//解圆形
Mat  QuickDemo::reduce_circle_domin(Mat  img, cv::Point_<int> c_point, int c_r)
{         // 输入图像 位置 圆的半径 解出的圆
	Mat circle_roi = Mat::zeros(img.size(), img.type());  //[2592 x 1944]
	Mat copy_img = img.clone();
	circle(circle_roi, c_point, c_r, Scalar(255, 255, 255), -1);
	


	Mat reduce_img;
	copy_img.copyTo(reduce_img, circle_roi);


	return reduce_img;
}
// 开运算 闭运算
Mat  QuickDemo::opening_ellipse(Mat  img, cv::Point_<int> kernel_size, int interations)
{
	Mat copy_img = img.clone();
	Mat kernel = getStructuringElement(cv::MORPH_ELLIPSE,kernel_size);
	Mat img_open;
		morphologyEx(copy_img, img_open,cv::MORPH_OPEN,kernel, cv::Point(-1,-1),interations = interations);
	return img_open;
}
Mat  QuickDemo::closing_ellipse(Mat  img, cv::Point_<int> kernel_size, int interations)
{
	Mat copy_img = img.clone();
	Mat kernel = getStructuringElement(cv::MORPH_ELLIPSE, kernel_size);
	Mat img_close;
	morphologyEx(copy_img, img_close, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), interations = interations);
	return img_close;
}
//填充孔洞
Mat  QuickDemo::fill_hole(Mat  img)
{
	Mat copy_img = img.clone();
	
	int h = copy_img.rows;
	int w = copy_img.cols;
	Mat mask = Mat::zeros(Size(w + 2, h + 2), copy_img.type());
	floodFill(copy_img, mask, Point(0,0), 255 );
	Mat copy_img_inv;
	bitwise_not(copy_img, copy_img_inv);
	Mat fill_image = img | copy_img_inv;
	return 	fill_image;
}



//找圆环中心和内径

pair<Point2f, float>  QuickDemo::find_point(Mat orig_img)
{
	Mat copy_img = orig_img.clone();
	//划分感兴趣区域
	Mat roi = reduce_circle_domin(copy_img,Point(1210,990),980);  //[2592 x 1944]

	//直方图均值化
	Mat equal0;
	equalizeHist(roi, equal0);

	
	//二值化
	Mat binary, thresh;
	threshold(equal0, binary,220,255, THRESH_TOZERO_INV);
	threshold(binary, thresh, 65, 255, THRESH_BINARY);


	
	//形态学处理 闭运算
	Mat close0 = closing_ellipse(thresh,Point(15,15),1);
	//填充孔洞
	Mat Fill_IMG = fill_hole(close0);
	//开运算
	Mat open0 = opening_ellipse(Fill_IMG, Point(15, 15), 1);

	vector<vector<Point>> contours;
    findContours(open0.clone(),contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
	vector<int> area = {};
	//找到最大轮廓
	int length = size(contours);
	for (int k = 0; k < length - 1; k++)
	{
		area.push_back(contourArea(contours[k]));
	}
	int max_idx = 2;//max_element(area.begin(), area.end()) - area.begin();
	//计算实际的中心点半径和坐标
	Point2f center;
	float in_radius;
	minEnclosingCircle(contours[max_idx], center, in_radius);
	
	pair<Point2f, float> result;
	result = make_pair(center, in_radius);  //center[1198.23, 971.415]radius965.175
	return result;   //center = result.first;  radius = result.second
} 


void QuickDemo::sensors_homework()
{
	Mat original_img = imread("E://pictures/opencv_img/homework_pic.bmp",IMREAD_GRAYSCALE);
	Mat img = original_img.clone();
	pair<Point2f, float> result;
	result = find_point(img);
	Point2f center;
	float out_radius;
	center = result.first; 
	out_radius = result.second;  
	float in_radius = out_radius / 1.3; 
	int x = round(center.x);
	int y = round(center.y);
	int in_r = round(in_radius);
	int out_r = round(out_radius);
	//提取圆环
	Mat ring = for_background(img, Point_<int> (x,y),in_r,out_r);
	//高斯模糊，便于寻找边缘
	Mat ring_blur;
	blur(ring, ring_blur,Point(5,5));
	//边缘检测，寻找划痕
	Canny(ring_blur,ring,50,240);
	//圆环的边缘也有可能被被识别为边缘，因此需要用之前识别到的圆环位置消除圆环边界，突出划痕
	Mat remove_roi_out = Mat::zeros(ring.size(), ring.type());
	remove_roi_out.setTo(255);
	Scalar color_out = (0, 0, 0);
	circle(remove_roi_out, Point_<int>(x, y), out_r, color_out,4);
	circle(remove_roi_out, Point_<int>(x, y), in_r, color_out,4);
	bitwise_and(remove_roi_out, ring, ring);
	Mat scratch = closing_ellipse(ring, Point_<int>(15, 15), 1);
	//找到划痕轮廓，用最小外接矩形描述它的长度
	vector<vector<Point>> contours;
	findContours(scratch, contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
	vector<int> area = {};
	//找到最大轮廓
	int length = size(contours);
	for (int k = 0; k < length - 1; k++)
	{
		area.push_back(contourArea(contours[k]));
	}
	namedWindow("debug", 0);
	imshow("debug", scratch);
	int max_idx = max_element(area.begin(), area.end())- area.begin();
	//计算图像上的长
	RotatedRect rect = minAreaRect(contours[max_idx]);
	Mat box, Cov;
	boxPoints(rect, box);
	box.assignTo(Cov, CV_32S);
	//按指定大小显示
	int w = original_img.cols;
	int h = original_img.rows;
	float f1 = 1.0 * 1000.0 / w;
	float f2 = 1.0 * 1000.0 / h;
	float factor = min(f1,f2);
	int width = int(w * factor);
	int height = int(h * factor);
	//画矩形框
	polylines(original_img, Cov, true, Scalar(0, 0, 255),2);
	//drawContours(original_img, Cov,0, Scalar(0,0,255),2);
	//矩形的长度
	float length_pixel = rect.size.height;
	cout <<"划痕最小外接矩形长度" << length_pixel <<"mm" << endl;
	//估计划痕实际长度
	cout << "划痕实际长度" << length_pixel * 0.4 << "mm" << endl;
	resize(original_img, original_img, Size(width, height));
	//显示划痕检测框
	imshow("rect", original_img);


}






