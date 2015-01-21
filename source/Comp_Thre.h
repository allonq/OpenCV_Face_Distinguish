/*
	this function is to compute the optimal threshold 

	Author: Yujing Qian
*/

#ifndef COMP_THRE_H
#define COMP_THRE_H

#include <iostream>
#include <highgui.h>


using namespace std;
using namespace cv;

float Comp_Thre(Mat Omega){
	float thre= 0;
	float mid = 0;
	Mat Rowi; 
	Mat Rowj; 
	Mat Rowi_j;  

	for (int i = 0; i < Omega.cols; i ++){

		Rowi = Omega(Rect(i, 0, 1, Omega.rows)); //i th row
		for (int j = 0; j < Omega.cols; j++){

			Rowj = Omega(Rect(j, 0, 1, Omega.rows)); // j the row
			Rowi_j = Rowj - Rowi; // irow -jrow
			mid = norm(Rowi_j, NORM_L2)/2; 
			if(mid > thre)thre = mid; // find maximum
		}
	}	
	return thre;
}


#endif