#ifndef IMAGE_CONTROLLER_CLASS_H
#define IMAGE_CONTROLLER_CLASS_H
#include<QDir>
#include<QString>
#include<QDateTime>
#include "opencv2/core/core.hpp"
#define DST_IMG_WIDTH 80;
#define DST_IMG_HEIGH 80;
using namespace cv;
class ImageController
{
public:
    ImageController(QString main_path);
    ~ImageController();
    void CreateMainDir();
    void CreateSubdir();
    void BackToMainDir();
    void ImageControl(Mat& frame, bool &flag, Rect face);


private:
    QDir* file_;
    QString current_dir_;
    QString subdir_name_;
    QString current_path_;
    int num_of_image_;
    int num_of_dir_;
    QDateTime date;
    Mat face;
}


#endif // IMAGE_CONTROLER_CLASS_H
