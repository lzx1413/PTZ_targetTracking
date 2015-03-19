#ifndef FACEDETECTION_H
#define FACEDETECTION_H
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "cv.h"
#include <stdio.h>
#include <assert.h> //用于防御式编程
using namespace cv;
using namespace std;
CvSeq * FaceDetect( IplImage *image);
CvRect GetFaceRoi(  IplImage *img);
void CascadeInit();
#endif // FACEDETECTION_H
