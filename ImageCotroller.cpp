#include"ImageController.h"
#include<opencv2/opencv.hpp>
#define DST_IMG_WIDTH 80;
#define DST_IMG_HEIGH 80;
static QDir* file_ ;
static QString current_dir_;
static QString subdir_name_;
static QString current_path_;
static int num_of_image_ = 0;
static int num_of_dir_ = 0;
static Mat face;
void MakeDirName(QString name)
{

}
void ImageControllerInit(QString main_path)
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

void CreateMainDir()
{
    QDateTime date= QDateTime::currentDateTime();
   QString current_dir= date.toString("hh:mm:ss");
   current_dir.replace(":","_");
   // file_->mkdir(current_dir_);
    if(!  file_->mkdir( current_dir))
        qDebug()<<"can not make new dir";
    file_->cd(current_dir);
    current_path_.clear();
    current_path_ = file_->path();
    qDebug()<<file_->path();

}

 void CreateSubdir()
 {
    QString current_dir = QString::number(num_of_dir_);
     file_->mkdir(current_dir);
   if(!  file_->cd(current_dir))
       qDebug()<<"can not make new dir";
     num_of_dir_++;
     current_path_.clear();
     current_path_ = file_->path();
     qDebug()<<file_->path();

 }

 void BackToMainDir()
 {
     file_->cdUp();
     current_path_.clear();
     current_path_ = file_->path();
 }

 void ImageControl( Mat& frame,bool &flag,Rect rec )
 {
    if(flag)
    {
        BackToMainDir();
        CreateSubdir();
        flag = !flag;
        num_of_image_ =0;
    }
    resize(frame(rec),face,face.size(),0,0,INTER_LINEAR);
    char a[1] ;
    itoa(num_of_image_,a,10);
    num_of_image_++;
    std::string img_name = current_path_.toStdString()+"/"+a+".bmp";
    imwrite(img_name,face);
    img_name.clear();


 }
