#ifndef DISTING_FACES_H
#define DISTING_FACES_H

#include <iostream>
#include <highgui.h>
#include <imgproc\imgproc.hpp>
#include <cstring>
#include "dispmanyimgs.h"

using namespace std;
using namespace cv;

int Disting_Faces(Mat _X_img_meanint, Mat _eignVectorn, Mat _omiga_mat, float threshold_omiga, int rows, int cols, int i, int j,string path, string Targetpath);

#endif