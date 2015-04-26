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
#include<qmap.h>
#include<opencv2/core/core.hpp>
#include"FaceRecognition.h"
#include <opencv2/nonfree/features2d.hpp>
#include"watershed_segment_class.h"
#include <opencv2/imgproc/imgproc.hpp>
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
    Point old_point_ = Point(320,240);  //上一个位置
    Point new_point_ = Point(320,240);//目前的位置
    void TestFunction();//测试新函数的函数
    Mat ReturnNoramlizedImage();
    void  set_flag_of_train();
    void TrainingModelOfFace();
    void  set_num_of_template(int num);
    void  AddFaceName(QString name);
    QString GetNameOfList() ;
    void set_target_rect(int x_,int y_,int width_,int height_);
signals:
    void GetFaceName();

private:
    void DrawCross( Point center, Scalar color,int d );  //画粒子
    bool face_config(Mat &frame, Rect rect);
    void PTZReposition();
    void GetPredictPoint();
    int  iAbsolute(int a, int b);  //作差求绝对值
    bool target_miss_config();//确定是否丢失目标
    void UpdateStablePoint();
    int num_of_template  = 2;
    bool backproj_mode_  = false;
    bool show_hist_ = true;  //是否显示直方图
    bool flag_of_new_target_ = true;
    Point statePt_ =Point(0,0) ;
    RotatedRect trackBox = RotatedRect(Point2f(100,100), Size2f(100,50), 30);
    int vmin_ = 10;
    int vmax_ = 256;
    int smin_ = 30;
    bool flag_of_train = false;
    Point predict_pt_ = Point(0,0);  //预测的位置
    bool  exit_flag_ = false;  //退出循环的标志
    int  old_target_area_ = 0;//获得的目标面积
    int  new_target_area_ = 0;
    int origin_area_ = 0;
    Point stable_point_ = Point(320,240);
    Mat face;
    QMap<int,QString> face_name_list_;
    LabelOfFace face_labe_;
    Rect target_rect_;
    Mat binary;
    Mat rawframe;
    Rect target;
    Vector<Point> contour_of_target;
    vector<Vector<Point>> contour_of_image;
    void ImageWatersheds(Rect rec);
    Mat segment;
    WatershedSegment segmenter;
    int minHessian = 4000;
      double max_dist=0;
    double min_dist=100;
    void CalculateKeyPoint(Mat &img,bool flag);
    Mat descriptors_object,descriptors_scene;
    void GetTargetWithPoints(Mat &img);

};

inline int get_point_distace(Point A,Point B)
{
    return sqrt((A.x-B.x)^2+(A.y-B.y)^2);
}
inline Mat opening(const Mat src)//开运算使轮廓平滑完整
    {
        Mat dst;
        int morph_elem = 2;
        int morph_size = 2;
        Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
        morphologyEx( src, dst, MORPH_OPEN , element );
        return dst;
    };

#endif // TARGETRACKING_H
