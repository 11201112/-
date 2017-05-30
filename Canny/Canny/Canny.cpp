//// Canny.cpp : 定义控制台应用程序的入口点。
////
//..........................................代码一...............................................
//#include "stdafx.h"
//#include <iostream>
//#include "cv.h" 
//#include "highgui.h"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv_tool.hpp" 
//
//using namespace std;
//using namespace cv;
//
////TrackBar发生改变的回调函数  
//void onChangeTrackBar1(int pos, void* userdata);
//Mat src;
//int main(int argc, char *argv[])
//{
//	int alpha = 0;
//	// Read image
//	src = imread("stuff.jpg", CV_LOAD_IMAGE_COLOR);
//	if (!src.data) {
//		cout << "Error: read image" << endl;
//		return 0
//			;
//	}
//	namedWindow("Canny", CV_WINDOW_AUTOSIZE);
//	createTrackbar("Threshold1", "Canny", &alpha, 255, onChangeTrackBar1);
//	onChangeTrackBar1(0, 0);
//	waitKey(0);
//	return 0;
//}
//// 回调函数  
//void onChangeTrackBar1(int pos, void* usrdata)
//{
//	vector<vector<Point> > contours;
//
//	Mat image = src >= pos;
//	//cvtColor(src, src, CV_RGB2GRAY);
//	//namedWindow("Origin", CV_WINDOW_AUTOSIZE);
//	//imshow("Origin", src);
//
//	//Mat dst;
//	//GaussianBlur(src, dst, Size(3, 3), 0, 0);  // 使用Gaussian滤波器进行平滑
//	//Canny(dst, dst, pos, 255, 3);
//	//imshow("Canny", dst);
//
//	findContours(image, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
//	Mat cimage = Mat::zeros(image.size(), CV_8UC3);
//	for (int i = 0; i < contours.size(); i++)
//	{
//		//轮廓的边缘点个数  
//		int count = contours[i].size();
//		//Fitzgibbon的椭圆拟合方法，要求至少6个点，文献：Direct Least Squares Fitting of Ellipses[1999]  
//		if (count < 6)
//			continue;
//
//		Mat pointsf;
//		//将轮廓中的点转换为以Mat形式存储的2维点集(x,y)  
//		Mat(contours[i]).convertTo(pointsf, CV_32F);
//
//		//最小二次拟合（Fitzgibbon的方法）  
//		//box包含了椭圆的5个参数：(x,y,w,h,theta)  
//		RotatedRect box = fitEllipse(pointsf);
//
//		//把那些长轴与短轴之比很多的那些椭圆剔除。  
//		if (MAX(box.size.width, box.size.height) > MIN(box.size.width, box.size.height) * 8)
//			continue;
//		//绘制轮廓  
//		drawContours(cimage, contours, (int)i, Scalar::all(255), 1, 8);
//
//		//绘制椭圆  
//		ellipse(cimage, box, Scalar(0, 0, 255), 1, CV_AA);
//		//绘制椭圆  
//		// ellipse(cimage, box.center, box.size*0.5f, box.angle, 0, 360, Scalar(0,255,255), 1, CV_AA);  
//
//		//绘制矩形框  
//		Point2f vtx[4];
//		//成员函数points 返回 4个矩形的顶点(x,y)  
//		box.points(vtx);
//		for (int j = 0; j < 4; j++)
//			line(cimage, vtx[j], vtx[(j + 1) % 4], Scalar(0, 255, 0), 1, CV_AA);
//	}
//
//	imshow("result", cimage);
//
//}
/********************************************************************************
*
*
*  This program is demonstration for ellipse fitting. Program finds
*  contours and approximate it by ellipses.
*
*  Trackbar specify threshold parametr.
*
*  White lines is contours. Red lines is fitting ellipses.
*
*
*  Autor:  Denis Burenkov.
*
*
*
******************************************代码二**************************************/
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "stdafx.h"
//#include "cv.h" 
//#include "highgui.h"
//#include "opencv_tool.hpp" 
//#include <iostream>
//using namespace cv;
//using namespace std;
//
//// static void help()
//// {
////     cout <<
////             "\nThis program is demonstration for ellipse fitting. The program finds\n"
////             "contours and approximate it by ellipses.\n"
////             "Call:\n"
////             "./fitellipse [image_name -- Default stuff.jpg]\n" << endl;
//// }
//
//int sliderPos = 70;
//
//Mat image;
//
//void processImage(int, void*);
//
//int main(int argc, char** argv)
//{
//	const char* filename = argc == 2 ? argv[1] : (char*)"2.jpg";
//	image = imread(filename, 0);
//	if (image.empty())
//	{
//		cout << "Couldn't open image " << filename << "\nUsage: fitellipse <image_name>\n";
//		return 0;
//	}
//	GaussianBlur(image, image, Size(3, 3), 0, 0);  // 使用Gaussian滤波器进行平滑
//	imshow("source", image);
//	namedWindow("result", 1);
//
//	// Create toolbars. HighGUI use.
//	createTrackbar("threshold", "result", &sliderPos, 255, processImage);
//	processImage(0, 0);
//
//	// Wait for a key stroke; the same function arranges events processing
//	waitKey();
//	return 0;
//}
//
//// Define trackbar callback functon. This function find contours,
//// draw it and approximate it by ellipses.
//void processImage(int /*h*/, void*)
//{
//	vector<vector<Point> > contours;
//	Mat bimage = image >= sliderPos;
//
//	findContours(bimage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
//
//	Mat cimage = Mat::zeros(bimage.size(), CV_8UC3);
//
//	for (size_t i = 0; i < contours.size(); i++)
//	{
//		size_t count = contours[i].size();
//		if (count < 6)
//			continue;
//
//		Mat pointsf;
//		Mat(contours[i]).convertTo(pointsf, CV_32F);
//		RotatedRect box = fitEllipse(pointsf);
//
//		if (MAX(box.size.width, box.size.height) > MIN(box.size.width, box.size.height) * 30)
//			continue;
//		drawContours(cimage, contours, (int)i, Scalar::all(255), 1, 8);
//
//		ellipse(cimage, box, Scalar(0, 0, 255), 1, CV_AA);
//		ellipse(cimage, box.center, box.size*0.5f, box.angle, 0, 360, Scalar(0, 255, 255), 1, CV_AA);
//		Point2f vtx[4];
//		box.points(vtx);
//		for (int j = 0; j < 4; j++)
//			line(cimage, vtx[j], vtx[(j + 1) % 4], Scalar(0, 255, 0), 1, CV_AA);
//	}
//
//	imshow("result", cimage);
//}
//................................................代码三..........................................
using namespace cv;
using namespace std;
#include "stdafx.h"  
#include "cxcore.h"  
#include "highgui.h""  
#include <math.h>  
#include "cv.h"  
#include <stdio.h>  
#include "opencv_tool.hpp" 

using namespace cv;
using namespace std;

int sliderPos = 30;
IplImage* image = cvLoadImage("123.jpg");
IplImage* gray;                   /*保存灰度图*/
IplImage* threshold_image;
IplImage* result;                 /*保存结果*/

void processImage(int, void*);
int main(int argc, char** argv)
{
	cvNamedWindow("原图", 1);
	cvNamedWindow("拟合", 1);         /*窗口命名*/
	cvNamedWindow("阈值化", 1);
	cvNamedWindow("灰度图", 1);
	/****************1.读取图像和图像预处理****************/

	gray = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);  /*创建输出图像，位无符号深度，通道*/
	
	
	cvZero(result);

	createTrackbar("threshold", "拟合", &sliderPos, 255, processImage);
	processImage(0, 0);
	

	// Wait for a key stroke; the same function arranges events processing     
	cvWaitKey(0);
	cvReleaseImage(&image);//释放图片资源  
	cvReleaseImage(&result);

	cvDestroyWindow("原图");//销毁窗口  
	cvDestroyWindow("拟合");
	return 0;
}

void processImage(int /*h*/, void*)
{
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq *contour;
	result = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);  /*创建输出图像，位无符号深度，通道*/
	threshold_image = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
	int count;
	CvPoint *PointArray;
	CvPoint center;
	CvPoint2D32f *PointArray2D32f;

	/* 创建动态结构序列*/
	storage = cvCreateMemStorage(0);
	contour = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), storage);
	CvBox2D *box;
	CvSize size;

	/****************2.将图像转换为二值图像****************/

	cvCvtColor(image, gray, CV_BGR2GRAY);      /*把image转换成灰度放到gray中*/
	cvSmooth(gray, gray);
	cvThreshold(gray, threshold_image, sliderPos, 255, THRESH_BINARY);      /*将灰度图像二值化,需要针对输入图像进行调整,seal1时对应(195, 255),seal2时对应(190, 255),coin1时对应(70, 200)*/

	/****************3.抽取图像中对象的轮廓属性**********************************************/

	cvFindContours(threshold_image, storage, &contour, sizeof(CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);  /*找轮廓*/
	/*遍历每个轮廓*/
	printf("该阈值下拟合结果：\n");
	printf("*******************************************************************************\n");
	for (; contour; contour = contour->h_next){
		count = contour->total;
		if (count<250 || count>500)        /*去掉轮廓小于一定数值的圆,要根据输入图像进行调整,seal1时对应250,seal2时对应160,coin1时对应75*/
			continue;
		// Alloc memory for contour point set.    
		PointArray = (CvPoint*)malloc(count*sizeof(CvPoint));
		PointArray2D32f = (CvPoint2D32f*)malloc(count*sizeof(CvPoint2D32f));

		// Alloc memory for ellipse data.  
		box = (CvBox2D32f*)malloc(sizeof(CvBox2D32f));
		/*格式转化，contour -- PointArray -- PointArray2D32f*/
		cvCvtSeqToArray(contour, PointArray, CV_WHOLE_SEQ);
		for (int i = 0; i<count; i++)
		{
			PointArray2D32f[i].x = (float)PointArray[i].x;
			PointArray2D32f[i].y = (float)PointArray[i].y;
		}

		/****************4.椭圆拟合****************/

		cvFitEllipse(PointArray2D32f, count, box);  /*拟合椭圆*/

		center.x = cvRound(box->center.x);     /*确定椭圆box的值center、size、angle*/
		center.y = cvRound(box->center.y);
		size.width = cvRound(box->size.width*0.5);
		size.height = cvRound(box->size.height*0.5);
		box->angle = -box->angle;

		if (size.width > 100 || size.height > 100)  //拟合出了错误的形状
			continue;
		cvDrawContours(threshold_image, contour, CV_RGB(255, 255, 255), CV_RGB(255, 255, 255), 0, 2, 8, cvPoint(0, 0)); /*画轮廓到阈值化的图片上*/
		cvEllipse(result, center, size, box->angle, 0, 360, CV_RGB(0, 0, 0), 5, CV_AA, 0);   /*画椭圆到result*/

		/****************5.输出结果*********************/
		
		printf("中心位置：x=%d,y=%d\n", center.x, center.y);  /*输出中心位置*/
		printf("半径或长短轴长度：w=%d,h=%d\n", size.width, size.height);  /*输出半径或长短轴长度*/
		printf("---------------------------------------------------------------------\n");/*不同圆或椭圆数据输出分割线*/
		/*释放空间*/
		free(PointArray);
		free(PointArray2D32f);
		free(box);
	}
	/*图像输出*/
	cvShowImage("原图", image);
	cvSaveImage("拟合.jpg", result);/*将图片保存到本地*/
	//	cvNamedWindow("拟合", 1);/*窗口命名*/
	cvShowImage("拟合", result);/*显示图片*/
	cvShowImage("阈值化", threshold_image);
	cvShowImage("灰度图", gray);
}