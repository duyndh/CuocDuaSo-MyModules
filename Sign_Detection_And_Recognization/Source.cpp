#include "sign.h"

int main()
{
	Mat frame;
	VideoCapture cap(0);
	
	Mat mask(FRAME_HEIGHT, FRAME_WIDTH, CV_8UC1);
	Mat gray(FRAME_HEIGHT, FRAME_WIDTH, CV_8UC1);
	Mat hsv(FRAME_HEIGHT, FRAME_WIDTH, CV_8UC3);
	Sign sign;

	double st = 0, et = 0, fps = 0;
	double freq = getTickFrequency();

	while ((char)waitKey(1) != 'q')
	{		
		st = getTickCount();

		cap >> frame;
		if (frame.empty())
			break;

		resize(frame, frame, Size(FRAME_WIDTH, FRAME_HEIGHT));
		hist_equalize(frame);
		
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		cvtColor(frame, hsv, COLOR_BGR2HSV);
		
		get_mask(hsv, mask, "blue red");
		
		if (sign.detect(mask))
		{
			sign.recognize(gray);
			switch (sign.getClassID())
			{
			case 1: cout << "SIGN LEFT\n";
				break;
			case 2: cout << "SIGN RIGHT\n";
				break;
			case 3: cout << "SIGN STOP\n";
				break;
			default: cout << "NO SIGN\n";
			}
		}

		imshow("frame", frame);
		imshow("mask", mask);

		et = getTickCount();
		fps = 1.0 / ((et - st) / freq);
		cerr << "FPS: " << fps << '\n';
	}

	return 0;
}