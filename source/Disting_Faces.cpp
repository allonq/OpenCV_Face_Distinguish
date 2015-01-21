/**
 Main part of the pca, use to distinguish different faces

 Author: Yujing Qian
*/

#include "Disting_Faces.h"
int Disting_Faces(Mat X_img_mean, Mat Eign_Vec, Mat omega_mat, float omega_thre, int row, int col, int i, int j,string path, string Targetpath)
{
	char pathNames[100]; 
	char windowsName[100]; 


	Mat img_rgb(row, col, CV_8U, Scalar(0,0,0)); 
	Mat img_rgb_dis(row, col, CV_8U, Scalar(0,0,0)); 

	Mat img_gray(row, col, CV_8U, Scalar(0)); 
	Mat img_grayt(row, col, CV_8U, Scalar(0)); 
	Mat img_gray_f(row, col, CV_32F, Scalar(0.0));
	//--------------
	Mat omega_Roi;
	Mat Omega_mat; 
	Mat Omega_mat_mid; 

	float sigma_x; 
	int ix = 1;
	int iy = 1;
	int Num_Correct = 0; 
	int face_idx = 0;//which face is being tested    


	sprintf_s(pathNames, Targetpath+"%d_%d.bmp", i, j);

	img_rgb = imread(pathNames); //
	if(!img_rgb.data){
		cout << "no such file" << endl;
		exit(0);
	}

	cvtColor(img_rgb, img_gray, CV_BGR2GRAY); // rgb2gray
	img_grayt = img_gray.t().convertTo(img_gray_f, CV_32F, 1.0, 0.0); // uchar to float
	
	normalize(img_gray_f, img_gray_f, 1.0, 0.0, NORM_INF); 
	img_gray_f = img_gray_f.reshape(1,1); // reshape gray scale img
	Omega_mat = Eign_Vec.t() * (img_gray_f - img_Mean).t(); 

	for (int k = 0; k < Eign_Vec.cols; k++){
		omega_Roi = omega_mat(Rect(k, 0, 1, omega_mat.rows));
		Omega_mat_mid = Omega_mat - omega_Roi;
		sigma_x = norm(Omega_mat_mid, NORM_L2); // dis in euclidian space
		if (sigma_x < omega_thre){
			omega_thre = sigma_x;
			face_idx = k + 1;
		}
	}

	if (face_idx != 0){
		ix = int((face_idx - 0.5) / 8); // find the corresponding face in target image(s)
		iy = face_idx - ix * 8;
		sprintf_s(pathNames, path+"%d_%d.bmp", ix + 1, iy);

		img_rgb_dis = imread(pathNames);

		if(i == (ix+1)){
			//cout <<i <<"->"<<ix+1<<"right"<<endl;
			Num_Correct = 1;
		}else{
			//cout <<i <<"->"<<ix+1<<"wrong"<<endl;
			Num_Correct = 0;
		}//for debug use, show which one is not correct

	}
	return Num_Correct;
}
