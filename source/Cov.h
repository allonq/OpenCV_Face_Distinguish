#ifndef COV_H
#define COV_H

#include <iostream>
#include <highgui.h>
//#include <imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

Mat Cov(Mat X, int M, int N){
	return X * X.t() / (M * N);
}

#endif