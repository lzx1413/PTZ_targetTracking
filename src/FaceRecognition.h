#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"
#include <cv.h>
#include <vector>
#include <utility>
#include "StatDir.h"
using namespace cv;
using namespace std;
//用于表示人脸识别结果
struct LabelOfFace
{
    int label;
    float confidence;
};
void TrainingModle(int FaceNum);
LabelOfFace FaceRecognition(Mat &face,Rect rec);
void FaceRecognitionInit();

#endif // FACERECOGNITION_H
