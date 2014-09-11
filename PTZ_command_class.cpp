#include "PTZ_command_class.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QDateTime>
PTZCommand::PTZCommand()
{
    my_serial_port = new MySerialPort;
    this->my_serial_port->ChangeTxState(false);
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    time_stop_ = 10;
    last_x_state_ = 1;
    last_y_state_ = 1;
    now_x_state_ = 1;
    now_y_state_ = 1;

}


PTZCommand::~PTZCommand()
{
  //  delete my_serial_port;
}


void PTZCommand::CommInit()
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		qDebug() << "Name        : " << info.portName();
		qDebug() << "Description : " << info.description();
		qDebug() << "Manufacturer: " << info.manufacturer();
        this-> my_serial_port->information_.InfoDisplay(info.portName()+"\n"+info.description()+"\n"+ info.manufacturer()+"\n");


        my_serial_port->SetPortnum(info.portName());
//TODO:刷新可用串口再选择的实现

    } // 查找所有可用串口
    my_serial_port->StartCom();
	qDebug() << "Thread starting" << endl;
    my_serial_port->ChangeComState(false);
    my_serial_port->start();  //串口线程开始
    qDebug() <<tr( "com has opened" )<< endl;
    
}

void PTZCommand::PTZ_Init()
{
     //1.主机控制模式
    char  command_data_1[7] = { 0xFF, 0x30, 0x30, 0x00, 0x90, 0x30, 0xEF};
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->tx_data_.append(command_data_1, 7);
    this->my_serial_port->ChangeTxState(true);
    //this->my_serial_port->msleep(20);
    waitKey(20);


    //2.信号反馈设置
    //writestring = "FF 30 30 00 94 31 EF";
    char command_data_2[7] = {0xFF, 0x30, 0x30, 0x00, 0x94, 0x31, 0xEF};
   // this->command_data.clear();
  //  this->command_data.append( 0xFF, 0x30, 0x30, 0x00, 0x94, 0x31, 0xEF );
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data_2, 7);
    this->my_serial_port->ChangeTxState(true);
    //this->my_serial_port->msleep(20);
    waitKey(20);
    //3. 打开摄像头
    //    writestring = "FF 30 30 00 A0 31 EF";
    char command_data_3[7 ] = {0xFF, 0x30, 0x30, 0x00, 0x94, 0x31, 0xEF};
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data_3, 7);
    this->my_serial_port->ChangeTxState(true);
     waitKey(20);
}
void PTZCommand::Home(void)
{
    PanSpeedSet(800);
    waitKey(20);
    TiltSpeedSet(622);
    waitKey(20);

    char command_data[6] = { 0xFF, 0x30, 0x30, 0x00, 0x57, 0xEF};
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 6);
    this->my_serial_port->ChangeTxState(true);
}

void PTZCommand::AutoLeft(bool is_stop,int stop_time )
{
   // char command_data[8] = { 0xFF, 0x30, 0x30, 0x00,0x60, 0x31,0x30, 0xEF };
    //PanSpeedSet(200);
    this->my_serial_port->msleep(5);
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00,0x53, 0x32, 0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
   // this->my_serial_port->msleep(stop_time);
    if(is_stop)
    {
      Stop();
      //this->my_serial_port->msleep(50);
      waitKey(20);
    }



    qDebug()<<"LEFT";
   // this->comm->stop();
    this->my_serial_port->information_.InfoDisplay("Left");
}

void PTZCommand::AutoRight(bool is_stop ,int stop_time)
{
    //char command_data[8] = { 0xFF, 0x30, 0x30, 0x00, 0x60, 0x32, 0x30, 0xEF };
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0x53, 0x31, 0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
    qDebug()<<"Right"<<endl;
   // this->comm->msleep(TimeStop);
   // this->comm->stop();
    this->my_serial_port->msleep(stop_time);
    if(is_stop)
    {
      Stop();
      //this->my_serial_port->msleep(50);
      waitKey(20);
    }

}

void PTZCommand::AutoUp(bool is_stop ,int stop_time )
{


   // char command_data[8] = { 0xFF, 0x30, 0x30, 0x00, 0x60, 0x30, 0x31, 0xEF };
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0x53, 0x33, 0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
    //this->comm->msleep(TimeStop);
    //this->comm->stop();
    this->my_serial_port->msleep(stop_time);
    if(is_stop)
    {
      Stop();
     // this->my_serial_port->msleep(50);
      waitKey(20);
    }

}


void PTZCommand::AutoDown(bool is_stop ,int stop_time )
{


    //char command_data[8]= { 0xFF, 0x30, 0x30, 0x00, 0x60, 0x30, 0x32, 0xEF };
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0x53, 0x34, 0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
   // this->comm->msleep(TimeStop);
   // this->comm->stop();
   // this->my_serial_port->msleep(stop_time);
    if(is_stop)
    {
      Stop();
      //this->my_serial_port->msleep(50);
      waitKey(20);
    }

}


void PTZCommand::ManuLeft( )
{
   // char command_data[8] = { 0xFF, 0x30, 0x30, 0x00,0x60, 0x31,0x30, 0xEF };
   // PanSpeedSet(800);
    //this->my_serial_port->msleep(5);
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00,0x53, 0x32, 0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
    //this->my_serial_port->msleep(500);

   // this->my_serial_port->msleep(50);
     waitKey(200);
   //  Stop();
     waitKey(20);



    qDebug()<<"LEFT";
   // this->comm->stop();
    this->my_serial_port->information_.InfoDisplay("Left");
}

void PTZCommand::ManuRight()
{
    //char command_data[8] = { 0xFF, 0x30, 0x30, 0x00, 0x60, 0x32, 0x30, 0xEF };
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0x53, 0x31, 0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
    qDebug()<<"Right"<<endl;
   // this->comm->msleep(TimeStop);
   // this->comm->stop();
   // this->my_serial_port->msleep(500);

    //this->my_serial_port->msleep(50);
    waitKey(200);
  //  Stop();
    waitKey(20);


}

void PTZCommand::ManuUp( )
{
    // char command_data[8] = { 0xFF, 0x30, 0x30, 0x00, 0x60, 0x30, 0x31, 0xEF };
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0x53, 0x33, 0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
    //this->comm->msleep(TimeStop);
    //this->comm->stop();
   // this->my_serial_port->msleep(500);

    //this->my_serial_port->msleep(50);
    waitKey(200);
   // Stop();
    waitKey(20);
}


void PTZCommand::ManuDown()
{
    //char command_data[8]= { 0xFF, 0x30, 0x30, 0x00, 0x60, 0x30, 0x32, 0xEF };
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0x53, 0x34, 0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
   // this->comm->msleep(TimeStop);
   // this->comm->stop();
   // this->my_serial_port->msleep(500);

    //this->my_serial_port->msleep(50);
    waitKey(200);
   // Stop();
    waitKey(20);
}
void PTZCommand::Stop()
{
    char command_data[8]= { 0xFF, 0x30, 0x30, 0x00, 0x60, 0x30,0x30, 0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 8);
    this->my_serial_port->ChangeTxState(true);
}
void PTZCommand::PosSet(double cpan_angle, double ctilt_angle)
{
    char ccpan_angle[5] = { 0 };
    char cctilt_angle[5] = { 0 };
    int i = 0;

    int pan_angle = static_cast<int>(cpan_angle / 0.1125 + 32768);
    _itoa(pan_angle, ccpan_angle, 16);
    for (i = 0; i<5; i++)
        if ((ccpan_angle[i] >= 'a') && (ccpan_angle[i] <= 'z'))
            ccpan_angle[i] -= 32;

    int tilt_angle = static_cast<int>(ctilt_angle / 0.1125 + 32768);
    _itoa(tilt_angle, cctilt_angle, 16);
    for (i = 0; i<5; i++)
        if ((cctilt_angle[i] >= 'a') && (cctilt_angle[i] <= 'z'))
            cctilt_angle[i] -= 32;

    char command_data[5] = { 0xFF, 0X30, 0X30, 0X00, 0X62 };


    memcpy(command_data + 5, ccpan_angle, 4);
    memcpy(command_data + 9, cctilt_angle, 4);
    command_data[13] = 0xEF;
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 14);
    this->my_serial_port->ChangeTxState(true);
}



void PTZCommand::ZoomIn(void)//放大
{

    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA2, 0x34,  0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
}

void PTZCommand::ZoomOut(void)//缩小
{

    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA2, 0x33,0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
}
void PTZCommand::ZoomSet(int zoomNumber)
{
    char cZoomPos[5] = { 0 };
    int i = 0;
    char command_data[6] = { 0 };

    int Zoompos = (zoomNumber);

    _itoa(Zoompos, cZoomPos, 16);
    for (i = 0; i<5; i++)
        if ((cZoomPos[i] >= 'a') && (cZoomPos[i] <= 'z')) cZoomPos[i] -= 32;

    command_data[0] = 0xFF;
    command_data[1] = 0x30;
    command_data[2] = 0x30;
    command_data[3] = 0x00;
    command_data[4] = 0xA3;

    if (zoomNumber <16)
    {
        command_data[5] = 0x30;
        memcpy(command_data + 6, cZoomPos, 1);
    }
    else
    {
        memcpy(command_data + 5, cZoomPos, 2);
    }

    command_data[7] = 0xEF;
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 8);
    this->my_serial_port->ChangeTxState(true);
}

void PTZCommand::ZoomStop(void)
{

    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA2, 0x30, 0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
}

void PTZCommand::FocusFar(void)//聚焦于远点
{


    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA1, 0x33, 0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
}

void PTZCommand::FocusNear(void)//聚焦于近点
{

    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA1, 0x32, 0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
}
void PTZCommand::FocusSetMF(void)//调节为手动对焦模式
{
	
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA1, 0x31, 0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
}


void PTZCommand::FocusSetAF(void)//调节为自动对焦模式
{
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA1, 0x30, 0xEF };
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
}


void PTZCommand::FocusSet(double FocusNumber)
{

    char cZoomPos[5] = { 0 };
    int i = 0;

    //Set manual focus mode
    FocusSetMF();

    char command_data[6];
    int Zoompos = static_cast<int>(FocusNumber);
    _itoa(Zoompos, cZoomPos, 16);
    for (i = 0; i<5; i++)
        if ((cZoomPos[i] >= 'a') && (cZoomPos[i] <= 'z')) cZoomPos[i] -= 32;

    command_data[0] = 0xFF;
    command_data[1] = 0x30;
    command_data[2] = 0x30;
    command_data[3] = 0x00;
    command_data[4] = 0xB0;
    command_data[5] = 0x30;

    memcpy(command_data + 6, cZoomPos, 3);

    command_data[9] = 0xEF;
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 10);
    this->my_serial_port->ChangeTxState(true);

    //return to auto focus mode
    //FocusSetAF();
}
void PTZCommand::PanSpeedSet(int PanSpeed)
{
    char cPanSpeed[5] = { 0 };
    int i = 0;

    //Set manual focus mode
   // FocusSetMF();

    char command_data[7];
    _itoa(PanSpeed, cPanSpeed, 16);
    for (i = 0; i<5; i++)
        if ((cPanSpeed[i] >= 'a') && (cPanSpeed[i] <= 'z'))
            cPanSpeed[i] = cPanSpeed[i]- 32;

    command_data[0] = 0xFF;
    command_data[1] = 0x30;
    command_data[2] = 0x30;
    command_data[3] = 0x00;
    command_data[4] = 0x50;
    if(PanSpeed<16)
    {
        command_data[5] = 0x30;
        command_data[6] = 0x30;
        memcpy(command_data + 7, cPanSpeed, 1);

    }
    if((PanSpeed>=16)&&(PanSpeed<255))
    {
        command_data[5] = 0x30;
        memcpy(command_data + 6,cPanSpeed, 2);
    }
    else
    {

        memcpy(command_data + 5, cPanSpeed, 3);
    }
//    memcpy(command_data + 6, cZoomPos, 3);

    command_data[8] = 0xEF;
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 9);
    this->my_serial_port->ChangeTxState(true);

}

void PTZCommand::TiltSpeedSet(int TiltSpeed)
{
    char cTiltSpeed[5] = { 0 };
    int i = 0;

    //Set manual focus mode
   // FocusSetMF();

    char command_data[7];
    _itoa(TiltSpeed, cTiltSpeed, 16);
    for (i = 0; i<5; i++)
        if ((cTiltSpeed[i] >= 'a') && (cTiltSpeed[i] <= 'z')) cTiltSpeed[i] -= 32;

    command_data[0] = 0xFF;
    command_data[1] = 0x30;
    command_data[2] = 0x30;
    command_data[3] = 0x00;
    command_data[4] = 0x51;
    if(TiltSpeed<16)
    {
        command_data[5] = 0x30;
        command_data[6] = 0x30;
        memcpy(command_data + 7,cTiltSpeed, 1);

    }
    if((TiltSpeed>=16)&&(TiltSpeed<255))
    {
        command_data[5] = 0x30;
        memcpy(command_data + 6, cTiltSpeed, 2);
    }
    else
    {

        memcpy(command_data + 5, cTiltSpeed, 3);
    }
//    memcpy(command_data + 6, cZoomPos, 3);

    command_data[8] = 0xEF;
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 9);
    this->my_serial_port->ChangeTxState(true);

}


void PTZCommand::GetPTZFocusRange(int *nMinValue, int *nMaxValue)
{
    int is_response_length = 0;
    char cResponseDate[256] = { 0 };
    char  cangle[5] = { 0 };
    int nMinV = 0;
    int nMaxV = 0;
    char command_data[7] = { 0 };

    command_data[0] = 0xFF;
    command_data[1] = 0x30;
    command_data[2] = 0x30;
    command_data[3] = 0x00;
    command_data[4] = 0xB1;
    command_data[5] = 0x32;
    command_data[6] = 0xEF;


    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
   // my_serial_port->msleep(50);
    waitKey(20);

    is_response_length = my_serial_port->request_data_.size();

    if (is_response_length = 14)
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
double PTZCommand::GetPTZPanAngle(void)
{
    int is_response_length = 0;
    char  cangle[5] = { 0 };
    double cpan_angle = 0.0;
   // int istep = 0;
    char command_data[6] = { 0 };
    command_data[0] = 0xFF;
    command_data[1] = 0x30;
    command_data[2] = 0x30;
    command_data[3] = 0x00;
    command_data[4] = 0x63;
    command_data[5] = 0xEF;
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 6);
    this->my_serial_port->ChangeTxState(true);
    //my_serial_port->msleep(50);
    waitKey(20);
    qDebug()<<"rxevent is"<<my_serial_port->rx_event_;
    my_serial_port->rx_event_ = false;
    is_response_length = my_serial_port->request_data_.size();
    qDebug()<<"resize is"<<my_serial_port->request_data_.size();

    if (is_response_length == 14)
    {
//        memcpy(cangle, comm->request_data_ + 5, 4);
        for(int i = 0;i<4;i++)
        {
           cangle[i] = my_serial_port->request_data_[i+5] ;

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

        cpan_angle = (val - 32768)*0.1125;
    }
    else
    {
        return 0;
    }


    return cpan_angle;
}


/**********获得当前TILT的角度*************/
double PTZCommand::GetPTZTiltAngle(void)
{
    int is_response_length = 0;
    char  cangle[5] = { 0 };
    double ctilt_angle = 0.0;
   // int istep = 0;
    char command_data[6] = { 0x00 };
    command_data[0] = 0xFF;
    command_data[1] = 0x30;
    command_data[2] = 0x30;
    command_data[3] = 0x00;
    command_data[4] = 0x63;
    command_data[5] = 0xEF;
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 6);
    this->my_serial_port->ChangeTxState(true);
  //  my_serial_port->msleep(500);

    is_response_length = my_serial_port->request_data_.size();

    if (is_response_length == 14)
    {
            for(int i = 0;i<4;i++)
            {
               cangle[i] = my_serial_port->request_data_[i+9] ;

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

        ctilt_angle = (val - 32768)*0.1125;
    }
    else
    {
        return 0;
    }

    return ctilt_angle;
}


 int PTZCommand::GetPTZZoomPos(void)
{
   int is_response_length = 0;
   char  cangle[3] = { 0 };
   int zoompos = 0;
   char command_data[6] = { 0X00 };
   command_data[0] = 0xFF;
   command_data[1] = 0x30;
   command_data[2] = 0x30;
   command_data[3] = 0x00;
   command_data[4] = 0xA4;
   command_data[5] = 0xEF;

   this->my_serial_port->request_data_.clear();
   this->my_serial_port->tx_data_.clear();
   this->my_serial_port->tx_data_.append(command_data, 6);
   this->my_serial_port->ChangeTxState(true);
 //  my_serial_port->msleep(800);
   waitKey(20);
   qDebug()<<"resize is"<<my_serial_port->request_data_.size();
   is_response_length = my_serial_port->request_data_.size();

       if (is_response_length == 8)
       {
           for(int i = 0;i<2;i++)
           {
              cangle[i] = my_serial_port->request_data_[i+5] ;

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
int PTZCommand::GetPTZFocusPos(void)
{
    int is_response_length = 0;
    char  cangle[5] = { 0 };
    int focuspos = 0;
    char command_data[7] = { 0 };
    command_data[0] = 0xFF;
    command_data[1] = 0x30;
    command_data[2] = 0x30;
    command_data[3] = 0x00;
    command_data[4] = 0xB1;
    command_data[5] = 0x30;
    command_data[6] = 0xEF;


    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
   // my_serial_port->msleep(500);
    waitKey(20);

    is_response_length = my_serial_port->request_data_.size();

    if (is_response_length == 10)
    {
        for(int i = 0;i<4;i++)
        {
           cangle[i] = my_serial_port->request_data_[i+5] ;

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
bool PTZCommand::ReturnPTZ(const double cpan_angle, const double ctilt_angle)
{
    char ccpan_angle[5] = { 0 };
    char cctilt_angle[5] = { 0 };
    int i = 0;
    char command_data[14] = {0x00};

    //double Pixelrate = 15;
    //double rotatecpan_angle = (360 - ClickedPoint.x)/Pixelrate;
    //double rotatectilt_angle = (ClickedPoint.y - 240)/Pixelrate;

    //rotate PTZ
    double curcpan_angle = GetPTZPanAngle();
    if ((curcpan_angle >101) || (curcpan_angle <-101))
        return false;
    double curctilt_angle = GetPTZTiltAngle();
    if ((curctilt_angle >31) || (curctilt_angle <-31))
        return false;
    double set_cpan_angle = curcpan_angle + cpan_angle;
    double set_ctilt_angle = curctilt_angle + ctilt_angle;

   int pan_angle = static_cast<int>(set_cpan_angle / 0.1125 + 32768);
   _itoa(pan_angle, ccpan_angle, 16);
    for (i = 0; i<5; i++)
       if ((ccpan_angle[i] >= 'a') && (ccpan_angle[i] <= 'z')) ccpan_angle[i] -= 32;

    int tilt_angle = static_cast<int>(set_ctilt_angle / 0.1125 + 32768);
    _itoa(tilt_angle, cctilt_angle, 16);
    for (i = 0; i<5; i++)        if ((cctilt_angle[i] >= 'a') && (cctilt_angle[i] <= 'z')) cctilt_angle[i] -= 32;

    command_data[0] = 0xFF;
    command_data[1] = 0x30;
    command_data[2] = 0x30;
    command_data[3] = 0x00;
    command_data[4] = 0x62;

//    memcpy(command_data + 5, ccpan_angle, 4);
//    memcpy(command_data + 9, cctilt_angle, 4);
    for(int  i = 0;i<4;i++)
    {
        command_data[i+5] = ccpan_angle[i];
    }
    for(int  i = 0;i<4;i++)
    {
        command_data[i+9] = ccpan_angle[i];
    }
    command_data[13] = 0xEF;
    this->my_serial_port->request_data_.clear();
    this->my_serial_port->tx_data_.clear();
    this->my_serial_port->tx_data_.append(command_data, 14);
    this->my_serial_port->ChangeTxState(true);
  //  my_serial_port->msleep(50);


}
	
void PTZCommand::PTZcontrol(Point oldPoint, Point newPoint,int frame_num)
{
    int pan_speed;
    int tilt_speed;
    if(frame_num == 1)
    {
        last_x_state_ = newPoint.x-oldPoint.x;
        last_y_state_ = newPoint.y-oldPoint.y;
     }
    else
    {
    if((abs(newPoint.x-oldPoint.x)<10)&&(abs(newPoint.y-oldPoint.y)<10))
    {
      Stop();
      waitKey(20);
    }
    else
    {
        if(abs(newPoint.x-oldPoint.x)<100)
        {
           pan_speed = (abs(newPoint.x-oldPoint.x)*1.25*0.8*2);
        }
        if(abs(newPoint.x-oldPoint.x)>=100)
        {
            pan_speed = (abs(newPoint.x-oldPoint.x)*1.25*0.6*2);
        }
        PanSpeedSet(pan_speed);
       // my_serial_port->msleep(5);
        waitKey(15);
        if(abs(newPoint.y-oldPoint.y)<100)
        {
           tilt_speed = (abs(newPoint.y-oldPoint.y)*0.6*0.2);
        }
        else
        {
            tilt_speed = (abs(newPoint.y-oldPoint.y)*0.6*0.1);
        }
       // TiltSpeed = (abs(newPoint.y-oldPoint.y)*0.6*0.8);
        TiltSpeedSet(50);
        waitKey(15);
//        if((newPoint.x-oldPoint.x)>0)
//        {
//            now_x_state_ = 1;
//            if(last_x_state_*now_x_state_ == -1)
//            {
//                Stop();
//               waitKey(60);
//            }
//             AutoRight(false,10);
//       // comm->msleep(50);
//      //  comm->stop();
//       // comm->msleep(50);
//        }
//        if((newPoint.x - oldPoint.x) < 0)
//        {
//            now_x_state_ = -1;
//            if(last_x_state_*now_x_state_ == -1)
//            {
//               Stop();
//               waitKey(60);
//            }
//             AutoLeft(false,10);
//        }
        now_x_state_ = newPoint.x-oldPoint.x;

        if(last_x_state_*now_x_state_<0)
        {
            Stop();
            waitKey(15);
        }
        if(now_x_state_>0)
        {
            if((last_x_state_>0)&&(now_x_state_-last_x_state_>10))
            {
                Stop();
                waitKey(15);
            }
            AutoRight(false,5);
        }
        if(now_x_state_<0)
        {
            if((last_x_state_<0)&&(now_x_state_-last_x_state_<-10))
            {
                Stop();
                waitKey(15);
            }
            AutoLeft(false,5);
        }
        last_x_state_ = now_x_state_;


//        if((newPoint.y-oldPoint.y) > 0)
//        {
//            now_y_state_ = 1;
//            if(last_y_state_*now_y_state_ == -1)
//            {
//                Stop();
//                waitKey(50);
//            }
//             AutoDown(false,10);
//        }
//         if((newPoint.y-oldPoint.y) < 0)
//         {
//             now_x_state_ = -1;
//             if(last_y_state_*now_y_state_ == -1)
//             {
//                 Stop();
//                 waitKey(50);
//             }
//              AutoUp(false,10);
//         }

        now_y_state_ = newPoint.y-oldPoint.y;
        if(last_y_state_*now_y_state_<0)
        {
            Stop();
            waitKey(15);
        }
        if(now_y_state_>0)
        {
            if((last_y_state_>0)&&(now_y_state_-last_y_state_>10))
            {
                Stop();
                waitKey(15);
            }
            AutoDown(false,5);
        }
        if(now_y_state_<0)
        {
            if((last_y_state_<0)&&(now_y_state_-last_y_state_<-10))
            {
                Stop();
                waitKey(15);
            }
            AutoUp(false,5);
        }
         last_y_state_ = now_y_state_;
    }
    //comm->stop();
    }
}

/*根据当前鼠标的点击位置使得摄像头转到鼠标点击的位置*/
/*暂时不需要这个功能*/
//bool CPTZComm::ReturnPTZ(const CvPoint ClickedPoint)
//{
 //  char ccpan_angle[5] = { 0 };
 //  char cctilt_angle[5] = { 0 };
 //  int i = 0;

 //  double Pixelrate = 15;
//   double rotatecpan_angle = (359.5 - ClickedPoint.x) / Pixelrate;
//   double rotatectilt_angle = (ClickedPoint.y - 239.5) / Pixelrate;

  //rotate PTZ
 //  double curcpan_angle = GetPTZcpan_angle();
//    if ((curcpan_angle >99.99) || (curcpan_angle <-99.99))
//        return false;
//    double curctilt_angle = GetPTZctilt_angle();
//    if ((curctilt_angle >29.99) || (curctilt_angle <-29.99))
//        return false;
//    double set_cpan_angle = curcpan_angle - rotatecpan_angle;
//    double set_ctilt_angle = curctilt_angle - rotatectilt_angle;

//    int cpan_angle = (int)(set_cpan_angle / 0.1125 + 32768);
//    _itoa(cpan_angle, ccpan_angle, 16);
//    for (i = 0; i<5; i++)
//        if ((ccpan_angle[i] >= 'a') && (ccpan_angle[i] <= 'z')) ccpan_angle[i] -= 32;

//    int ctilt_angle = (int)(set_ctilt_angle / 0.1125 + 32768);
//    _itoa(ctilt_angle, cctilt_angle, 16);
//    for (i = 0; i<5; i++)
//        if ((cctilt_angle[i] >= 'a') && (cctilt_angle[i] <= 'z')) cctilt_angle[i] -= 32;

//    m_pCmdData[0] = 0xFF;
//    m_pCmdData[1] = 0x30;
//    m_pCmdData[2] = 0x30;
//    m_pCmdData[3] = 0x00;
//    m_pCmdData[4] = 0x62;

//    memcpy(m_pCmdData + 5, ccpan_angle, 4);
//    memcpy(m_pCmdData + 9, cctilt_angle, 4);
//    m_pCmdData[13] = 0xEF;

//    ClearBuf();
//    Sleep(5);

//    m_CmdLength = 14;

//    try
//    {
//        SendData(m_pCmdData, m_CmdLength);
//        /*
//        Sleep(50);
//        m_dPTZPanAng = GetPTZcpan_angle();
//        m_dPTZctilt_angle = GetPTZctilt_angle();
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


	
