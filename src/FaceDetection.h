#ifndef FACEDETECTION_H
#define FACEDETECTION_H
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "cv.h"
#include <stdio.h>
#include <assert.h>
using namespace cv;
using namespace std;
CvSeq *FaceDetect(IplImage *img);
Rect GetFaceRoi(Mat &src, Rect rect1);
void CascadeInit();
#endif // FACEDETECTION_H
