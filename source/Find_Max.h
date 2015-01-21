/*
	this function finds the largest num in vec matrix 

	Author:Yujing Qian
*/

#ifndef FIND_MAX_H
#define FIND_MAX_H

#include <iostream>
#include <highgui.h>
#include <Windows.h>

using namespace std;
using namespace cv;


int Find_Max(Mat Eign_val, float Thre){
	if(Eign_val.depth() != 5){
		cout << "invalid input" << endl;
		exit(-1);
	}

	Mat sum_All; 
	Mat Eign_val_mid; 
	float sum_Eign= 0; 
	int Num_within_Thre = 0; 

	reduce(Eign_val, sum_All, 0, CV_REDUCE_SUM); 
	for (int i=0; i<Eign_val.rows; i++){
		Num_within_Thre+= 1;
		sum_Eign += Eign_val.at<float>(i);
		if(sum_Eign >= sum_All.at<float>(0) * Thre){
			i = Eign_val.rows;
		}
	}
	//cout << sum_All << endl;
	//cout << sum_Eignn << endl;
	return Num_within_Thre;
}

#endif