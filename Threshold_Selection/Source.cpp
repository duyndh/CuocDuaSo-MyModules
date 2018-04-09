#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/ml.hpp>

#include <iostream>

using namespace cv;
using namespace std;
using namespace cv::ml;

#define FRAME_WIDTH 320
#define FRAME_HEIGHT 240

int low_h = 30, low_s = 30, low_v = 30;
int high_h = 100, high_s = 100, high_v = 100;

void hist_equalize(Mat &img)
{
	Mat ycrcb;
	cvtColor(img, ycrcb, CV_BGR2YCrCb);

	vector<Mat> chanels(3);
	split(ycrcb, chanels);

	Ptr<CLAHE> clahe = createCLAHE(2.0, Size(8, 8));
	clahe->apply(chanels[0], chanels[0]);

	merge(chanels, ycrcb);
	cvtColor(ycrcb, img, CV_YCrCb2BGR);
}

void on_low_h_thresh_trackbar(int, void *)
{
	low_h = min(high_h - 1, low_h);
	setTrackbarPos("Low H", "Object Detection", low_h);
}

void on_high_h_thresh_trackbar(int, void *)
{
	high_h = max(high_h, low_h + 1);
	setTrackbarPos("High H", "Object Detection", high_h);
}

void on_low_s_thresh_trackbar(int, void *)
{
	low_s = min(high_s - 1, low_s);
	setTrackbarPos("Low S", "Object Detection", low_s);
}

void on_high_s_thresh_trackbar(int, void *)
{
	high_s = max(high_s, low_s + 1);
	setTrackbarPos("High G", "Object Detection", high_s);
}

void on_low_v_thresh_trackbar(int, void *)
{
	low_v = min(high_v - 1, low_v);
	setTrackbarPos("Low B", "Object Detection", low_v);
}

void on_high_v_thresh_trackbar(int, void *)
{
	int high_v = max(high_v, low_v + 1);
	setTrackbarPos("High B", "Object Detection", high_v);
}

int main()
{
	Mat frame, hsv, mask;
	VideoCapture cap(0);

	namedWindow("Threshold Selection", WINDOW_NORMAL);

	createTrackbar("Low H", "Threshold Selection", &low_h, 255, on_low_h_thresh_trackbar);
	createTrackbar("High H", "Threshold Selection", &high_h, 255, on_high_h_thresh_trackbar);
	createTrackbar("Low S", "Threshold Selection", &low_s, 255, on_low_s_thresh_trackbar);
	createTrackbar("High S", "Threshold Selection", &high_s, 255, on_high_s_thresh_trackbar);
	createTrackbar("Low V", "Threshold Selection", &low_v, 255, on_low_v_thresh_trackbar);
	createTrackbar("High V", "Threshold Selection", &high_v, 255, on_high_v_thresh_trackbar);
	
	while ((char)waitKey(1) != 'q')
	{
		cap >> frame;
		if (frame.empty())
			break;

		resize(frame, frame, Size(FRAME_WIDTH, FRAME_HEIGHT));
		hist_equalize(frame);

		cvtColor(frame, hsv, COLOR_BGR2HSV);

		inRange(hsv, Scalar(low_h, low_s, low_v), Scalar(high_h, high_s, high_v), mask);
		
		imshow("frame", frame);
		imshow("mask", mask);
	}	

	return 0;
}