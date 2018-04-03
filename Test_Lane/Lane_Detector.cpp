#include "stdafx.h"
#include "Lane_Detector.h"


Lane_Detector::Lane_Detector() {
}


Lane_Detector::~Lane_Detector() {
}



//get region have only lanes
Mat Filter_Region(Mat binImg) {
	Mat dst = Mat::zeros(Size(binImg.cols, binImg.rows), CV_8UC1);
	Point poly[1][4];
	poly[0][0] = LEFT_DOWN;
	poly[0][1] = LEFT_UP;
	poly[0][2] = RIGHT_UP;
	poly[0][3] = RIGHT_DOWN;

	const Point* polygons[1] = { poly[0] };
	int num_points[] = { 4 };


	fillPoly(dst, polygons, num_points, 1, Scalar(255, 255, 255));
	bitwise_and(binImg, dst, dst);
	
	return dst;
}

void Draw_Line(Mat& binImg,Vec4i _line) {
	int x1 = _line[0];
	int y1 = _line[1];
	int x2 = _line[2];
	int y2 = _line[3];

	line(binImg, Point(x1, y1), Point(x2, y2), Scalar(255, 255, 255), 3);
	return;
}
void Draw_Lines_in_Lane(Mat &binImg) {
	vector<Vec4i> lines;
	//HoughlineP
	HoughLinesP(binImg, lines, RHO, CV_PI / 180, THREH, MIN_LENTH, MAX_GAP);
	cout << "Size of lines = " << lines.size() << endl;
	for (int i = 0; i < lines.size(); i++) {
		Draw_Line(binImg, lines[i]);
	}
	return;
}
// Return angle between veritcal line containing car and destination point in degree
double getTheta(Point car, Point dst) {

	if (dst.x == car.x) return 0;

	if (dst.y == car.y) return (dst.x < car.x ? -90 : 90);

	double pi = acos(-1.0);

	double dx = dst.x - car.x;

	double dy = car.y - dst.y; // image coordinates system: car.y > dst.y

	if (dx < 0) return -atan(-dx / dy) * 180 / pi;

	return atan(dx / dy) * 180 / pi;

}

double Process_Haft_Frame(Mat& frame,bool lane_left) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(frame, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	
	if (contours.size() == 0)
		return 0;

	//Draw line
	imshow("Before Draw Line", frame);
	Draw_Lines_in_Lane(frame);

	
	int ymax = 0;
	int xmax = 0;
	int ymin = frame.rows -1;
	int xmin = 0;
	bool check_max = false;
	bool check_min = false;

	if (lane_left) {
		while (true) {//Get point max in left
			for (int i = frame.cols - 1; i >= 0; i--) {
				if (frame.at<uchar>(ymax, i) != 0) {
					xmax = i;
					break;
				}
			}
			ymax++;
			if (ymax >= VIDEO_HEIGHT_FRAME / 2)
				break;
		}

		while (true) {//Get point min in left
			for (int i = 0; i < frame.cols; i++) {
				if (frame.at<uchar>(ymin, i) != 0) {
					xmin = i;
					break;
				}
					
			}
			ymin--;
			if (ymin < VIDEO_HEIGHT_FRAME / 2 || ymin == ymax)
				break;
		}
	}
	else {
		while (true) {//get point max in right
			for (int i = 0; i < frame.cols; i++) {
				if (frame.at<uchar>(ymax, i) != 0) {
					xmax = i;
					break;
				}
			}
			ymax++;
			if (ymax >= VIDEO_HEIGHT_FRAME / 2)
				break;
		}
		while (true) {//get point min in right
			for (int i = frame.cols - 1; i >= 0; i--) {
				if (frame.at<uchar>(ymin, i) != 0) {
					xmin = i;
					break;
				}
			}
			ymin--;
			if (ymin < VIDEO_HEIGHT_FRAME/2 || ymin == ymax)
				break;
		}
	}
	cout << xmax << "-" << ymax << "-" << xmin << "-" << ymin << endl;
	circle(frame, Point(xmax, ymax), 3, Scalar(255, 255, 255));
	circle(frame, Point(xmin, ymin), 5, Scalar(255, 255, 255));
	//return getTheta(Point(0, 0), Point(0, 100));
	imshow("After Draw Line", frame);
	
	return getTheta(Point(xmax, ymax), Point(xmin, ymin));

}

void Lane_Detector::Process_Lane_binImg(Mat& binImg) {
	//Draw line
	//Draw_Lines_in_Lane(binImg);
	
	//Left frame (0-->Fram*2/5,Frame/2--> Frame)
	Mat LeftFrame = binImg(Rect(0, VIDEO_HEIGHT_FRAME / 2, 2 * VIDEO_WIDTH_FRAME / 5, VIDEO_HEIGHT_FRAME / 2));
	//right frane (3/5frame---> frame,frame/2--->frame)
	Mat RightFrame = binImg(Rect(3 * VIDEO_WIDTH_FRAME / 5, VIDEO_HEIGHT_FRAME / 2, 2 * VIDEO_WIDTH_FRAME / 5, VIDEO_HEIGHT_FRAME / 2));
	double thetaLeft = 0, thetaRight = 0;
	// Get theta from two haft
	thetaLeft = Process_Haft_Frame(LeftFrame, true);
	cout << "Theta Left = " << thetaLeft << endl;
	thetaRight = Process_Haft_Frame(RightFrame, false);
	cout<< "Theta Right = "<<thetaRight<<endl;
	if (thetaLeft == 0 || thetaRight == 0) {
		this->theta = thetaLeft + thetaRight;
		return;
	}

	this->theta = (thetaLeft + thetaRight) / 2;
	return;
}


void Lane_Detector::Detect_Not_Lane(Mat& grayImage) {
	Mat proImg;
	//process candy edge detection
	//-----------reduce noisy
	blur(grayImage, proImg, Size(3, 3));
	//------------edge detection
	Canny(proImg, proImg, TH_LOWER_EDGE, TH_LOWER_EDGE*RATIO, KERNEL_SIZE);
	
	//-----------get area lane
	proImg = Filter_Region(proImg);
	//imshow("Canny", proImg);
	//get theta
	this->Process_Lane_binImg(proImg);
	return;
}
void Lane_Detector::Detect_White_Lane(Mat& colorImage) {
	//Nothing
	return;
}

double Lane_Detector::getTheta() {
	return this->theta;
}
