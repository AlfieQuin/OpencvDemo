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

//01ת��ͼ���ʽ������ͼ��//

void QuickDemo::colorSpace_Demo(Mat& image,Mat* datahsv, Mat* datagray) {

	Mat gray, hsv;
	//����Ҷ�ͼ��hsvͼ����
	//������ת��Ϊ�Ҷ���HSV�����������
	cvtColor(image, hsv, COLOR_BGR2HSV);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	//imshow("origin", image);
	imshow("HSV", hsv);  //��ʾ
	imshow("�Ҷ�", gray);
	//����
	//imwrite("E:/pictures/opencv_img/output��0.png",gray);
	//imwrite("E:/pictures/opencv_img/outputhsv0.png", hsv);
	
	//����ָ������������
	*datahsv = hsv;
	*datagray = gray;
}  

//02����ͼ�� ����ͼ��//
void  QuickDemo::MatCreation_Demo() {
	//mat m1, m2;//clone copy
	//m1 = image.clone();
	//image.copyto(m2);        �������   ֻ��=��ǳ����
	// 
	//�����հ�ͼ�� 
	Mat m3 = Mat::zeros(Size(400,400),CV_8UC3) ; //8λ �޷��� 3ͨ��  ��=8 ��=8*3��
	m3 = Scalar(255,0,0);            //3��ͨ���ֱ�ֵ pure blue
	
										 //������ �� �� ͨ��
	cout << "width:" << m3.cols << "  height:" << m3.rows << "  channels:" << m3.channels() << endl;

	//cout << m3 << endl;  //��ӡ
	
	imshow("m3", m3);


}

// 03���ʶ�дͼ�������  /
void QuickDemo::pixel_visit_Demo(Mat& image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();  //�Ҷ�1����ɫ3
	/*for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			if(dims == 1){ //�Ҷ�ͼ
				int pv = image.at<uchar>(row, col); //��ȡ����ֵ
				image.at<uchar>(row, col)= 255-pv; //
			}

			if(dims == 3){//��ɫͼ��
				Vec3b bgr = image.at<Vec3b>(row, col);
				image.at<Vec3b>(row, col)[0] = 255-bgr[0];
				image.at<Vec3b>(row, col)[1] = 255-bgr[1];
				image.at<Vec3b>(row, col)[2] = 255-bgr[2];
			}
		}
	}*/
	//�����±�
	for (int row = 0; row < h; row++) {
		uchar  *current_row = image.ptr<uchar>(row); //��ȡ��ǰ��ָ��
		for (int col = 0; col < w; col++) {
			if (dims == 1) { //�Ҷ�ͼ
				int pv = *current_row; //��ȡ����ֵ
				*current_row++ = 255 - pv; //
			}

			if (dims == 3) {//��ɫͼ��
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}  //����ָ��  ��ʱcol��row�����ò�����Ѱַ����һ�����⣩�����Ǽ���
	imwrite("E:/pictures/opencv_img/invertest.jpg", image);
	imshow("pixel_change", image);

}

//04ͼ�����ص���������
void QuickDemo::operator_Demo(Mat& image) {
	Mat dst;
	//dst = image + Scalar(50, 50, 50); // ͼƬ����
	//dst = image/Scalar(2,2,2);// ͼƬ���ȼ���
	Mat m = Mat::zeros(image.size(),image.type());  //m����ߴ�
	m = Scalar(2,2,2);        //m��ֵ
	multiply(image,m,dst);   //dst = image*m
	
	imshow("����",dst); //

}

//05��������
/*
Mat  src, dst, m;  //���� ��� ��ֵ
int lightness = 50;//�����ʼ������Ϊ50 ȫ�ֱ���
static void ontrack(int,void*){
	m = Scalar(abs(lightness - 50), abs(lightness - 50), abs(lightness - 50));//�����������ȵ���ֵ
	if(lightness>=50){		
		add(src, m, dst);//�������ȱ仯Ϊ��
	}
	else {
		subtract(src, m, dst);//�������ȱ仯Ϊ��
	}
	imshow("���ȵ���", dst);//��ʾ��������֮���ͼƬ
}
void QuickDemo::adjust_light(Mat &image) {
	namedWindow("���ȵ���", WINDOW_FREERATIO);
	dst = Mat::zeros(image.size(), image.type());//ͼƬ�ĳ�ʼ������һ����image��С��ȣ�������ͬ��ͼ��
	m = Mat::zeros(image.size(), image.type());//ͼƬ�ĳ�ʼ������һ����image��С��ȣ�������ͬ��ͼ��
	int max_light = 100;
	
	src = image;//��src��ֵ
	createTrackbar("value_bar:","���ȵ���", &lightness, max_light,ontrack);
	ontrack(50,0);

}  */ 

//06��������������  *point   �ص�����
/*
static void on_lightness(int b, void* userdata)
{
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(b, b, b);
	addWeighted(image, 1.0, m, 0, b, dst);//�ں�����ͼ
	imshow("����&�Աȶȵ���", dst);
}
static void on_contrast(int b, void* userdata)
{
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, dst);//�ں�����ͼ
	imshow("����&�Աȶȵ���", dst);
}
void QuickDemo::tracking_bar_demo(Mat& image) {
	namedWindow("����&�Աȶȵ���", WINDOW_FREERATIO);
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;
	createTrackbar("Value Bar", "����&�Աȶȵ���", &lightness, max_value, on_lightness, (void*)(&image));
	createTrackbar("Contrast Bar", "����&�Աȶȵ���", &contrast_value, 200, on_contrast, (void*)(&image));
	on_lightness(50, &image);
}
*/

//07������Ӧ
void QuickDemo::key_demo(Mat& image) {
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true)
	{
		char c = waitKey(100);// ͣ��100ms ����Ƶ������1
		if (c == 27) { //esc �˳�Ӧ�ó���
			break;
		}
		if (c == 49)//key#1
		{
			cout << "you enter key #1" << endl;
			cvtColor(image, dst, COLOR_BGR2GRAY);  //����1ת��Ϊ�Ҷ�
		}
		if (c == 50)//key#1
		{
			cout << "you enter key #2" << endl;
			cvtColor(image, dst, COLOR_BGR2HSV); //����2ת��ΪHSV
		}
		if (c == 51)//key#1
		{
			cout << "you enter key #3" << endl;
			dst = Scalar(50, 50, 50);
			add(image, dst, dst);  //����3�������
		}
		imshow("������Ӧ", dst);
		cout << c << endl;
	}
}

//08��ɫ�� ���� ��ʱ
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
	int t ;  //tΪ0-21��ѭ��
	while (true)
	{
		t = index % 22; //0-21ʵ�����ݵ�ѭ��
		char c = waitKey(100);// 
		if (c == 27) { //esc �˳�Ӧ�ó���
			break;
		}
		//if (c == 49)//key#1 ���°���1ʱ������ͼƬ��ָ��λ��
		//{
		//	cout << "you enter key #1" << endl;
		//	imwrite("E:/pictures/opencv_img/colormap0.png", dst);
		//}
		applyColorMap(image, dst, colormap[t]);//ѭ��չʾ22��ͼƬ
		index++;
		imshow("ѭ������", dst);
		cout << t << endl;
		Sleep(500); //��ʱ0.5s
	}
}

//09 ��ͼ���� //10 �߼�����
void QuickDemo::bitwise_demo(Mat& image) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	/*��ͼ*/
	 /*  ����1��Դͼ��
	   ����2��(a,b,c,d)
	           a,b:��ʼλ��
			   c.d:ĩλλ��
	   ����3�� ��ɫ
	   ����4�� ����(���)  ()   ����(����)
	   ����5�� ����� 4 8 ����
	   ����6��С��λ��
	*/
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0); //BGR 
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0); //
	imshow("m1", m1);
	imshow("m2", m2);

	Mat dst;
	//bitwise_and(m1, m2, dst);//λ������   *������ɫ
	//bitwise_or(m1, m2, dst);  //λ������     +������ɫ
	//bitwise_not(image, dst);//ȡ������     ��ɫ
	//bitwise_xor(m1, m2, dst);//������  �� ԭɫ ��+��
	dst = ~image;
	imshow("����λ����", dst);  
}

//11ͨ������
void QuickDemo::channels_demo(Mat& image)
{
	vector<Mat>mv;  //����mat��������
	split(image, mv);  //ͨ������ BGR
	
	/*0,1,2����ͨ���ֱ����BGR���ر�2��ͨ����ζ�ſ���һ��ͨ����*/
	/* imshow("��ɫ0", mv[0]);
	imshow("��ɫ0", mv[1]);
	imshow("��ɫ0", mv[2]); */
	Mat dst;
	mv[1] = 0;
	mv[0] = 0;
	merge(mv, dst); //dst = 0+0+R
	imshow("��ɫ", dst);

	Mat swapBR = Mat::zeros(image.size(), image.type());
	int from_to[] = { 0,1,1,2,2,0 };
	//����ͨ������0->��1����1->��2����2->��0   
	mixChannels(&image, 1, &swapBR, 1, from_to, 3);//3��ʾ3��ͨ��
	imshow("ͨ�����", swapBR);
	//ͨ�����
  /* ����1��������󣬿���x��
	   ����2��x��ͼƬ
	   ����3�� ������� y��
	   ����4�� y��
	   ����5�� ִ��from_to����
	   ����6��3ͨ��
	*/
}

//12ͼ��ɫ�ʿռ�ת��  ��ͼ�ر� copyto()��������Ӧ��
void QuickDemo::inrange_demo(Mat& image){
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);  //BGR->HSV ��ʶ�Ƚϸ�
	imshow("hsv", hsv);
	Mat mask;        //���ֻ�������
	inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);
	//35,43,46����ͼƬ����ɫ�����ȷ����Сֵ��
	//77,255,255 ��ȡ
	//����1�ͷ�Χ������2�߷�Χ
	//��hsv�е��ɵ͵��ߵ����ص���ȡ�������Ҵ洢��mask���С���ȡ��Ϊ�ף�δ��ȡ��Ϊ�ڣ���ĻΪ�ף�
	Mat redback = Mat::zeros(image.size(), image.type());
	redback = Scalar(40, 40, 200);
	bitwise_not(mask, mask);  //mask�б���Ϊ��
	imshow("mask", mask);

	image.copyTo(redback, mask);//ֻ��mask��Ϊ1�׵�λ�õ����أ���image������redback�С�
	imshow("roi��ȡ", redback);


}

//13����ͳ��
void QuickDemo::pixel_statistic_demo(Mat& image) {
	double minv, maxv;//������ֵ
	Point minLoc, maxLoc;//������ֵ��ַ point ������������
	/*����ͨ��*/
	vector<Mat>mv;
	split(image, mv);
	
	/*�ֱ��ӡ����ͨ������ֵ*/
	for (int i = 0; i < mv.size(); i++) {
		/*�˺���ֻ�ܴ���ͨ��ͼ��*/ // ��һ��������mask
		minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc, Mat());
		cout <<" No.channels��"<<i 
			<< " min value: " << minv << " max value " << maxv << endl;
	}
	
	 //���ֵ ����
	Mat mean, stddev;
	meanStdDev(image,mean,stddev); //��һ��������mask
	cout << " mean:" << mean << std::endl;
	cout << " stddev:" << stddev << std::endl;
}

//14���λ���
void QuickDemo::drawing_demo(Mat& image) {
	
		Rect rect; //�������
		rect.x = 100;
		rect.y = 100;  //λ��
		rect.width = 150;
		rect.height = 200;  //��С  
	    //�ȼ��� rect = Rect(100,100,150,200);
		
		Mat bg = Mat::zeros(image.size(), image.type());//���ɱ���
		/*����*/
		rectangle( bg, rect, Scalar(0, 0, 255), 3, 8, 0);
		/*Բ��*/
		circle(bg, Point(250, 300), 15, Scalar(255, 0, 0), 3, 8, 0);
		 /*  ����1��Դͼ��
		   ����2�� Բ������
		   ����3�� ��ɫ
		   ����4�� ����(���)     ����(�����߿�)
		   ����5�� ����� 4 8 ����
		   ����6��С��λ��
		*/	
		/*ֱ��*/
		line(bg, Point(100, 100), Point(250, 300), Scalar(0, 255, 0), 3, LINE_AA, 0); //  LINA_AA �����
		
		RotatedRect rtt;
		rtt.center = Point(100, 100);
		rtt.size = Size(200, 100);
		rtt.angle = 0.0;
		//�ȼ��� rtt = RotatedRect(100,100,100,200,0.0);
		/*��Բ*/
        ellipse(bg, rtt, Scalar(255, 0, 0), 2, 8);
		
		Mat dst;
		addWeighted(image, 0.7, bg, 1, 0, dst); //�ں�ͼ��	


		
		
		
		imshow("������ʾ", dst);
	

}

//15�����ɫ
void QuickDemo::random_drawing(Mat& image)
{
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	int w = canvas.cols;
	int h = canvas.rows;


	RNG rng(12345);
	//�����
	/*
	    RNG���Բ���3�������
		RNG(int seed) ʹ������seed����һ��64λ���������Ĭ��-1	
		RNG::gaussian( ) ����һ����˹�ֲ��������
		RNG::uniform(a, b ) ����һ��[a,b)��Χ�ľ��ȷֲ����������
		                    a,b����������Ҫһ�£�
							���ұ�����int��float��double�е�һ�֣�
							Ĭ����int��
		RNG::gaussian( ��) ����һ����ֵΪ0����׼��Ϊ�ҵ��������
	   ��+ RNG::gaussian( ��) ������ֵΪ�ˣ���׼��Ϊ�ҵ������������
	*/	
	while (true)
	{
		int c = waitKey(10);
		if (c == 27)
		{
			break;
		}
		int x1 = rng.uniform(0, w);
		int y1 = rng.uniform(0, h);  //��ʼλ��
		int x2 = rng.uniform(0, w);
		int y2 = rng.uniform(0, h);  //����λ�� point

		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255); //������ɫ
		canvas = Scalar(0, 0, 0);   //�滭ǰ���������
		line(canvas, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 5, LINE_AA, 0);//line_AA��ʾȥ�����	
		imshow("���������ʾ", canvas);
	}
}

//16 ���ƶ����
void QuickDemo::polyline_drawing_demo(Mat& image)
{
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	Mat canvas2 = Mat::zeros(Size(512, 512), CV_8UC3);
	Point p1(100, 100);
	Point p2(350, 100);
	Point p3(450, 280);
	Point p4(320, 450);
	Point p5(80, 400);    
	vector<Point>pts;//��5����װ��һ�������ڡ�
	pts.push_back(p1);//δ��ʼ������������ֻ����pushback����
					  //�����ʼ���������������±������
	pts.push_back(p2);
	pts.push_back(p3);
	pts.push_back(p4);
	pts.push_back(p5);	
	/*���*/
	fillPoly(canvas, pts, Scalar(0, 0, 255), LINE_AA, 0);
	 /*
	����1��ʾ���� / ���룬����2��ʾ�㼯������3��ɫ
	����4��ʾ����/��ݣ�����5��ʾС��λ��
	 */
	 /*���*/
	polylines(canvas, pts, true, Scalar(255, 255, 0), 5, LINE_AA, 0);//���ƶ����
	/*
	����1��ʾ����/���룬����2��ʾ�㼯������3��ʾ�Ƿ�պ����ߣ�����4��ɫ
	����5��ʾ�߿�����6��ʾ�߶����ͣ�����7��ʾ���ű��� 0������ 4Ϊ1/4
	*/
	
	/*ͬһ���������+��� */
	vector<vector<Point>>contours;
	contours.push_back(pts);
	drawContours(canvas2, contours, -1, Scalar(0, 0, 255), -1, LINE_AA);
	drawContours(canvas2, contours, -1, Scalar(0, 255, 0), 5, LINE_AA);
	/*
		����1Ϊ����������2��ʾ�����ڵ����飬
		����3��ʾ���Ƶڼ���������-1��ʾȫ������
		����4��ʾ��ɫ
		����5��ʾ�߿�-1��ʾ���
		����6��ʾ����
		���߸�����Ϊ�����ṹ��Ϣ��
		�ڰ˸�����ΪmaxLevel
	*/
	imshow("����λ���", canvas);
	imshow("����λ���2", canvas2);
}
 
//17 ������  //����¼�
  
/*
	EVENT_MOUSEMOVE              ����
	EVENT_LBUTTONDOWN          ������
	EVENT_RBUTTONDOWN          �Ҽ����
	EVENT_MBUTTONDOWN          �м����
	EVENT_LBUTTONUP                 ����ſ�
	EVENT_RBUTTONUP                 �Ҽ��ſ�
	EVENT_MBUTTONUP                 �м��ſ�
	EVENT_LBUTTONDBLCLK          ���˫��
	EVENT_RBUTTONDBLCLK         �Ҽ�˫��
	EVENT_MBUTTONDBLCLK         �м�˫��
	EVENT_MOUSEWHEEL    �������»���
	EVENT_MOUSEHWHEEL   �������һ��� flags +-�ж�
*/
/*
Point sp(-1, -1);//���Ŀ�ʼ��λ��
Point ep(-1, -1);
Mat temp; //ԭͼ��ÿ�λ���ǰ����
static void on_draw(int event, int x, int y, int flags, void* userdata)
{                 // ����¼�      λ��
	               //����on_draw���� ������setmousecallbackʶ�𲢰�˳��������
	Mat image = *((Mat*)userdata);

	
	
		if (event == EVENT_LBUTTONDOWN)//��������������
		{
			sp.x = x;
			sp.y = y;
			cout << "start point" << sp << endl; //��ӡ��ʼλ��

			namedWindow("��ѡ����", WINDOW_AUTOSIZE);
			destroyWindow("��ѡ����"); //������ǰ����ȡ����	
		}
		else if (event == EVENT_LBUTTONUP) //����������̧��
		{   			
				ep.x = x;
				ep.y = y;
				if(ep.x > image.cols){ ep.x = image.cols; }
				if (ep.y > image.rows) { ep.y = image.rows; }//Խ���ж�
				int dx = ep.x - sp.x;
				int dy = ep.y - sp.y;  //���㿪ʼ���������������ľ���
				if (dx > 0 && dy > 0)   //�жϾ����Ƿ����0
				{
					Rect box(sp.x, sp.y, dx, dy); //���β���
					//��ȡ����
					temp.copyTo(image);
					imshow("��ѡ����", image(box)); 
					//���ƾ���
					rectangle(image, box, Scalar(0,255,255), 2, 8, 0);
					imshow("������", image);
					sp.x = -1;
					sp.y = -1;//��λ��Ϊ��һ����׼��
				}
		}
		else if (event == EVENT_MOUSEMOVE) //�������ƶ�
		{
			if (sp.x > 0 && sp.y > 0)  //����ƶ� Ϊ���ϵ�����
			{
				ep.x = x;
				ep.y = y;
				if (ep.x > image.cols) { ep.x = image.cols; }
				if (ep.y > image.rows) { ep.y = image.rows; }//Խ���ж�
				int dx = ep.x - sp.x;
				int dy = ep.y - sp.y;
				if (dx > 0 && dy > 0)
				{
					Rect box(sp.x, sp.y, dx, dy);
					temp.copyTo(image);
					rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
					imshow("������", image);
				}
			}
		}
		else if (event == EVENT_RBUTTONDBLCLK) //�������Ҽ�˫��
		{
			bitwise_not(image,image);
			imshow("������", image);
		}

	

}
void QuickDemo::mouse_drawing_demo(Mat& image)
{
	namedWindow("������", WINDOW_AUTOSIZE);
	
	setMouseCallback("������", on_draw, (void*)(&image));
	//���ô��ڵĻص�����������1��ʾ���ƣ�����2��ʾ����on_draw(���Ʒ���)
	  //����on_draw������� ������setmousecallbackʶ�𲢰�˳��������������ֵ
	imshow("������", image);
	temp = image.clone();
}
*/


//18 �������͵�ת�����һ�� 0-255->0-1
      //���ѧϰ�����ദ��
void QuickDemo::norm_demo(Mat& image)
{    
	//��һ������ normtype
	/*
	NORM_MINMAX   ���
	NORM_INF
	NORM_L1
	NORM_L2

	*/
	
	cout << image.type() << endl;//��ӡ����ͼƬ������
	image.convertTo(image, CV_32F);
	//��dst����ת���ɸ�����float32λ���ݡ�**127->127.0
	
		//CV_8UC3   3ͨ��ÿ��ͨ��8λ��UC����
		//CV_32FC3	3ͨ�� ÿ��ͨ��32λ�ĸ�����
	    //CV_32S    3ͨ�� ÿ��ͨ��32λ��int��������
	cout << image.type() << endl;//��ӡת�������������

	//��һ������ 
	Mat dst;
	normalize(image, dst, 1.0, 0, NORM_MINMAX);//���й�һ������ **127.0->0.5
	/*	
	src   �������飻
    dst   ������飬����Ĵ�С��ԭ����һ�£�
    alpha  1,�����淶ֵ��2.�淶��Χ�����������ޣ�
    beta   ֻ�����淶��Χ���������ޣ�//Ϊ0ʱ��Ϊֵ��һ��������Ϊ��Χ��һ��
    norm_type   ��һ��ѡ�����ѧ��ʽ���ͣ�
	dtype  ����������ڴ�С���ͨ�������������룬
	       ���������ֻ����������벻ͬ����ͬ�ĵط���dtype������
	mark   ���롣ѡ�����Ȥ����ѡ����ֻ�ܶԸ�������в�����
	*/	
	cout << dst.type() << endl;//��ӡ��һ������֮�������
	imshow("ͼ��Ĺ�һ��", dst);//��ʾ��һ����ͼ��

}

//19 ���� ��ֵ
void QuickDemo::resize_demo(Mat& image)
{    //��ֵ����
	/*
	a.����ڲ�ֵ����INTER_NEAREST��
����b.���Բ�ֵ   ����INTER_LINEAR����Ĭ��ֵ��
����c.�����ֵ   ����INTER_AREA��(�������������ϵ���ز�����ֵ)
����d.����������ֵ����INTER_CUBIC������4*4���������ڵ�˫���β�ֵ��
����e.Lanczos��ֵ����INTER_LANCZOS4������8*8���������Lanczos��ֵ��
����һ����˵Ҫ��Сͼ���������ֵ��INTER_AREA����
    Ҫ�Ŵ�ͼ��һ��������������ֵ��INTER_CUBIC���������Բ�ֵ��INTER_LINEAR���죻
	*/
	Mat zoomin, zoomout;
	int h = image.rows;
	int w = image.cols;
	//���� ��ֵ
	resize(image, zoomin, Size(w / 2, h / 2), 0, 0, INTER_LINEAR);
	imshow("zoomin", zoomin);
	/*    ��һ��������Ϊ����ͼ��
����	  �ڶ���������Ϊ���ͼ��
����	  ���������������ͼ��Ĵ�С��
����	  ���ĸ�����������ˮƽx�������ϵ����
����	  ��������������Ŵ�ֱy�������ϵ����
����	  ��������������ֵ��ʽĬ��Ϊ INTER_LINEAR  ���Բ�ֵ
	*/	
	resize(image, zoomout, Size(w * 1.5, h * 1.5), 0, 0, INTER_LINEAR);
	imshow("zoomout", zoomout);
}

//ASSIGN ������ʵ��ͼƬ����
  char times = 0;
static void on_rolling(int event, int x, int y, int flags, void* userdata)
{                 // ����¼�      λ��
				   //�������� ������setmousecallbackʶ�𲢰�˳��������
	Mat image = *((Mat*)userdata);
	if (event == EVENT_MOUSEWHEEL)//���������
	{
		int h = image.rows;
		int w = image.cols;
		if (flags < 0) 
		{
			times = times - 1;
			resize(image, image, Size(w + (times*w)/20, h + (times * h) / 20), 0, 0, INTER_LINEAR);
			imshow("����������", image);
		}
		if (flags > 0)
		{
			times = times + 1;
			resize(image, image, Size(w + (times * w) / 20, h + (times * h) / 20), 0, 0, INTER_LINEAR);
			imshow("����������", image);
		}
	}	
}
void QuickDemo::mouseRolling_demo(Mat& image)
{
	namedWindow("����������", WINDOW_AUTOSIZE);
	setMouseCallback("����������", on_rolling, (void*)(&image));
	//���ô��ڵĻص�����������1��ʾ���ƣ�����2��ʾ����on_draw(���Ʒ���)
	  //����on_draw������� ������setmousecallbackʶ�𲢰�˳��������������ֵ
	imshow("����������", image);
}

// 20  ͼ��ķ�ת
void QuickDemo::flip_demo(Mat& image)
{
	Mat dst;
	flip(image, dst, 0);//���·�ת x�Գ�
	imshow("ͼ����ֱ��ת", dst);
	flip(image, dst, 1);//���ҷ�ת y�Գ�
	imshow("ͼ��ˮƽ��ת", dst);
	flip(image, dst, -1);//��ת180��
	imshow("ͼ����ת180", dst);
}

// 21  ͼ�����ת  
Mat QuickDemo::rotate_demo(Mat& image)
{
	Mat dst, M;
	int h = image.rows;//����ͼƬ�ĸ߶�
	int w = image.cols;//����ͼƬ�Ŀ��


	M = getRotationMatrix2D(Point2f(w / 2, h / 2), 45, 1.0);
	/*Point2f center����ʾ��ת�����ĵ�
	    double angle����ʾ��ת�ĽǶ�
		double scale��ͼ����������*/

	double cos = abs(M.at<double>(0, 0)); //���|cos��|
	double sin = abs(M.at<double>(0, 1)); //���|sin��|
	int nw = cos * w + sin * h;  //new width
	int nh = sin * w + cos * h;  //new height
	M.at<double>(0, 2) += (nw / 2 - w / 2); //a += b   �ȼ���  a=a+b
	M.at<double>(1, 2) += (nh / 2 - h / 2);//��������µ���ת����
	
	/*����任*/
	warpAffine(image, dst, M, Size(nw, nh), INTER_LINEAR, 0, Scalar(0, 0, 0));
	imshow("��ת��ʾ", dst);
	/*
	image - ����ͼ��
	dst - ���
    M - �任����
	dsize - ���ͼ��Ĵ�С��
	INTER - ��ֵ��������ϣ�int ���ͣ���
	borderMode - �߽�����ģʽ��int ���ͣ���
	borderValue - ��������ɫ���߽����ֵ; Ĭ������£���Ϊ0��  
	*/
	return dst;
}

//22 ��Ƶ ��������ͷ
void QuickDemo::video0_demo(Mat& image)
{
	VideoCapture capture("E:/videos/opencv/origin.mp4");  //��ȡ��Ƶ�ĵ�ַ 0Ϊ����ͷ
	Mat frame;//����һ����ֵ���� frame
	Mat gray;
	Mat hsv;
	while (true)
	{
		capture.read(frame); //��ȡ��Ƶ
		//flip(frame, frame, 1);//ͼ�������
		if (frame.empty())//�����ƵΪ�յĻ� ��������
		{
			break;
		}
		imshow("frame", frame);//��ʾ��Ƶ
		colorSpace_Demo(frame, & hsv, &gray);//����Ƶ����֮ǰ��demo
		int c = waitKey(1);//ͣ��100ms ����Ƶ������1
		if (c == 27) { //esc �˳�Ӧ�ó���
			break;
		}
	}
	capture.release();//�ͷ��������Դ
}

//23 ��Ƶ ���� ���� ����
void QuickDemo::video_demo(Mat& image)
{

	VideoCapture capture("E:/videos/opencv/origin.mp4");
	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);//��ȡ��Ƶ�Ŀ��
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);//��ȡ��Ƶ�ĸ߶�
	int count = capture.get(CAP_PROP_FRAME_COUNT);//��Ƶ�ܵ�֡��	
	double fps = capture.get(CAP_PROP_FPS);//fps�Ǻ���������Ƶ������
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

	//����1 �����ַ������2 ��ȡͼƬ�ĸ�ʽ 
	//����3 ͼƬ��֡�� ����4 ��Ƶ��� ����5 ��
	Mat frame;
	Mat gray;
	Mat hsv;
	while (true)
	{
		capture.read(frame);
		//flip(frame, frame, 1);//ͼ�������
		if (frame.empty())
		{
			break;
		}
		imshow("frame", frame);
		colorSpace_Demo(frame,&hsv,&gray); //����ָ������������

		framewriter.write(frame);
		graywriter.write(gray);
		hsvwriter.write(hsv);

		int c = waitKey(1);//ͣ��100ms ����Ƶ������1
		if (c == 27) { //esc �˳�Ӧ�ó���
			break;
		}
	}
	framewriter.release();
	graywriter.release();
	hsvwriter.release();
	//�ͷŴ�ŵ���Դ
}

//ASSIGN ����ʶ��
void QuickDemo::sift_demo(Mat& image)
{
	Mat imageL = imread("E:/pictures/opencv_img/test0.jpg");
	Mat imageR = rotate_demo(imageL);
	/*imshow("1", imageL);
	imshow("2", imageR);
	waitKey();
	return 0;*/



	//��ȡ�����㷽��
	//SIFT
	Ptr<SIFT> surf = cv::SIFT::create();
	//ORB
	//cv::Ptr<cv::ORB> orb = cv::ORB::create();
	//SURF
	//cv::Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create();

	//������
	std::vector<cv::KeyPoint> keyPointL, keyPointR;
	//������ȡ������
	surf->detect(imageL, keyPointL);
	surf->detect(imageR, keyPointR);

	//��������
	cv::Mat keyPointImageL;
	cv::Mat keyPointImageR;
	drawKeypoints(imageL, keyPointL, keyPointImageL, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	drawKeypoints(imageR, keyPointR, keyPointImageR, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	//��ʾ����
	cv::namedWindow("KeyPoints of imageL", WINDOW_FREERATIO);
	cv::namedWindow("KeyPoints of imageR", WINDOW_FREERATIO);

	//��ʾ������
	cv::imshow("KeyPoints of imageL", keyPointImageL);
	cv::imshow("KeyPoints of imageR", keyPointImageR);

	//������ƥ��
	cv::Mat despL, despR;
	//��ȡ�����㲢��������������
	surf->detectAndCompute(imageL, cv::Mat(), keyPointL, despL);
	surf->detectAndCompute(imageR, cv::Mat(), keyPointR, despR);

	//Struct for DMatch: query descriptor index, train descriptor index, train image index and distance between descriptors.
	//int queryIdx �C>�ǲ���ͼ����������������� descriptor �����±꣬ͬʱҲ����������Ӧ�����㣨keypoint)���±ꡣ
	//int trainIdx �C> ������ͼ������������������±꣬ͬ��Ҳ����Ӧ����������±ꡣ
	//int imgIdx �C>�������Ƕ���ͼ��Ļ����á�
	//float distance �C>������һ��ƥ�������������������������������ŷ�Ͼ��룬��ֵԽСҲ��˵������������Խ����
	std::vector<cv::DMatch> matches;

	//������� flannBased ���� ��ô despͨ��orb�ĵ������Ͳ�ͬ��Ҫ��ת������
	if (despL.type() != CV_32F || despR.type() != CV_32F)
	{
		despL.convertTo(despL, CV_32F);
		despR.convertTo(despR, CV_32F);
	}

	cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("FlannBased");
	matcher->match(despL, despR, matches);

	//�����������������ֵ 
	double maxDist = 0;
	for (int i = 0; i < despL.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist > maxDist)
			maxDist = dist;
	}

	//��ѡ�õ�ƥ���
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

//24ͼ��ֱ��ͼ
void QuickDemo::histogram_demo(Mat& image) 
{
	// ��ͨ������
	std::vector<Mat> bgr_plane;
	split(image, bgr_plane);
	// �����������
	const int channels[1] = { 0 };
	const int bins[1] = { 256 };
	float hranges[2] = { 0,255 };
	const float* ranges[1] = { hranges };
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	// ����Blue, Green, Redͨ����ֱ��ͼ
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);

	// ��ʾֱ��ͼ
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	// ��һ��ֱ��ͼ����
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	// ����ֱ��ͼ����
	for (int i = 1; i < bins[0]; i++) {
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	}
	// ��ʾֱ��ͼ
	namedWindow("Histogram Demo", WINDOW_AUTOSIZE);
	imshow("Histogram Demo", histImage);
}

void QuickDemo::temp_match_demo(Mat& image) {

	Mat srcImg = imread("E:/pictures/opencv_img/target.jpg" );
	Mat tempImg = imread("E:/pictures/opencv_img/keys.jpg" );
	//1.�������ͼ��resultImg(ע���С������)
	//���ԭͼ(������ͼ��)�ߴ�ΪW x H, ��ģ��ߴ�Ϊ w x h, ����ͼ��ߴ�һ����(W-w+1)x(H-h+1)
	//���ͼ�����Ϊ��ͨ��32λ������ͼ��
	int width = srcImg.cols - tempImg.cols + 1;
	int height = srcImg.rows - tempImg.rows + 1;
	Mat resultImg(Size(width, height), CV_32FC1);
	//2.ģ��ƥ��
	matchTemplate(srcImg, tempImg, resultImg, TM_CCOEFF_NORMED);
	imshow("result", resultImg);
	//3.����(��һ����0-1)
	normalize(resultImg, resultImg, 0, 1, NORM_MINMAX, -1);
	//4.����resultImg������ɸѡ������ɸѡ��ǰ����ƥ��λ��
	int tempX = 0;
	int tempY = 0;
	char prob[10] = { 0 };
	//4.1����resultImg
	for (int i = 0; i < resultImg.rows; i++)
	{
		for (int j = 0; j < resultImg.cols; j++)
		{
			//4.2���resultImg��(j,x)λ�õ�ƥ��ֵmatchValue
			double matchValue = resultImg.at<float>(i, j);
			//sprintf(prob, "%.2f", matchValue);
			//4.3����ɸѡ����
			//����1:����ֵ����0.9
			//����2:�κ�ѡ�еĵ���x�����y�����϶�Ҫ����һ�����5(���⻭�߿���Ӱ�����)
			if (matchValue > 0.7 && abs(i - tempY) > 5 && abs(j - tempX) > 5)
			{
				//5.��ɸѡ���ĵ㻭���߿������
				rectangle(srcImg, Point(j, i), Point(j + tempImg.cols, i + tempImg.rows), Scalar(0, 255, 0), 1, 8);
				tempX = j;
				tempY = i;
			}
		}
	}
	imshow("srcImg", srcImg);
	imshow("template", tempImg);


}
//������Ƶ
void QuickDemo::accel_video(Mat& image)
{

	VideoCapture capture("E:/Videos/SF/output/01.mp4");

	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);//��ȡ��Ƶ�Ŀ��
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);//��ȡ��Ƶ�ĸ߶�
	int count = capture.get(CAP_PROP_FRAME_COUNT);//��Ƶ�ܵ�֡��	
	double fps = capture.get(CAP_PROP_FPS);//fps�Ǻ���������Ƶ������


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


		//��Esc���˳�while
		int c = waitKey(1);// ����Ƶ������1
		if (c == 27) 
		{ //esc �˳�Ӧ�ó���
			break;
		}

	}
		framewriter.release();

	//getchar();
}

//�ָ����

Mat QuickDemo::for_background(Mat  IMG, cv::Point_<int> center, int in_r,int out_r)
{    

	// �ú�inner
	Mat in_roi = Mat::zeros(IMG.size(), IMG.type());
	in_roi.setTo(255);
	Mat copy_img;
	IMG.copyTo(copy_img);
	const cv::Scalar color = (0,0,0);
	circle(in_roi, center, in_r, color, -1);
	Mat black_in;
	bitwise_and (in_roi,copy_img,black_in);
	// �ú�outer
	Mat out_roi = Mat::zeros(IMG.size(), IMG.type());
	out_roi.setTo(0);
	circle(out_roi, center, out_r, Scalar(255, 255, 255), -1);
	Mat ring;
	bitwise_and(out_roi,black_in,ring);
	return ring;
}
//��Բ��
Mat  QuickDemo::reduce_circle_domin(Mat  img, cv::Point_<int> c_point, int c_r)
{         // ����ͼ�� λ�� Բ�İ뾶 �����Բ
	Mat circle_roi = Mat::zeros(img.size(), img.type());  //[2592 x 1944]
	Mat copy_img = img.clone();
	circle(circle_roi, c_point, c_r, Scalar(255, 255, 255), -1);
	


	Mat reduce_img;
	copy_img.copyTo(reduce_img, circle_roi);


	return reduce_img;
}
// ������ ������
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
//���׶�
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



//��Բ�����ĺ��ھ�

pair<Point2f, float>  QuickDemo::find_point(Mat orig_img)
{
	Mat copy_img = orig_img.clone();
	//���ָ���Ȥ����
	Mat roi = reduce_circle_domin(copy_img,Point(1210,990),980);  //[2592 x 1944]

	//ֱ��ͼ��ֵ��
	Mat equal0;
	equalizeHist(roi, equal0);

	
	//��ֵ��
	Mat binary, thresh;
	threshold(equal0, binary,220,255, THRESH_TOZERO_INV);
	threshold(binary, thresh, 65, 255, THRESH_BINARY);


	
	//��̬ѧ���� ������
	Mat close0 = closing_ellipse(thresh,Point(15,15),1);
	//���׶�
	Mat Fill_IMG = fill_hole(close0);
	//������
	Mat open0 = opening_ellipse(Fill_IMG, Point(15, 15), 1);

	vector<vector<Point>> contours;
    findContours(open0.clone(),contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
	vector<int> area = {};
	//�ҵ��������
	int length = size(contours);
	for (int k = 0; k < length - 1; k++)
	{
		area.push_back(contourArea(contours[k]));
	}
	int max_idx = 2;//max_element(area.begin(), area.end()) - area.begin();
	//����ʵ�ʵ����ĵ�뾶������
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
	//��ȡԲ��
	Mat ring = for_background(img, Point_<int> (x,y),in_r,out_r);
	//��˹ģ��������Ѱ�ұ�Ե
	Mat ring_blur;
	blur(ring, ring_blur,Point(5,5));
	//��Ե��⣬Ѱ�һ���
	Canny(ring_blur,ring,50,240);
	//Բ���ı�ԵҲ�п��ܱ���ʶ��Ϊ��Ե�������Ҫ��֮ǰʶ�𵽵�Բ��λ������Բ���߽磬ͻ������
	Mat remove_roi_out = Mat::zeros(ring.size(), ring.type());
	remove_roi_out.setTo(255);
	Scalar color_out = (0, 0, 0);
	circle(remove_roi_out, Point_<int>(x, y), out_r, color_out,4);
	circle(remove_roi_out, Point_<int>(x, y), in_r, color_out,4);
	bitwise_and(remove_roi_out, ring, ring);
	Mat scratch = closing_ellipse(ring, Point_<int>(15, 15), 1);
	//�ҵ���������������С��Ӿ����������ĳ���
	vector<vector<Point>> contours;
	findContours(scratch, contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
	vector<int> area = {};
	//�ҵ��������
	int length = size(contours);
	for (int k = 0; k < length - 1; k++)
	{
		area.push_back(contourArea(contours[k]));
	}
	namedWindow("debug", 0);
	imshow("debug", scratch);
	int max_idx = max_element(area.begin(), area.end())- area.begin();
	//����ͼ���ϵĳ�
	RotatedRect rect = minAreaRect(contours[max_idx]);
	Mat box, Cov;
	boxPoints(rect, box);
	box.assignTo(Cov, CV_32S);
	//��ָ����С��ʾ
	int w = original_img.cols;
	int h = original_img.rows;
	float f1 = 1.0 * 1000.0 / w;
	float f2 = 1.0 * 1000.0 / h;
	float factor = min(f1,f2);
	int width = int(w * factor);
	int height = int(h * factor);
	//�����ο�
	polylines(original_img, Cov, true, Scalar(0, 0, 255),2);
	//drawContours(original_img, Cov,0, Scalar(0,0,255),2);
	//���εĳ���
	float length_pixel = rect.size.height;
	cout <<"������С��Ӿ��γ���" << length_pixel <<"mm" << endl;
	//���ƻ���ʵ�ʳ���
	cout << "����ʵ�ʳ���" << length_pixel * 0.4 << "mm" << endl;
	resize(original_img, original_img, Size(width, height));
	//��ʾ���ۼ���
	imshow("rect", original_img);


}






