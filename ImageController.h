#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H
#include<QDir>
#include<QString>
#include<QDateTime>
#include "opencv2/core/core.hpp"
#include<QDebug>
using namespace cv;

void CreateMainDir();
void CreateSubdir();
void BackToMainDir();
Mat ImageControl(Mat& frame, bool &flag, Rect face);
void ImageControllerInit(QString main_path);
void SaveImageForTrain(Mat&frame,Rect rec,int num_of_temp);
void set_number_of_dir(int num);
std::string GetCurrentPath();

#endif // IMAGECONTROLLER_H
