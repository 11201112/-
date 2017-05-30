//// Canny.cpp : �������̨Ӧ�ó������ڵ㡣
////
//..........................................����һ...............................................
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
////TrackBar�����ı�Ļص�����  
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
//// �ص�����  
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
//	//GaussianBlur(src, dst, Size(3, 3), 0, 0);  // ʹ��Gaussian�˲�������ƽ��
//	//Canny(dst, dst, pos, 255, 3);
//	//imshow("Canny", dst);
//
//	findContours(image, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
//	Mat cimage = Mat::zeros(image.size(), CV_8UC3);
//	for (int i = 0; i < contours.size(); i++)
//	{
//		//�����ı�Ե�����  
//		int count = contours[i].size();
//		//Fitzgibbon����Բ��Ϸ�����Ҫ������6���㣬���ף�Direct Least Squares Fitting of Ellipses[1999]  
//		if (count < 6)
//			continue;
//
//		Mat pointsf;
//		//�������еĵ�ת��Ϊ��Mat��ʽ�洢��2ά�㼯(x,y)  
//		Mat(contours[i]).convertTo(pointsf, CV_32F);
//
//		//��С������ϣ�Fitzgibbon�ķ�����  
//		//box��������Բ��5��������(x,y,w,h,theta)  
//		RotatedRect box = fitEllipse(pointsf);
//
//		//����Щ���������֮�Ⱥܶ����Щ��Բ�޳���  
//		if (MAX(box.size.width, box.size.height) > MIN(box.size.width, box.size.height) * 8)
//			continue;
//		//��������  
//		drawContours(cimage, contours, (int)i, Scalar::all(255), 1, 8);
//
//		//������Բ  
//		ellipse(cimage, box, Scalar(0, 0, 255), 1, CV_AA);
//		//������Բ  
//		// ellipse(cimage, box.center, box.size*0.5f, box.angle, 0, 360, Scalar(0,255,255), 1, CV_AA);  
//
//		//���ƾ��ο�  
//		Point2f vtx[4];
//		//��Ա����points ���� 4�����εĶ���(x,y)  
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
******************************************�����**************************************/
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
//	GaussianBlur(image, image, Size(3, 3), 0, 0);  // ʹ��Gaussian�˲�������ƽ��
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
//................................................������..........................................
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
IplImage* gray;                   /*����Ҷ�ͼ*/
IplImage* threshold_image;
IplImage* result;                 /*������*/

void processImage(int, void*);
int main(int argc, char** argv)
{
	cvNamedWindow("ԭͼ", 1);
	cvNamedWindow("���", 1);         /*��������*/
	cvNamedWindow("��ֵ��", 1);
	cvNamedWindow("�Ҷ�ͼ", 1);
	/****************1.��ȡͼ���ͼ��Ԥ����****************/

	gray = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);  /*�������ͼ��λ�޷�����ȣ�ͨ��*/
	
	
	cvZero(result);

	createTrackbar("threshold", "���", &sliderPos, 255, processImage);
	processImage(0, 0);
	

	// Wait for a key stroke; the same function arranges events processing     
	cvWaitKey(0);
	cvReleaseImage(&image);//�ͷ�ͼƬ��Դ  
	cvReleaseImage(&result);

	cvDestroyWindow("ԭͼ");//���ٴ���  
	cvDestroyWindow("���");
	return 0;
}

void processImage(int /*h*/, void*)
{
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq *contour;
	result = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);  /*�������ͼ��λ�޷�����ȣ�ͨ��*/
	threshold_image = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
	int count;
	CvPoint *PointArray;
	CvPoint center;
	CvPoint2D32f *PointArray2D32f;

	/* ������̬�ṹ����*/
	storage = cvCreateMemStorage(0);
	contour = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), storage);
	CvBox2D *box;
	CvSize size;

	/****************2.��ͼ��ת��Ϊ��ֵͼ��****************/

	cvCvtColor(image, gray, CV_BGR2GRAY);      /*��imageת���ɻҶȷŵ�gray��*/
	cvSmooth(gray, gray);
	cvThreshold(gray, threshold_image, sliderPos, 255, THRESH_BINARY);      /*���Ҷ�ͼ���ֵ��,��Ҫ�������ͼ����е���,seal1ʱ��Ӧ(195, 255),seal2ʱ��Ӧ(190, 255),coin1ʱ��Ӧ(70, 200)*/

	/****************3.��ȡͼ���ж������������**********************************************/

	cvFindContours(threshold_image, storage, &contour, sizeof(CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);  /*������*/
	/*����ÿ������*/
	printf("����ֵ����Ͻ����\n");
	printf("*******************************************************************************\n");
	for (; contour; contour = contour->h_next){
		count = contour->total;
		if (count<250 || count>500)        /*ȥ������С��һ����ֵ��Բ,Ҫ��������ͼ����е���,seal1ʱ��Ӧ250,seal2ʱ��Ӧ160,coin1ʱ��Ӧ75*/
			continue;
		// Alloc memory for contour point set.    
		PointArray = (CvPoint*)malloc(count*sizeof(CvPoint));
		PointArray2D32f = (CvPoint2D32f*)malloc(count*sizeof(CvPoint2D32f));

		// Alloc memory for ellipse data.  
		box = (CvBox2D32f*)malloc(sizeof(CvBox2D32f));
		/*��ʽת����contour -- PointArray -- PointArray2D32f*/
		cvCvtSeqToArray(contour, PointArray, CV_WHOLE_SEQ);
		for (int i = 0; i<count; i++)
		{
			PointArray2D32f[i].x = (float)PointArray[i].x;
			PointArray2D32f[i].y = (float)PointArray[i].y;
		}

		/****************4.��Բ���****************/

		cvFitEllipse(PointArray2D32f, count, box);  /*�����Բ*/

		center.x = cvRound(box->center.x);     /*ȷ����Բbox��ֵcenter��size��angle*/
		center.y = cvRound(box->center.y);
		size.width = cvRound(box->size.width*0.5);
		size.height = cvRound(box->size.height*0.5);
		box->angle = -box->angle;

		if (size.width > 100 || size.height > 100)  //��ϳ��˴������״
			continue;
		cvDrawContours(threshold_image, contour, CV_RGB(255, 255, 255), CV_RGB(255, 255, 255), 0, 2, 8, cvPoint(0, 0)); /*����������ֵ����ͼƬ��*/
		cvEllipse(result, center, size, box->angle, 0, 360, CV_RGB(0, 0, 0), 5, CV_AA, 0);   /*����Բ��result*/

		/****************5.������*********************/
		
		printf("����λ�ã�x=%d,y=%d\n", center.x, center.y);  /*�������λ��*/
		printf("�뾶�򳤶��᳤�ȣ�w=%d,h=%d\n", size.width, size.height);  /*����뾶�򳤶��᳤��*/
		printf("---------------------------------------------------------------------\n");/*��ͬԲ����Բ��������ָ���*/
		/*�ͷſռ�*/
		free(PointArray);
		free(PointArray2D32f);
		free(box);
	}
	/*ͼ�����*/
	cvShowImage("ԭͼ", image);
	cvSaveImage("���.jpg", result);/*��ͼƬ���浽����*/
	//	cvNamedWindow("���", 1);/*��������*/
	cvShowImage("���", result);/*��ʾͼƬ*/
	cvShowImage("��ֵ��", threshold_image);
	cvShowImage("�Ҷ�ͼ", gray);
}