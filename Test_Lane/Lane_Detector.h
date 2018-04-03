#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>



#define TH_LOWER_WHITE Scalar(0,0,100)
#define TH_UPPER_WHITE Scalar(180,100,255)
#define SET_FAR_LANE 100
//width and height 
#define VIDEO_WIDTH_FRAME 320
#define VIDEO_HEIGHT_FRAME 240


//set region lane 
#define LEFT_UP Point(20,120)
#define LEFT_DOWN Point(0,240)
#define RIGHT_UP Point(300,120)
#define RIGHT_DOWN Point(320,240)
//Canny edge index
#define TH_LOWER_EDGE 100
#define RATIO 3
#define KERNEL_SIZE 3

//set houghlineP

#define RHO 1
#define THREH 50
#define MIN_LENTH 50
#define MAX_GAP 10

using namespace std;
using namespace cv;

class Lane_Detector
{
private:
	double theta;
public:
	Lane_Detector();
	~Lane_Detector();

	void Detect_Not_Lane(Mat& grayImage);
	void Detect_White_Lane(Mat&);
	void Process_Lane_binImg(Mat&);
	double getTheta();
};