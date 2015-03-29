#include"ImageController.h"
#include<opencv2/opencv.hpp>
const int DST_IMG_WIDTH =  92;
const int DST_IMG_HEIGH= 112;
static QDir* file_ ;
static QString current_dir_;
static QString subdir_name_;
static QString current_path_;
static int num_of_image_ = 0;
static int num_of_dir_ = 0;
static Mat face;
static QString main_path_;
void MakeDirName(QString name)
{

}
void ImageControllerInit(QString main_path)
{
    main_path_ = main_path;
    file_ = new QDir(main_path);
       if(!file_->exists())
           qWarning("can not find the main saving file");
       if(!file_->makeAbsolute())
           qWarning("can not be maken absolute");
       CreateMainDir();
       CreateSubdir();
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
    std::string img_name = current_path_.toStdString()+"/ "+a+".bmp";
    cvtColor(face,face, CV_RGB2GRAY);
    imwrite(img_name,face);
    img_name.clear();


 }
 void SaveImageForTrain ( Mat& frame,Rect rec,int num_of_temp)
 {
    char b[1];
    itoa(num_of_temp,b,10);
    char a[1] ;
    itoa(num_of_image_,a,10);
    num_of_image_++;
    std::string img_name = main_path_.toStdString()+"/"+a+"/"+a+".bmp";
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
