/*
	function work:
	read several img_ and convert them into gray scale

	Author: Yujing

*/

#ifndef READ_IMG_H
#define READ_IMG_H

#include <iostream>
#include <highgui.h>
#include <cstring>
#include <Windows.h>
#include <imgproc\imgproc.hpp>


using namespace std;
using namespace cv;

Mat Read_Img(int N, int M, int row, int col,string path)
{
	char pathNames[100]; // store path
	Mat img_rgb(row, col, CV_8U, Scalar(0, 0, 0)); 
	Mat img_gray(row, col, CV_8U, Scalar(0)); 
	Mat img_grayt(row, col, CV_8U, Scalar(0)); 
	Mat img_gray_f(row, col, CV_32F, Scalar(0.0)); // 
	Mat out_Img(N*M, row*col, CV_32F, Scalar(0.0)); //
	Mat img_Roi; //

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= M; j++){

			sprintf_s(pathNames, path+"%d_%d.bmp", i, j);
			img_rgb = imread(pathNames); 
			if(!img_rgb.data)exit(0);

			cvtColor(img_rgb, img_gray, CV_BGR2GRAY); //rgb2gray
			img_grayt = img_gray.t(); 
			img_grayt.convertTo(img_gray_f, CV_32F, 1.0, 0.0); //uchar to float
			normalize(img_gray_f, img_gray_f, 1.0, 0.0, NORM_INF); 


			img_Roi = out_Img(Rect(0, (i-1)*M+j-1, row*col, 1)); 
			img_gray_f.reshape(1, 1).copyTo(img_Roi); 
		}
	}
	return out_Img;
}


#endif