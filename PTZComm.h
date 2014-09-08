#pragma once
#include<QtSerialPort/QSerialPort>
#include<QString>
#include"MyThread.h"
#include<QByteArray>
#include <opencv2/opencv.hpp>
using namespace cv;
//具体还得参考协议做出修改
class PTZComm:public QObject
{
	Q_OBJECT
public:
	MyThread* comm;
	PTZComm();
	~PTZComm();
    void PTZcontrol(Point oldPoint,Point newPoint);
	void CommInit(void);
	void PTZ_Init(void);
	void Home(void);
	void Left(void);
	void Right(void);
	void Up(void);
	void Down(void);
    void Stop(void);
	void ZoomIn(void);
	void ZoomOut(void);
	void ZoomStop(void);
    void ZoomSet(int zoomNumber);
	void FocusSet(double FocusNumber);
    void PanSpeedSet(int PanSpeed);
    void TiltSpeedSet(int TiltSpeed);
	void FocusFar(void);
	void FocusNear(void);
	void FocusSetMF(void);
	void FocusSetAF(void);
	void PosSet(double panangle, double tiltangle);
	double GetPTZPanAngle(void);
	double GetPTZTiltAngle(void);
	int GetPTZZoomPos(void);
	int GetPTZFocusPos(void);
	void GetPTZFocusRange(int *nMinValue, int *nMaxValue);
	bool ReturnPTZ(const double Panangle, const double Tiltangle);
	//bool ReturnPTZ(const CvPoint ClickedPoint);

	
	void displayRxData();
   // QByteArray commData;
private:
    int TimeStop;
	
};

