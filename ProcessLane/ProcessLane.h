#pragma once
#include <stdio.h>
#include<iostream>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#define OFFSET_DIVIDE 20
#define KERNEL_SIZE 5
#define	INPUT "Up5.png"
#define LOW_HSV Scalar(0, 0, 0)
#define HIG_HSV Scalar(180, 10, 255)


using namespace std;
using namespace cv;
class ProcessLane
{
private:
	Mat Image, Mask_Image;
public:
	ProcessLane();
	Mat get_mask(Mat img);
	Mat ConnectLine(Mat &mask, Mat Image);
	Mat Boundary(Mat &mask, Mat Image);
	~ProcessLane();
};