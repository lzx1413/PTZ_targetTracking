#include"image_controller_class.h"
#include "opencv2/imgproc/imgproc.hpp"
#include<cv.h>
#include <iostream>
#include <stdio.h>

ImageController::ImageController(QString main_path):num_of_dir_(0),num_of_image_(0)
{
    file_ = new QDir(main_path);
    if(!file_->exists())
        qWarning("can not find the main saving file");
    if(!file_->makeAbsolute())
        qWarning("can not be maken absolute");
    CreateMainDir();
    CreateSubdir();
    face = Mat::zeros(80,80,CV_8UC3);


}

void ImageController::CreateMainDir()
{
    date = QDateTime::currentDateTime();
    current_dir_ = date.toString("yyyy:MM:dd:hh:mm:ss");
    file_->mkdir(current_dir_);
    file_->cd(current_dir_);
    current_path_ = file_->path();

}

 void ImageController::CreateSubdir()
 {
     current_dir_ = QString::number(num_of_dir_);
     file_->mkdir(current_dir_);
     file_->cd(current_dir_);
     num_of_dir_++;
     current_path_ = file_->path();

 }

 void ImageController::BackToMainDir()
 {
     file_->cdUp();
     current_path_ = file_->path();
 }

 void ImageController::ImageControl( Mat& frame,bool &flag,Rect rec )
 {
    if(flag)
    {
        BackToMainDir();
        CreateSubdir();
        flag = !flag;
        num_of_image_ =0;
    }
    resize(frame(rec),face,face.size(),0,0,INTER_LINEAR);
    char* a = NULL;
     itoa(num_of_image_,a);
    std::string img_name = current_path_.toStdString()+a+".bmp";
    imwrite(img_name,face);
    img_name.clear();


 }


