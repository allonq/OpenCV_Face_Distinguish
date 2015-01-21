/*
	minus mean from each face 

	Author:Yujing Qian
*/

#ifndef MEAN_FACE_H
#define MEAN_FACE_H

#include <iostream>
#include <highgui.h>

using namespace std;
using namespace cv;

Mat  Mean_Face(Mat X_img, Mat X_img_mean)
{
	Mat Mu_Mat( X_img.rows, X_img.cols, CV_32F, Scalar(0.0));
	Mat img_Roi;
	for (int i=0; i< X_img.rows; i++)
	{
		img_Roi = X_img(Rect(0, i, X_img.cols, 1)); //
		Mu_Mat(Rect(0, i,  X_img.cols, 1)) = img_Roi - X_img_mean;// Ã¿Ò»ÐÐ¼õÈ¥ÐÐÆ½¾ùÖµ
	}
	return Mu_Mat;
}

#endif