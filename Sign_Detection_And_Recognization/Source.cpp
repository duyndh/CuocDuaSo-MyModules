#include "header.h"
#include "sign.h"

// WARNING: should only be used once because of ycrcb equalization
void get_mask(const Mat &hsv, Mat &mask, string colors)
{
	mask = Mat::zeros(mask.rows, mask.cols, CV_8UC1);
	
	Mat tmp_mask(mask.rows, mask.cols, CV_8UC1);
	if (colors.find("blue") != std::string::npos)
	{
		inRange(hsv, LOW_HSV_BLUE, HIG_HSV_BLUE, tmp_mask);
		bitwise_or(mask, tmp_mask, mask);
	}	
	if (colors.find("red") != std::string::npos)
	{
		Mat tmp_mask1(mask.rows, mask.cols, CV_8UC1);
		Mat tmp_mask2(mask.rows, mask.cols, CV_8UC1);
		inRange(hsv, LOW_HSV_RED1, HIG_HSV_RED1, tmp_mask1);
		inRange(hsv, LOW_HSV_RED2, HIG_HSV_RED2, tmp_mask2);
		bitwise_or(tmp_mask1, tmp_mask2, mask);
	}
	if (colors.find("green") != std::string::npos)
	{
		inRange(hsv, LOW_HSV_GREEN, HIG_HSV_GREEN, tmp_mask);
		bitwise_or(mask, tmp_mask, mask);
	}

	Mat kernel = Mat::ones(KERNEL_SIZE, KERNEL_SIZE, CV_8UC1);

	dilate(mask, mask, kernel);
	morphologyEx(mask, mask, MORPH_CLOSE, kernel);
}

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


int main()
{
	Mat frame, frame_threshold;
	VideoCapture cap(0);
	
	Mat mask(FRAME_HEIGHT, FRAME_WIDTH, CV_8UC1);
	Mat gray(FRAME_HEIGHT, FRAME_WIDTH, CV_8UC1);
	Mat hsv(FRAME_HEIGHT, FRAME_WIDTH, CV_8UC3);
	Sign sign;

	while ((char)waitKey(1) != 'q')
	{
		cap >> frame;
		if (frame.empty())
			break;
		resize(frame, frame, Size(FRAME_WIDTH, FRAME_HEIGHT));
		
		hist_equalize(frame);
		
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		cvtColor(frame, hsv, COLOR_BGR2HSV);
		get_mask(hsv, mask, "blue");

		if (sign.detect(mask))
		{
			cout << "detected!\n";
			sign.recognize(gray);
			cout << sign.get_class_id() << endl;
		}

		imshow("hsv", hsv);
		imshow("frame", frame);
		imshow("mask", mask);
	}

	return 0;
}