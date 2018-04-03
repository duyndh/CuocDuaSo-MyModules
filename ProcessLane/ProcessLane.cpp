#include"ProcessLane.h"

Mat ProcessLane::get_mask(Mat img)
{

	GaussianBlur(img, img, Size(KERNEL_SIZE, KERNEL_SIZE), 0);
	Mat dst;
	Mat hsv;
	cvtColor(img, hsv, COLOR_BGR2HSV);
	inRange(hsv, LOW_HSV, HIG_HSV, dst);

	Mat kernel = Mat::ones(KERNEL_SIZE, KERNEL_SIZE, CV_8UC1);
	dilate(dst, dst, kernel);
	morphologyEx(dst, dst, MORPH_CLOSE, kernel);
	return dst;
}
Mat ProcessLane::ConnectLine(Mat &mask, Mat Image)
{
	vector<Point> Data;
	bool CheckUp = false;
	bool CheckDown = false;
	Point Data1, Data2;
	int X = mask.cols;
	int Y = mask.rows;
	//-------------- CheckUp -------------------------// 
	for (int j = 0; j <X - 1; j++)
	{
		if ((int)mask.at<uchar>(0, j) >(int)mask.at<uchar>(0, j + 1))
			CheckUp = true;
	}

	// ----------------CheckDown----------------------//
	for (int j = 0; j < X - 1; j++)
	{
		if ((int)mask.at<uchar>(Y - 1, j) >(int)mask.at<uchar>(Y - 1, j + 1))
			CheckDown = true;

	}
	if (CheckDown == true && CheckUp == true)
	{
		bool CheckSpace;
		bool isDone = false;
		cout << "Up and Down" << endl;
		int Count = 0;
		for (int i = 0; i < Y; i++)
		{
			int k;
			CheckSpace = true;
			for (int j = 0; j < X - 1; j++)
			{
				k = j;
				if ((int)mask.at<uchar>(i, j) < (int)mask.at<uchar>(i, j + 1))
				{
					if (Count == 0)
					{
						Data1.x = j;
						Data1.y = i;
						CheckSpace = false;
						break;
					}
					cout << Count << endl;
					if (Count > 5)
					{
						Data2.x = j;
						Data2.y = i;
						isDone = true;
						CheckSpace = false;
						break;
					}


				}

			}
			if (CheckSpace == true && k == X - 2)
				Count++;
			if (isDone)
			{
				line(Image, Point(Data1.x, Data1.y), Point(Data2.x, Data2.y), Scalar(0, 0, 255), 40, 8, 0);
				break;
			}

		}
		return Image;
	}
	if (CheckDown == false && CheckUp == true)
	{
		vector<int> x;
		bool CheckSpace;
		bool isDone = false;
		cout << "Up" << endl;
		int Count = 0;
		int k;
		for (int i = 0; i < Y; i++)
		{
			CheckSpace = true;
			for (int j = 0; j < X - 1; j++)
			{
				k = j;
				if ((int)mask.at<uchar>(i, j) < (int)mask.at<uchar>(i, j + 1))
				{
					x.push_back(j);
					Data1.x = j;
					Data1.y = i;
					CheckSpace = false;
					break;

				}

			}
			if (CheckSpace == true && k == X - 2)
			{
				int x1 = x[0];
				int x2 = x[x.size() - 1];
				cout << "x1	" << x1 << "	x2	" << x2 << endl;
				cout << "x : " << Data1.x << "	" << "y : " << Data1.y << endl;
				if (abs(x1 - x2) < 30)
				{
					cout << "if 3" << endl;
					int x = x2;
					for (int i = Data1.y; i < Y; i++)
					{
						Data.push_back(Point(x, i));
						circle(Image, Point(x, i), 5, Scalar(0, 0, 0));
					}
					return Image;
				}
				if (x1 < x2 + 80)
				{
					cout << "if 1" << endl;
					int x = x2;
					for (int i = Data1.y; i < Y; i++)
					{

						x = x + 1;
						Data.push_back(Point(x, i));
						circle(Image, Point(x, i), 5, Scalar(0, 0, 0));
					}
					return Image;

				}
				if (x1 > x2 - 80)
				{
					int x = x2;
					cout << "if 2" << endl;
					for (int i = Data1.y; i < Y; i++)
					{
						x = x - 1;
						Data.push_back(Point(x, i));
						circle(Image, Point(x, i), 5, Scalar(0, 0, 0));
					}
					return Image;
				}
				break;
			}

		}

		return Image;
	}
	if (CheckDown == true && CheckUp == false)
	{
		vector<int> x;
		bool CheckSpace;
		bool isDone = false;
		cout << "Down" << endl;
		int Count = 0;
		int k;
		for (int i = Y - 1; i >= 0; i--)
		{
			CheckSpace = true;
			for (int j = 0; j < X - 1; j++)
			{
				k = j;
				if ((int)mask.at<uchar>(i, j) < (int)mask.at<uchar>(i, j + 1))
				{
					x.push_back(j);
					Data1.x = j;
					Data1.y = i;
					CheckSpace = false;
					break;

				}

			}
			if (CheckSpace == true && k == X - 2)
			{
				int x1 = x[0];
				int x2 = x[x.size() - 1];
				cout << "x1	" << x1 << "	x2	" << x2 << endl;
				cout << "x : " << Data1.x << "	" << "y : " << Data1.y << endl;
				if (abs(x1 - x2) < 75)
				{
					cout << "if 3" << endl;
					int x = x2;
					for (int i = Data1.y; i >= 0; i--)
					{
						Data.push_back(Point(x, i));
						circle(Image, Point(x, i), 5, Scalar(0, 0, 0));
					}
					return Image;
				}
				if (x1 < x2 + 80)
				{
					cout << "if 1" << endl;
					int x = x2;
					for (int i = Data1.y; i >= 0; i--)
					{

						x = x + 1;
						Data.push_back(Point(x, i));
						circle(Image, Point(x, i), 5, Scalar(0, 0, 0));
					}
					return Image;

				}
				if (x1 > x2 - 80)
				{
					int x = x2;
					cout << "if 2" << endl;
					for (int i = Data1.y; i >= 0; i--)
					{
						x = x - 1;
						Data.push_back(Point(x, i));
						circle(Image, Point(x, i), 5, Scalar(0, 0, 0));
					}
					return Image;
				}
				break;
			}

		}

		return Image;
	}

	return Image;
}
Mat ProcessLane::Boundary(Mat &mask, Mat Image)
{
	vector<Point> Data;
	int count = 0;

	for (int i = 0; i < mask.rows; i++)
	{
		for (int j = 0; j < mask.cols - 1; j++)
		{

			if ((int)mask.at<uchar>(i, j) >(int)mask.at<uchar>(i, j + 1))
			{
				Data.push_back(Point(j, i));

				cout << Data[count].x << "  " << Data[count].y << endl;
				count++;
			}

		}
		cout << endl;
	}
	for (int i = 0; i < Data.size(); i++)
	{
		circle(Image, Point(Data[i].x, Data[i].y), 5, Scalar(0, 0, 0));
	}
	cout << "Size : " << count << endl;
	cout << mask.cols << "		" << mask.rows << endl;
	return Image;
}