#include"ImageController.h"
#include<opencv2/opencv.hpp>
const int DST_IMG_WIDTH =  112;
const int DST_IMG_HEIGH= 92;
static QDir* file_ ;
static QString current_dir_;
static QString subdir_name_;
static QString current_path_;
static int num_of_image_ = 0;
static int num_of_dir_ = 0;
static Mat face;
static QString path_of_template;
static QString path_of_image;
void ImageControllerInit(QString main_path)
{
    path_of_template = "D:/E/work/QT/TargetTracking_PTZ/FaceLib";
    file_ = new QDir(main_path);
       if(!file_->exists())
           qWarning("can not find the main saving file");
       if(!file_->makeAbsolute())
           qWarning("can not be maken absolute");
       CreateMainDir();
       CreateSubdir();
       path_of_image = file_->path();
       face = Mat::zeros(DST_IMG_WIDTH,DST_IMG_HEIGH,CV_8UC3);
}

void CreateMainDir()
{
    QDateTime date= QDateTime::currentDateTime();
   QString current_dir= date.toString("hh:mm:ss");
   current_dir.replace(":","_");
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
     current_path_.clear();
     current_path_ = file_->path();
     qDebug()<<file_->path();

 }

Mat ImageControl( Mat& frame,bool &flag,Rect rec )
 {
    if(flag)
    {
        file_->cd(path_of_image);
        current_path_=file_->path();
        num_of_image_ =0;
    }
    resize(frame(rec),face,face.size(),0,0,INTER_LINEAR);
    char a[1] ;
    _itoa(num_of_image_,a,10);
    num_of_image_++;
    std::string img_name = current_path_.toStdString()+"/ "+a+".bmp";
    //cvtColor(face,face, CV_RGB2GRAY);
    imwrite(img_name,face);
    img_name.clear();
    return face;


 }
void  SaveImageForTrain ( Mat& frame,Rect rec,int num_of_temp,bool flag_of_train)
 {
    if(flag_of_train)
    {
       file_->cd(path_of_template);
       QString current_dir = QString::number(num_of_temp);
       file_->mkdir(current_dir);
       file_->cd(current_dir);
       current_path_ = file_->path();
    }
    char a[1] ;
    _itoa(num_of_image_,a,10);
    num_of_image_++;
    std::string img_name = current_path_.toStdString()+"/"+a+".bmp";
    resize(frame(rec),face,face.size(),0,0,INTER_LINEAR);
    cvtColor(face,face, CV_RGB2GRAY);
    imwrite(img_name,face);
 }

 std::string GetCurrentPath()
 {
     return current_path_.toStdString();
 }

 void set_number_of_dir(int num)
 {
     num_of_dir_ = num;
 }
