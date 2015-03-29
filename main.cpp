#include "mainwindow.h"
#include <QApplication>
#include <opencv2/opencv.hpp>
#include"targetTracking.h"
//#include "image_controller_class.h"
using namespace cv;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.target_-> ptz_command_->CommInit();
    w.target_-> ptz_command_->PTZ_Init();
    w.target_->ptz_command_->Home();
    waitKey();
    return a.exec();

    return 0;
}
