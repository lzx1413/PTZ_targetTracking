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
void ImageControl(Mat& frame, bool &flag, Rect face);
void ImageControllerInit(QString main_path);

#endif // IMAGECONTROLLER_H
