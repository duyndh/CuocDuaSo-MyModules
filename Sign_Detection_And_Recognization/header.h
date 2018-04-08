#ifndef __HEARDER_H__
#define __HEADER_H__

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/ml.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <math.h>

using namespace cv;
using namespace std;
using namespace cv::ml;

#define FRAME_WIDTH 320
#define FRAME_HEIGHT 240

#define LOW_HSV_BLUE Scalar(100, 100, 100)
#define HIG_HSV_BLUE Scalar(120, 255, 255)

#define LOW_HSV_RED1 Scalar(0, 120, 120)
#define HIG_HSV_RED1 Scalar(10, 255, 255)
#define LOW_HSV_RED2 Scalar(170, 120, 120)
#define HIG_HSV_RED2 Scalar(180, 255, 255)

#define LOW_HSV_GREEN Scalar(34, 138, 12)
#define HIG_HSV_GREEN Scalar(83, 246, 124)

#define KERNEL_SIZE 5
#define SIGN_SIZE 48
#define DIF_RATIO_SIGN_WIDTH_PER_HEIGHT 0.2
#define DIF_RATIO_SIGN_AREA 0.1
#define MIN_SIGN_AREA 1800

#define NO_SIGN 0
#define SIGN_STOP 1
#define SIGN_LEFT 2
#define SIGN_RIGHT 3

#endif