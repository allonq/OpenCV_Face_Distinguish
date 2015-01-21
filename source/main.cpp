/*
	This is a project demo finished by using OpenCV 
	The quality of the recognition is related to the training and testing human picture
	The path indicates the path in which training pictures are stored in the format of "i_j.jpg"
	The targetPath indicates the path in which testing pictures are stored in the format of "i_j.jpg"
	
	i represent the ith person

	j represent the jth img of the ith person
	
	Author: Yujing Qian
	UCLA CS 276
	Nov.2014
*/

#include <iostream>
#include <highgui.h>
#include <algorithm>
#include "Read_Img.h"

#include "Pick_Eign_Vec.h"
#include "Comp_Thre.h"
#include "Disting_Faces.h"
#include "Cov.h"
#include "Mean_Face.h"
#include "Find_Max.h"
	
using namespace std;
using namespace cv;

int main()
{
	int N = 50; //number of people
	int M = 5; //num of image per person
	int row = 256; // picture size
	int col = 256; 
	string path="c:/..... ";//place to put custom training images
	string targetPath="";// place to put testing image;

	int nCorrect = 0; 
	int nError = 0;
	//------matrix initial 
	Mat X_img(N*M, row*col, CV_32F, Scalar(0.0));
	Mat X_img_mean(1, row*col, CV_32F, Scalar(0.0));


	Mat A_Matrix; 
	Mat C_Matrix; 
	Mat S; 
	Mat U; 
	Mat VT; //SVD
	//------
	int Max_Eign = 0; 
	float Eign_Thre = 0.99; //represent the proximation percentage 
	Mat Eign_Vec; 
	Mat Omega_Matrix; 

	float Omega_Thre = 0.0f;//threshold
	int nSimilar = 0; // how many faces are similar

	//double running_time;
	//running_time = static_cast<double>(getTickCount());

	X_img = Read_Img(N, M, row, col,path); //
	reduce(X_img, X_img_mean, 0, CV_REDUCE_AVG); // vectorize it

	//------finish reading data
	A_Matrix = Mean_Face(X_img, X_img_mean); // mean of all
	C_Matrix = Cov(A_Matrix, M, N); 
	SVDecomp(C_Matrix, S, U, VT, SVD::FULL_UV);  //SVD
	Max_Eign = Find_Max(S, Eign_Thre); 
	//cout << "Max_Eign=" << Max_Eign << endl; //debug message
	Eign_Vec = Pick_Eign_Vec(A_Matrix, VT, S, Max_Eign); 

	Omega_Matrix = Eign_Vec.t() * A_Matrix.t(); //
	Omega_Thre = Comp_Thre(Omega_Matrix); 
	// cout << "Omega_Thre=" << Omega_Thre << endl;

	for (int i = 9; i <= 10; i++){
		for (int j = 1; j <= 40; j++){

			nSimilar=Disting_Faces(X_img_mean, Eign_Vec, Omega_Matrix, Omega_Thre, row, col, j, i, path); 
			if (nSimilar==1) nCorrect++;
			else if (nSimilar==2)nError++;
		}
	}
	/*cout << "correctRate" << nCorrect / 80.0 << endl;
	cout << "error_rate" << nError / 80.0 << endl;

	running_time = static_cast<double>(getTickCount())-running_time;
	running_time = running_time / getTickFrequency();
	cout << "compute time" << running_time << "s" <<endl;
	*/
	getchar();
	return 0;
}