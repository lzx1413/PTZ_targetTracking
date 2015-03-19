#ifndef TARGETRACKING_H
#define TARGETRACKING_H
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/legacy/legacy.hpp>
#include"PTZ_command_class.h"
#include<QDebug>
using namespace cv;
using namespace std;

class TargetTracking:public QObject
{
    Q_OBJECT
public:
    TargetTracking();
    ~TargetTracking();
    int tracking();  //追踪主函数
    void test();  //测试ptz控制算法函数
    void set_exit_flag();
    PTZCommand *ptz_command_;
    Point old_point_;  //上一个位置
    Point new_point_;//目前的位置


private:
    void ptzControl(Point oldPt,Point newPt);  //控制算法测试
    void DrawCross( Point center, Scalar color,int d );  //画粒子
    bool face_config( IplImage * frame,CvRect target);
    void PTZReposition();
    int  iAbsolute(int a, int b);  //作差求绝对值
    int target_miss_config();//确定是否丢失目标
    bool backproj_mode_ ;
    bool show_hist_;  //是否显示直方图
    int vmin_;
    int vmax_;
    int smin_;
    Point predict_pt_;  //预测的位置
    bool  exit_flag_;  //退出循环的标志
    int  old_target_area_;//获得的目标面积
    int  new_target_area_;

};

inline int get_point_distace(Point A,Point B)
{
    return sqrt((A.x-B.x)^2+(A.y-B.y)^2);
}

#endif // TARGETRACKING_H
