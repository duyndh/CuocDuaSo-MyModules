// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include "Lane_Detector.h"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace std;
using namespace cv;



int main()
{
	Mat proImg, grayImage;
	grayImage = imread("source/image.png");
	cvtColor(grayImage, grayImage, CV_BGR2GRAY);
	resize(grayImage, grayImage, Size(320, 240));
	imshow("Image", grayImage);


	Lane_Detector dtl;
	dtl.Detect_Not_Lane(grayImage);
	cout << "Theta: " << dtl.getTheta() << endl;
	/*
	int _TH_LOWER_EDGE = 100;
	int _RATIO = 3;
	int _KERNEL_SIZE = 3;
	

	proImg = grayImage;
	//equalize histogram
	equalizeHist(grayImage, proImg);
	imshow("equalHist", proImg);
	//process candy edge detection
	//-----------reduce noisy
	blur(proImg, proImg, Size(2, 2));
	//------------edge detection
	namedWindow("EDGE");
	createTrackbar("THRESH", "EDGE", &_TH_LOWER_EDGE, 150);
	createTrackbar("RATIO", "EDGE", &_RATIO, 5);
	createTrackbar("KERNEL", "EDGE", &_KERNEL_SIZE, 5);
	Canny(proImg, proImg, _TH_LOWER_EDGE, _TH_LOWER_EDGE*_RATIO, _KERNEL_SIZE);
	imshow("EDGE", proImg);
	
	Mat hImg = proImg;
	int _RHO = 1;
	int _THREH = 50;
	int _MIN_LENTH = 50;
	int _MAX_GAP = 70;
	
	namedWindow("HOUGHLINE");


	createTrackbar("RHO", "HOUGHLINE", &_RHO, 10);
	createTrackbar("THRESH", "HOULINE", &_THREH, 150);
	createTrackbar("_MIN_LENGTH", "HOUGHLINE", &_MIN_LENTH, 150);
	createTrackbar("_MAX_GAP", "HoughLINE", &_MAX_GAP, 150);

	vector<Vec4i> lines;
	HoughLinesP(hImg, lines, _RHO, CV_PI / 180, _THREH, _MIN_LENTH, _MAX_GAP);

	for (int i = 0; i < lines.size(); i++)
		Draw_Line(hImg, lines[i]);


	//houghlineP
	
	imshow("HOUGHLINE", hImg);
	*/
	waitKey(0);
    return 0;
}

