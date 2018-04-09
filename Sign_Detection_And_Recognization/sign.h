#ifndef __SIGN_H__
#define __SIGN_H__

#include "header.h"

class Sign
{
private:
	HOGDescriptor _hog;
	Ptr<SVM> _svm;
	Rect _sign_ROI;
	int _class_id;

public:
	Sign();
	bool detect(const Mat &mask);
	void recognize(const Mat &gray);
	void classify(const Mat &gray_sign);
	int getClassID();
};

#endif