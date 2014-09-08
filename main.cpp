#include "mainwindow.h"
#include <QApplication>
#include <opencv2/opencv.hpp>
#include"targetTracking.h"
using namespace cv;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.target->ptzComm->Home();
    w.target->ptzComm->comm->sleep(2);
   // w.target->test();
   //  w.startTracking();
//    targetTracking track;
//    track.ptzComm->Home();
//    track.tracking();

//    Mat img = imread("D:/tiger.jpg");
//    if (img.empty())
//    {
//        fprintf(stderr, "Error: load image failed.");
//        return -1;
//    }
//    namedWindow("image", CV_WINDOW_AUTOSIZE);
//    imshow("image", img);
//    PTZComm* com = new PTZComm;
//    com->CommInit();
//    com->PTZ_Init();
//    com->Home();
//    com->Up();
//    com->comm->sleep(1);
//    waitKey(0);
  //  return 0;
    // tracking();
    return a.exec();
}
