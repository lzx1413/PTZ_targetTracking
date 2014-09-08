#ifndef TARGETRACKING_H
#define TARGETRACKING_H
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/legacy/legacy.hpp>
#include"PTZComm.h"
using namespace cv;
using namespace std;

class targetTracking:public QObject
{
    Q_OBJECT
public:
    targetTracking();
    ~targetTracking();
    int tracking();
    void test();
    PTZComm* ptzComm;
    Point oldPoint;
    Point newPoint;
private:
    void ptzControl(Point oldPt,Point newPt);
    bool backprojMode ;
    bool showHist;
    int vmin,vmax,smin;
    Point predict_pt;
    void drawCross( Point center, Scalar color,int d );
    int  iAbsolute(int a, int b);



};


#endif // TARGETRACKING_H
