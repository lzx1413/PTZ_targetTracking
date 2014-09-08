#include "PTZComm.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QDateTime>
PTZComm::PTZComm()
{
	comm = new MyThread;
	this->comm->changeTxState(false);
	this->comm->TxData.clear();
	this->comm->requestData.clear();
    TimeStop = 10;
}


PTZComm::~PTZComm()
{
	delete comm;
}


void PTZComm::CommInit()
{
    comm->information.infor.clear();
    comm-> information.infor.append("Name is asfdasdf\n");
    comm-> information.infoChange();

	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		qDebug() << "Name        : " << info.portName();
		qDebug() << "Description : " << info.description();
		qDebug() << "Manufacturer: " << info.manufacturer();
        comm->information.infor.clear();
        comm-> information.infor.append("Name"+info.portName()+"\n");
        comm-> information.infoChange();

		// Example use QSerialPort
        comm->setPortnum(info.portName());

	}//查找串口
	comm->startCom();
	qDebug() << "Thread starting" << endl;
	comm->changeComState(false);
	comm->start();
    qDebug() <<tr( "com has opened" )<< endl;
    
}
	//PTZ初始化
	//1.Control by host computer
void PTZComm::PTZ_Init()
{
   // this->commData.clear();
    char  temp[7] = { 0xFF, 0x30, 0x30, 0x00, 0x90, 0x30, 0xEF};
  //  this->commData.append(temp,7 );
	this->comm->requestData.clear();
	this->comm->TxData.clear();
    this->comm->TxData.append(temp, 7);
	this->comm->changeTxState(true);
	this->comm->msleep(20);


    //2. Command terminaltion notification setting
    //writestring = "FF 30 30 00 94 31 EF";
    char commData1[7] = {0xFF, 0x30, 0x30, 0x00, 0x94, 0x31, 0xEF};
   // this->commData.clear();
  //  this->commData.append( 0xFF, 0x30, 0x30, 0x00, 0x94, 0x31, 0xEF );
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData1, 7);
    this->comm->changeTxState(true);
    this->comm->msleep(20);
    //3. Camera On
    //    writestring = "FF 30 30 00 A0 31 EF";
    char commData2[7 ] = {0xFF, 0x30, 0x30, 0x00, 0x94, 0x31, 0xEF};
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData2, 7);
    this->comm->changeTxState(true);
}
void PTZComm::Home(void)
{

    char commData[6] = { 0xFF, 0x30, 0x30, 0x00, 0x57, 0xEF };
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 6);
    this->comm->changeTxState(true);
}

void PTZComm::Left(void)
{
   // char commData[8] = { 0xFF, 0x30, 0x30, 0x00,0x60, 0x31,0x30, 0xEF };
    PanSpeedSet(200);
    this->comm->msleep(5);
    char commData[7] = { 0xFF, 0x30, 0x30, 0x00,0x53, 0x32, 0xEF };
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 7);
    this->comm->changeTxState(true);
    this->comm->msleep(200);
    Stop();
    this->comm->msleep(50);


    qDebug()<<"LEFT";
   // this->comm->stop();
    this->comm->information.infoDisplay("Left");
}

void PTZComm::Right(void)
{


    //char commData[8] = { 0xFF, 0x30, 0x30, 0x00, 0x60, 0x32, 0x30, 0xEF };
    char commData[7] = { 0xFF, 0x30, 0x30, 0x00, 0x53, 0x31, 0xEF };
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 7);
    this->comm->changeTxState(true);
    qDebug()<<"Right"<<endl;
   // this->comm->msleep(TimeStop);
   // this->comm->stop();
    this->comm->msleep(200);
    Stop();
    this->comm->msleep(50);
}

void PTZComm::Up(void)
{


   // char commData[8] = { 0xFF, 0x30, 0x30, 0x00, 0x60, 0x30, 0x31, 0xEF };
    char commData[7] = { 0xFF, 0x30, 0x30, 0x00, 0x53, 0x33, 0xEF };
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 7);
    this->comm->changeTxState(true);
    //this->comm->msleep(TimeStop);
    //this->comm->stop();
    this->comm->msleep(200);
    Stop();
    this->comm->msleep(50);
}


void PTZComm::Down(void)
{


    //char commData[8]= { 0xFF, 0x30, 0x30, 0x00, 0x60, 0x30, 0x32, 0xEF };
    char commData[7] = { 0xFF, 0x30, 0x30, 0x00, 0x53, 0x34, 0xEF };
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 7);
    this->comm->changeTxState(true);
   // this->comm->msleep(TimeStop);
   // this->comm->stop();
    this->comm->msleep(200);
    Stop();
    this->comm->msleep(50);
}

void PTZComm::Stop()
{
    char commData[8]= { 0xFF, 0x30, 0x30, 0x00, 0x60, 0x30,0x30, 0xEF };
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 8);
    this->comm->changeTxState(true);
}
void PTZComm::PosSet(double panangle, double tiltangle)
{
    char cPanAngle[5] = { 0 };
    char cTiltAngle[5] = { 0 };
    int i = 0;

    int PanAngle = (int)(panangle / 0.1125 + 32768);
    _itoa(PanAngle, cPanAngle, 16);
    for (i = 0; i<5; i++)
        if ((cPanAngle[i] >= 'a') && (cPanAngle[i] <= 'z'))
            cPanAngle[i] -= 32;

    int TiltAngle = (int)(tiltangle / 0.1125 + 32768);
    _itoa(TiltAngle, cTiltAngle, 16);
    for (i = 0; i<5; i++)
        if ((cTiltAngle[i] >= 'a') && (cTiltAngle[i] <= 'z'))
            cTiltAngle[i] -= 32;

    char commData[5] = { 0xFF, 0X30, 0X30, 0X00, 0X62 };


    memcpy(commData + 5, cPanAngle, 4);
    memcpy(commData + 9, cTiltAngle, 4);
    commData[13] = 0xEF;
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 14);
    this->comm->changeTxState(true);
}



void PTZComm::ZoomIn(void)//放大
{

    char commData[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA2, 0x34,  0xEF };
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 7);
    this->comm->changeTxState(true);
}

void PTZComm::ZoomOut(void)//缩小
{

    char commData[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA2, 0x33,0xEF };
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 7);
    this->comm->changeTxState(true);
}
void PTZComm::ZoomSet(int zoomNumber)
{
    char cZoomPos[5] = { 0 };
    int i = 0;
    char commData[6] = { 0 };

    int Zoompos = (zoomNumber);

    _itoa(Zoompos, cZoomPos, 16);
    for (i = 0; i<5; i++)
        if ((cZoomPos[i] >= 'a') && (cZoomPos[i] <= 'z')) cZoomPos[i] -= 32;

    commData[0] = 0xFF;
    commData[1] = 0x30;
    commData[2] = 0x30;
    commData[3] = 0x00;
    commData[4] = 0xA3;

    if (zoomNumber <16)
    {
        commData[5] = 0x30;
        memcpy(commData + 6, cZoomPos, 1);
    }
    else
    {
        memcpy(commData + 5, cZoomPos, 2);
    }

    commData[7] = 0xEF;
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 8);
    this->comm->changeTxState(true);
}

void PTZComm::ZoomStop(void)
{

    char commData[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA2, 0x30, 0xEF };
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 7);
    this->comm->changeTxState(true);
}

void PTZComm::FocusFar(void)//聚焦于远点
{


    char commData[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA1, 0x33, 0xEF };
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 7);
    this->comm->changeTxState(true);
}

void PTZComm::FocusNear(void)//聚焦于近点
{

    char commData[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA1, 0x32, 0xEF };
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 7);
    this->comm->changeTxState(true);
}
void PTZComm::FocusSetMF(void)//调节为手动对焦模式
{
	
    char commData[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA1, 0x31, 0xEF };
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 7);
    this->comm->changeTxState(true);
}


void PTZComm::FocusSetAF(void)//调节为自动对焦模式
{
    char commData[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA1, 0x30, 0xEF };
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 7);
    this->comm->changeTxState(true);
}


void PTZComm::FocusSet(double FocusNumber)
{

    char cZoomPos[5] = { 0 };
    int i = 0;

    //Set manual focus mode
    FocusSetMF();

    char commData[6];
    int Zoompos = static_cast<int>(FocusNumber);
    _itoa(Zoompos, cZoomPos, 16);
    for (i = 0; i<5; i++)
        if ((cZoomPos[i] >= 'a') && (cZoomPos[i] <= 'z')) cZoomPos[i] -= 32;

    commData[0] = 0xFF;
    commData[1] = 0x30;
    commData[2] = 0x30;
    commData[3] = 0x00;
    commData[4] = 0xB0;
    commData[5] = 0x30;

    memcpy(commData + 6, cZoomPos, 3);

    commData[9] = 0xEF;
    this->comm->requestData.clear();
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 10);
    this->comm->changeTxState(true);

    //return to auto focus mode
    //FocusSetAF();
}
void PTZComm::PanSpeedSet(int PanSpeed)
{
    char cPanSpeed[5] = { 0 };
    int i = 0;

    //Set manual focus mode
   // FocusSetMF();

    char commData[7];
    _itoa(PanSpeed, cPanSpeed, 16);
    for (i = 0; i<5; i++)
        if ((cPanSpeed[i] >= 'a') && (cPanSpeed[i] <= 'z'))
            cPanSpeed[i] = cPanSpeed[i]- 32;

    commData[0] = 0xFF;
    commData[1] = 0x30;
    commData[2] = 0x30;
    commData[3] = 0x00;
    commData[4] = 0x50;
    if(PanSpeed<16)
    {
        commData[5] = 0x30;
        commData[6] = 0x30;
        memcpy(commData + 7, cPanSpeed, 1);

    }
    if((PanSpeed>=16)&&(PanSpeed<255))
    {
        commData[5] = 0x30;
        memcpy(commData + 6,cPanSpeed, 2);
    }
    else
    {

        memcpy(commData + 5, cPanSpeed, 3);
    }
//    memcpy(commData + 6, cZoomPos, 3);

    commData[8] = 0xEF;
    this->comm->requestData.clear();
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 9);
    this->comm->changeTxState(true);

}

void PTZComm::TiltSpeedSet(int TiltSpeed)
{
    char cTiltSpeed[5] = { 0 };
    int i = 0;

    //Set manual focus mode
   // FocusSetMF();

    char commData[7];
    _itoa(TiltSpeed, cTiltSpeed, 16);
    for (i = 0; i<5; i++)
        if ((cTiltSpeed[i] >= 'a') && (cTiltSpeed[i] <= 'z')) cTiltSpeed[i] -= 32;

    commData[0] = 0xFF;
    commData[1] = 0x30;
    commData[2] = 0x30;
    commData[3] = 0x00;
    commData[4] = 0x51;
    if(TiltSpeed<16)
    {
        commData[5] = 0x30;
        commData[6] = 0x30;
        memcpy(commData + 7,cTiltSpeed, 1);

    }
    if((TiltSpeed>=16)&&(TiltSpeed<255))
    {
        commData[5] = 0x30;
        memcpy(commData + 6, cTiltSpeed, 2);
    }
    else
    {

        memcpy(commData + 5, cTiltSpeed, 3);
    }
//    memcpy(commData + 6, cZoomPos, 3);

    commData[8] = 0xEF;
    this->comm->requestData.clear();
    this->comm->TxData.clear();
    this->comm->requestData.clear();
    this->comm->TxData.append(commData, 9);
    this->comm->changeTxState(true);

}


void PTZComm::GetPTZFocusRange(int *nMinValue, int *nMaxValue)
{
    int iResponseLength = 0;
    char cResponseDate[256] = { 0 };
    char  cangle[5] = { 0 };
    int nMinV = 0;
    int nMaxV = 0;
    char commData[7] = { 0 };

    commData[0] = 0xFF;
    commData[1] = 0x30;
    commData[2] = 0x30;
    commData[3] = 0x00;
    commData[4] = 0xB1;
    commData[5] = 0x32;
    commData[6] = 0xEF;


    this->comm->requestData.clear();
    this->comm->TxData.clear();
    this->comm->TxData.append(commData, 7);
    this->comm->changeTxState(true);
    comm->msleep(50);

    iResponseLength = comm->requestData.size();

    if (iResponseLength = 14)
    {
        memcpy(cangle, cResponseDate + 5, 4);

        int val = 0;
        for (int i = 0; i<5; i++)
        {
            if (cangle[i] >= 'a'   &&   cangle[i] <= 'f')
                val = val * 16 + cangle[i] - 'a' + 10;
            else   if (cangle[i] >= 'A'   &&   cangle[i] <= 'F')
                val = val * 16 + cangle[i] - 'A' + 10;
            else   if (cangle[i] >= '0'   &&   cangle[i] <= '9')
                val = val * 16 + cangle[i] - '0';
            else
                break;
        }

        nMinV = val;

        memcpy(cangle, cResponseDate + 9, 4);

        val = 0;
        for (int i = 0; i<5; i++)
        {
            if (cangle[i] >= 'a'   &&   cangle[i] <= 'f')
                val = val * 16 + cangle[i] - 'a' + 10;
            else   if (cangle[i] >= 'A'   &&   cangle[i] <= 'F')
                val = val * 16 + cangle[i] - 'A' + 10;
            else   if (cangle[i] >= '0'   &&   cangle[i] <= '9')
                val = val * 16 + cangle[i] - '0';
            else
                break;
        }

        nMaxV = val;
    }
    else
    {
        return;
    }

	

    *nMinValue = nMinV;
    *nMaxValue = nMaxV;
}

/**********获得当前水平旋转角度**************/
double PTZComm::GetPTZPanAngle(void)
{
    int iResponseLength = 0;
    char  cangle[5] = { 0 };
    double panangle = 0.0;
   // int istep = 0;
    char commData[6] = { 0 };
    commData[0] = 0xFF;
    commData[1] = 0x30;
    commData[2] = 0x30;
    commData[3] = 0x00;
    commData[4] = 0x63;
    commData[5] = 0xEF;
    this->comm->requestData.clear();
    this->comm->TxData.clear();
    this->comm->TxData.append(commData, 6);
    this->comm->changeTxState(true);
    comm->msleep(50);
    qDebug()<<"rxevent is"<<comm->rx_event;
    comm->rx_event = false;
    iResponseLength = comm->requestData.size();
    qDebug()<<"resize is"<<comm->requestData.size();

    if (iResponseLength == 14)
    {
//        memcpy(cangle, comm->requestData + 5, 4);
        for(int i = 0;i<4;i++)
        {
           cangle[i] = comm->requestData[i+5] ;

        }

        int val = 0;
        for (int i = 0; i<4; i++)
        {
            if (cangle[i] >= 'a'   &&   cangle[i] <= 'f')
                val = val * 16 + cangle[i] - 'a' + 10;
            else   if (cangle[i] >= 'A'   &&   cangle[i] <= 'F')
                val = val * 16 + cangle[i] - 'A' + 10;
            else   if (cangle[i] >= '0'   &&   cangle[i] <= '9')
                val = val * 16 + cangle[i] - '0';
            else
                break;
        }

        panangle = (val - 32768)*0.1125;
    }
    else
    {
        return 0;
    }


    return panangle;
}


/**********获得当前TILT的角度*************/
double PTZComm::GetPTZTiltAngle(void)
{
    int iResponseLength = 0;
    char  cangle[5] = { 0 };
    double tiltangle = 0.0;
    int istep = 0;
    char commData[6] = { 0x00 };
    commData[0] = 0xFF;
    commData[1] = 0x30;
    commData[2] = 0x30;
    commData[3] = 0x00;
    commData[4] = 0x63;
    commData[5] = 0xEF;
    this->comm->requestData.clear();
    this->comm->TxData.clear();
    this->comm->TxData.append(commData, 6);
    this->comm->changeTxState(true);
    comm->msleep(500);

    iResponseLength = comm->requestData.size();

    if (iResponseLength == 14)
    {
            for(int i = 0;i<4;i++)
            {
               cangle[i] = comm->requestData[i+9] ;

            }

        int val = 0;
        for (int i = 0; i<4; i++)
        {
            if (cangle[i] >= 'a'   &&   cangle[i] <= 'f')
                val = val * 16 + cangle[i] - 'a' + 10;
            else   if (cangle[i] >= 'A'   &&   cangle[i] <= 'F')
                val = val * 16 + cangle[i] - 'A' + 10;
            else   if (cangle[i] >= '0'   &&   cangle[i] <= '9')
                val = val * 16 + cangle[i] - '0';
            else
                break;
        }

        tiltangle = (val - 32768)*0.1125;
    }
    else
    {
        return 0;
    }

	

    return tiltangle;
}


/*************获取当前放大倍数*****************/
 int PTZComm::GetPTZZoomPos(void)
{
   int iResponseLength = 0;
   char  cangle[3] = { 0 };
   int zoompos = 0;
   char commData[6] = { 0X00 };
   commData[0] = 0xFF;
   commData[1] = 0x30;
   commData[2] = 0x30;
   commData[3] = 0x00;
   commData[4] = 0xA4;
   commData[5] = 0xEF;

   this->comm->requestData.clear();
   this->comm->TxData.clear();
   this->comm->TxData.append(commData, 6);
   this->comm->changeTxState(true);
   comm->msleep(800);
   qDebug()<<"resize is"<<comm->requestData.size();
   iResponseLength = comm->requestData.size();

       if (iResponseLength == 8)
       {
           for(int i = 0;i<2;i++)
           {
              cangle[i] = comm->requestData[i+5] ;

           }

           int val = 0;
           for (int i = 0; i<2; i++)
            {
                if (cangle[i] >= 'a'   &&   cangle[i] <= 'f')
                    val = val * 16 + cangle[i] - 'a' + 10;
                else   if (cangle[i] >= 'A'   &&   cangle[i] <= 'F')
                    val = val * 16 + cangle[i] - 'A' + 10;
                else   if (cangle[i] >= '0'   &&   cangle[i] <= '9')
                    val = val * 16 + cangle[i] - '0';
                else
                    break;
            }

            zoompos = val;
        }
        else
        {
            return 0;
       }


   return zoompos;
}

 /*To return present focus position*/
int PTZComm::GetPTZFocusPos(void)
{
    int iResponseLength = 0;
    char  cangle[5] = { 0 };
    int focuspos = 0;
    char commData[7] = { 0 };
    commData[0] = 0xFF;
    commData[1] = 0x30;
    commData[2] = 0x30;
    commData[3] = 0x00;
    commData[4] = 0xB1;
    commData[5] = 0x30;
    commData[6] = 0xEF;


    this->comm->requestData.clear();
    this->comm->TxData.clear();
    this->comm->TxData.append(commData, 7);
    this->comm->changeTxState(true);
    comm->msleep(500);

    iResponseLength = comm->requestData.size();

    if (iResponseLength == 10)
    {
        for(int i = 0;i<4;i++)
        {
           cangle[i] = comm->requestData[i+5] ;

        }

       int val = 0;
       for (int i = 0; i<4; i++)
       {
            if (cangle[i] >= 'a'   &&   cangle[i] <= 'f')
                val = val * 16 + cangle[i] - 'a' + 10;
            else   if (cangle[i] >= 'A'   &&   cangle[i] <= 'F')
               val = val * 16 + cangle[i] - 'A' + 10;
           else   if (cangle[i] >= '0'   &&   cangle[i] <= '9')
               val = val * 16 + cangle[i] - '0';
           else
               break;
       }

        focuspos = val;
    }
    else
    {
        return 0;
    }

	

    return focuspos;
}

//rotate the PTZ pointedangle based on current posion
bool PTZComm::ReturnPTZ(const double Panangle, const double Tiltangle)
{
    char cPanAngle[5] = { 0 };
    char cTiltAngle[5] = { 0 };
    int i = 0;
    char commData[14] = {0x00};

    //double Pixelrate = 15;
    //double rotatePanAngle = (360 - ClickedPoint.x)/Pixelrate;
    //double rotateTiltAngle = (ClickedPoint.y - 240)/Pixelrate;

    //rotate PTZ
    double curPanAngle = GetPTZPanAngle();
    if ((curPanAngle >101) || (curPanAngle <-101))
        return false;
    double curTiltAngle = GetPTZTiltAngle();
    if ((curTiltAngle >31) || (curTiltAngle <-31))
        return false;
    double setpanangle = curPanAngle + Panangle;
    double setTiltange = curTiltAngle + Tiltangle;

   int PanAngle = static_cast<int>(setpanangle / 0.1125 + 32768);
   _itoa(PanAngle, cPanAngle, 16);
    for (i = 0; i<5; i++)
       if ((cPanAngle[i] >= 'a') && (cPanAngle[i] <= 'z')) cPanAngle[i] -= 32;

    int TiltAngle = static_cast<int>(setTiltange / 0.1125 + 32768);
    _itoa(TiltAngle, cTiltAngle, 16);
    for (i = 0; i<5; i++)        if ((cTiltAngle[i] >= 'a') && (cTiltAngle[i] <= 'z')) cTiltAngle[i] -= 32;

    commData[0] = 0xFF;
    commData[1] = 0x30;
    commData[2] = 0x30;
    commData[3] = 0x00;
    commData[4] = 0x62;

//    memcpy(commData + 5, cPanAngle, 4);
//    memcpy(commData + 9, cTiltAngle, 4);
    for(int  i = 0;i<4;i++)
    {
        commData[i+5] = cPanAngle[i];
    }
    for(int  i = 0;i<4;i++)
    {
        commData[i+9] = cPanAngle[i];
    }
    commData[13] = 0xEF;
    this->comm->requestData.clear();
    this->comm->TxData.clear();
    this->comm->TxData.append(commData, 14);
    this->comm->changeTxState(true);
    comm->msleep(50);


}
	
void PTZComm::PTZcontrol(Point oldPoint, Point newPoint)
{
    int PanSpeed;
    int TiltSpeed;
    if((abs(newPoint.x-oldPoint.x)<30)&&(abs(newPoint.y-oldPoint.y)<30))
    {
     // comm->stop();
      comm->msleep(50);
    }
    else
    {
        PanSpeed = (abs(newPoint.x-oldPoint.x)*0.8);
       // PanSpeedSet(PanSpeed);
       // comm->msleep(5);
        if((newPoint.x-oldPoint.x)>0)
        {
            Right();
       // comm->msleep(50);
      //  comm->stop();
       // comm->msleep(50);
        }
        if((newPoint.x-oldPoint.x)<0)
        {
            Left();
           // comm->msleep(50);
           // comm->stop();
           // comm->msleep(50);
        }
        TiltSpeed = (abs(newPoint.y-oldPoint.y)*0.8);
       // TiltSpeedSet(PanSpeed);
        comm->msleep(5);
        if((newPoint.y-oldPoint.y)<0)
        {
            Up();
          //  comm->msleep(50);
          //  comm->stop();
         //   comm->msleep(50);
        }
        if((newPoint.y-oldPoint.y)>0)
         {
            Down();
          //  comm->msleep(50);
            //comm->stop();
           // comm->msleep(50);
        }
    }
    //comm->stop();
}

/*根据当前鼠标的点击位置使得摄像头转到鼠标点击的位置*/
/*暂时不需要这个功能*/
//bool CPTZComm::ReturnPTZ(const CvPoint ClickedPoint)
//{
 //  char cPanAngle[5] = { 0 };
 //  char cTiltAngle[5] = { 0 };
 //  int i = 0;

 //  double Pixelrate = 15;
//   double rotatePanAngle = (359.5 - ClickedPoint.x) / Pixelrate;
//   double rotateTiltAngle = (ClickedPoint.y - 239.5) / Pixelrate;

  //rotate PTZ
 //  double curPanAngle = GetPTZPanAngle();
//    if ((curPanAngle >99.99) || (curPanAngle <-99.99))
//        return false;
//    double curTiltAngle = GetPTZTiltAngle();
//    if ((curTiltAngle >29.99) || (curTiltAngle <-29.99))
//        return false;
//    double setpanangle = curPanAngle - rotatePanAngle;
//    double setTiltange = curTiltAngle - rotateTiltAngle;

//    int PanAngle = (int)(setpanangle / 0.1125 + 32768);
//    _itoa(PanAngle, cPanAngle, 16);
//    for (i = 0; i<5; i++)
//        if ((cPanAngle[i] >= 'a') && (cPanAngle[i] <= 'z')) cPanAngle[i] -= 32;

//    int TiltAngle = (int)(setTiltange / 0.1125 + 32768);
//    _itoa(TiltAngle, cTiltAngle, 16);
//    for (i = 0; i<5; i++)
//        if ((cTiltAngle[i] >= 'a') && (cTiltAngle[i] <= 'z')) cTiltAngle[i] -= 32;

//    m_pCmdData[0] = 0xFF;
//    m_pCmdData[1] = 0x30;
//    m_pCmdData[2] = 0x30;
//    m_pCmdData[3] = 0x00;
//    m_pCmdData[4] = 0x62;

//    memcpy(m_pCmdData + 5, cPanAngle, 4);
//    memcpy(m_pCmdData + 9, cTiltAngle, 4);
//    m_pCmdData[13] = 0xEF;

//    ClearBuf();
//    Sleep(5);

//    m_CmdLength = 14;

//    try
//    {
//        SendData(m_pCmdData, m_CmdLength);
//        /*
//        Sleep(50);
//        m_dPTZPanAng = GetPTZPanAngle();
//        m_dPTZTiltAngle = GetPTZTiltAngle();
//        UpdateData(FALSE);
//        */
//        //return true;
//    }
//    catch (...)
//    {
//        // Inform the user if the hex string was not properly formatted
//        AfxMessageBox("Write serial port error ");
//        return false;
//    }

//}


	
