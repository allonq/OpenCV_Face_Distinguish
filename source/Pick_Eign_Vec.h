/*
	pick eignvectors according to the indx of eignvalue

*/

#ifndef PICK_EIGN_VEC_H
#define PICK_EIGN_VEC_H

#include <iostream>
#include <highgui.h>
#include <Windows.h>

using namespace std;
using namespace cv;
Mat Pick_Eign_Vec(Mat A_matrix, Mat VT_mat, Mat eignValues, int nums){

	Mat Eign_Vec(A_matrix.cols, nums, CV_32F, Scalar(0.0));
	Mat Eign_Vec_Roi;
	Mat vec_Roi;

	for (int i = 0; i < nums; i++){
		Eign_Vec_Roi = Eign_Vec(Rect(i, 0, 1, A_matrix.cols));
		vec_Roi =VT_mat.t()(Rect(i, 0, 1, VT_mat.cols)); // 
		Eign_Vec_Roi = (1/sqrt(eignValues.at<float>(i,0))) * A_matrix.t() * vec_Roi;
	}
	return Eign_Vec;
}

#endif