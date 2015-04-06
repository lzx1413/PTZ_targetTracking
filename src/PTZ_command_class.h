#pragma once
#include<QtSerialPort/QSerialPort>
#include<QString>
#include"my_serialport_class.h"
#include<QByteArray>
#include <opencv2/opencv.hpp>
using namespace cv;
//具体还得参考协议做出修改
class PTZCommand:public QObject
{
	Q_OBJECT
public:
    MySerialPort *my_serial_port;
    PTZCommand();
    ~PTZCommand();
    void PTZcontrol(Point old_point,Point new_point,int frame_num);  //控制算法
    void CommInit(void);  //串口初始化
    void CloseCom(void);//关闭串口
    void PTZ_Init(void);  //ptz初始化
    void Home(void);  //返回home(0,0)处
    void AutoTurn(int now_x,int now_y,int last_x,int last_y);
    void AutoLeft(bool is_stop = true);  //自动追踪时开始向左转
    void AutoRight(bool is_stop = true,int stop_time = 100);  //自动追踪时开始向右转
    void AutoUp(bool is_stop = true,int stop_time = 100);  //自动追踪时开始向上转
    void AutoDown(bool is_stop = true);  //自动追踪时开始向下转
    void ManuLeft();  //手动追踪时开始向左转
    void ManuRight();  //手动追踪时开始向右转
    void ManuUp();  //手动追踪时开始向上转
    void ManuDown();  //手动追踪时开始向下转
    void Stop(void);  //停止转动
    void AutoZoom(int height,int width);
    void ZoomIn(void);  //放大
    void ZoomOut(void);  //缩小
    void ZoomStop(void);  //停止放大或缩小
    void ZoomSet(int zoomNumber);  //设置放大倍数（0-128）
    void FocusSet(double FocusNumber);  //设置聚焦位置
    void PanSpeedSet(int PanSpeed);  //设置水平转动速度
    void TiltSpeedSet(int TiltSpeed);  //设置竖直转动速度
    void FocusFar(void);  //聚焦于最远点
    void FocusNear(void);  //聚焦于最近点
    void FocusSetMF(void);  //设定为手动聚焦
    void FocusSetAF(void);  //设定为自动聚焦
    void PosSet(double panangle, double tiltangle);  //设置下一步转动位置
    double GetPTZPanAngle(void);  //获得当前水平角度
    double GetPTZTiltAngle(void);  //获得当前竖直角度
    int GetPTZZoomPos(void);  //获得当前放大倍数
    int GetPTZFocusPos(void);  //获得当前聚焦位置
    void GetPTZFocusRange(int *nMinValue, int *nMaxValue);  //获得聚焦位置范围
    bool ReturnPTZ(const double Panangle, const double Tiltangle);  //根据当前位置设置下一步位置
    void DisplayRxData();
    void Point2Point(Point oldpoint);

signals:
    void SetComNum(QString comnum);
private:
    int time_stop_;  //每个指令运行的时间
    int x_state_change_;  //判断x方向是否发生反转
    int y_state_change_;  //判断y方向是否发生反转
    int last_x_state_;  //上一帧x运动方向
    int last_y_state_;   //上一次y运动方向
    int now_x_state_;  //这一次x运动方向
    int now_y_state_;  //这一次y运动方向
    int last_x_state_2;//两次前的运动方向
    int last_y_state_2;
	
};

