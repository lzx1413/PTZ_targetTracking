#ifndef TARGETRACKING_H
#define TARGETRACKING_H
#include<QDebug>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/legacy/legacy.hpp>
#include"PTZ_command_class.h"
using namespace cv;
using namespace std;

class TargetTracking:public QObject
{
    Q_OBJECT
public:
    TargetTracking();
    ~TargetTracking();
    int tracking();  //追踪主函数
    void FaceRecognizeTrain();
    void test();  //测试ptz控制算法函数
    void set_exit_flag();
    PTZCommand *ptz_command_;
    Point old_point_ = Point(320,240);  //上一个位置
    Point new_point_ = Point(320,240);//目前的位置
    void set_num_of_template(int num);


private:

    void DrawCross( Point center, Scalar color,int d );  //画粒子
    bool face_config(IplImage * frame);
    void PTZReposition();
    void GetPredictPoint();
    int  iAbsolute(int a, int b);  //作差求绝对值
    int target_miss_config();//确定是否丢失目标
    void UpdateStablePoint();

    bool backproj_mode_  = false;
    bool show_hist_ = true;  //是否显示直方图
    bool flag_of_new_target_ = false;
    Point statePt_ =Point(0,0) ;
    RotatedRect trackBox = RotatedRect(Point2f(100,100), Size2f(100,50), 30);
    int vmin_ = 10;
    int vmax_ = 256;
    int smin_ = 30;
    Point predict_pt_ = Point(0,0);  //预测的位置
    bool  exit_flag_ = false;  //退出循环的标志
    int  old_target_area_ = 0;//获得的目标面积
    int  new_target_area_ = 0;
    int origin_area_ = 0;
    Point stable_point_ = Point(320,240);
  //  ImageController* image_controller_;

};

inline int get_point_distace(Point A,Point B)
{
    return sqrt((A.x-B.x)^2+(A.y-B.y)^2);
}

#endif // TARGETRACKING_H
