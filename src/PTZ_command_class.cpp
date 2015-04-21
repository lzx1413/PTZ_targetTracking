#include "PTZ_command_class.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QDateTime>
#include <iostream>
#include<windows.h>
using namespace std;
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
    my_serial_port->exit();
    delete my_serial_port;
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
    emit SetComNum(my_serial_port->port_num_);
    this->my_serial_port->information_.InfoDisplay("Tread of com start\n");
    qDebug() << "Thread starting" << endl;
    my_serial_port->ChangeComState(false);
    my_serial_port->start();  //串口线程开始
    qDebug() <<tr( "com has opened" )<< endl;
     this->my_serial_port->information_.InfoDisplay("com has opended");

}

void PTZCommand::PTZ_Init()
{
     //1.主机控制模式
    char  command_data_1[7] = { 0xFF, 0x30, 0x30, 0x00, 0x90, 0x30, 0xEF};
    this->my_serial_port->tx_data_.append(command_data_1, 7);
    this->my_serial_port->ChangeTxState(true);
    this->my_serial_port->msleep(20);
    //2.信号反馈设置
    char command_data_2[7] = {0xFF, 0x30, 0x30, 0x00, 0x94, 0x31, 0xEF};
    this->my_serial_port->tx_data_.append(command_data_2, 7);
    this->my_serial_port->ChangeTxState(true);
    this->my_serial_port->msleep(20);
    //3. 打开摄像头
    char command_data_3[7 ] = {0xFF, 0x30, 0x30, 0x00, 0x94, 0x31, 0xEF};
    this->my_serial_port->tx_data_.append(command_data_3, 7);
    this->my_serial_port->ChangeTxState(true);
    this->my_serial_port->information_.InfoDisplay("PTZ has been initialed\n");
}

void PTZCommand::Home(void)
{

    char command_data[6] = { 0xFF, 0x30, 0x30, 0x00, 0x57, 0xEF};
    if(this->my_serial_port->tx_data_.isEmpty())
    {
      this->my_serial_port->tx_data_.append(command_data, 6);
      this->my_serial_port->ChangeTxState(true);
    }
}

void PTZCommand::AutoLeft(bool is_stop )
{
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00,0x53, 0x32, 0xEF };
 //    if(this->my_serial_port->tx_data_.isEmpty())
//     {
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
 //    }
    if(is_stop)
    {
     // Stop();
    }
    this->my_serial_port->information_.InfoDisplay("Left");
}

void PTZCommand::AutoRight(bool is_stop)
{
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0x53, 0x31, 0xEF };
 //   if(this->my_serial_port->tx_data_.isEmpty())
 //   {
        this->my_serial_port->tx_data_.append(command_data, 7);
        this->my_serial_port->ChangeTxState(true);

 //   }
    if(is_stop)
    {
     // Stop();
    }

}

void PTZCommand::AutoUp(bool is_stop ,int stop_time )
{

    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0x53, 0x33, 0xEF };

  //  if(this->my_serial_port->tx_data_.isEmpty())
  //  {
       this->my_serial_port->tx_data_.append(command_data, 7);
       this->my_serial_port->ChangeTxState(true);
//
  //  }
    if(is_stop)
    {
    //  Stop();
    }

}


void PTZCommand::AutoDown(bool is_stop  )
{

    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0x53, 0x34, 0xEF };
   // if(this->my_serial_port->tx_data_.isEmpty())
   // {
      this->my_serial_port->tx_data_.append(command_data, 7);
      this->my_serial_port->ChangeTxState(true);
  //  }
    if(is_stop)
    {
  //    Stop();
    }

}


void PTZCommand::ManuLeft( )
{
    Stop();
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00,0x53, 0x32, 0xEF };
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
     qDebug()<<"LEFT";
    this->my_serial_port->information_.InfoDisplay("Left");
}

void PTZCommand::ManuRight()
{
    Stop();
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0x53, 0x31, 0xEF };
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
    qDebug()<<"Right"<<endl;

}

void PTZCommand::ManuUp( )
{
    Stop();
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0x53, 0x33, 0xEF };
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
}


void PTZCommand::ManuDown()
{
    Stop();
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0x53, 0x34, 0xEF };
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
}
void PTZCommand::Stop()
{
    char command_data[8]= { 0xFF, 0x30, 0x30, 0x00, 0x60, 0x30,0x30, 0xEF };
    this->my_serial_port->tx_data_.append(command_data, 8);
    this->my_serial_port->ChangeTxState(true);
}
void PTZCommand::PosSet(double cpan_angle, double ctilt_angle)
{
    char ccpan_angle[5] = { 0 };
    char cctilt_angle[5] = { 0 };
    int i = 0;

    int pan_angle = static_cast<int>(cpan_angle / 0.1125 + 32768);
    _itoa_s(pan_angle, ccpan_angle, 16);
    for (i = 0; i<5; i++)
        if ((ccpan_angle[i] >= 'a') && (ccpan_angle[i] <= 'z'))
            ccpan_angle[i] -= 32;

    int tilt_angle = static_cast<int>(ctilt_angle / 0.1125 + 32768);
    _itoa_s(tilt_angle, cctilt_angle, 16);
    for (i = 0; i<5; i++)
        if ((cctilt_angle[i] >= 'a') && (cctilt_angle[i] <= 'z'))
            cctilt_angle[i] -= 32;

    char command_data[5] = { 0xFF, 0X30, 0X30, 0X00, 0X62 };


    memcpy(command_data + 5, ccpan_angle, 4);
    memcpy(command_data + 9, cctilt_angle, 4);
    command_data[13] = 0xEF;
    this->my_serial_port->tx_data_.append(command_data, 14);
    this->my_serial_port->ChangeTxState(true);
}



void PTZCommand::ZoomIn(void)//放大
{

    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA2, 0x34,  0xEF };
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
}

void PTZCommand::ZoomOut(void)//缩小
{

    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA2, 0x33,0xEF };
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
    this->my_serial_port->tx_data_.append(command_data, 8);
    this->my_serial_port->ChangeTxState(true);
}

void PTZCommand::ZoomStop(void)
{

    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA2, 0x30, 0xEF };
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
}

void PTZCommand::FocusFar(void)//聚焦于远点
{


    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA1, 0x33, 0xEF };
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
}

void PTZCommand::FocusNear(void)//聚焦于近点
{

    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA1, 0x32, 0xEF };
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
}
void PTZCommand::FocusSetMF(void)//调节为手动对焦模式
{

    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA1, 0x31, 0xEF };
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
}


void PTZCommand::FocusSetAF(void)//调节为自动对焦模式
{
    char command_data[7] = { 0xFF, 0x30, 0x30, 0x00, 0xA1, 0x30, 0xEF };
    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
}


void PTZCommand::FocusSet(double FocusNumber)
{

    char cZoomPos[5] = { 0 };
    int i = 0;
    FocusSetMF();

    char command_data[6];
    int Zoompos = static_cast<int>(FocusNumber);
    _itoa_s(Zoompos, cZoomPos, 16);
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
    this->my_serial_port->tx_data_.append(command_data, 10);
    this->my_serial_port->ChangeTxState(true);

}
void PTZCommand::PanSpeedSet(int PanSpeed)//8-800
{
    char cPanSpeed[5] = { 0 };
    int i = 0;

    char command_data[7];
    _itoa_s(PanSpeed, cPanSpeed, 16);
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

    command_data[8] = 0xEF;
    this->my_serial_port->tx_data_.append(command_data, 9);
    this->my_serial_port->ChangeTxState(true);

}

void PTZCommand::TiltSpeedSet(int TiltSpeed)//8-622
{
    char cTiltSpeed[5] = { 0 };
    int i = 0;
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

    command_data[8] = 0xEF;
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

    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
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
    char command_data[6] = { 0 };
    command_data[0] = 0xFF;
    command_data[1] = 0x30;
    command_data[2] = 0x30;
    command_data[3] = 0x00;
    command_data[4] = 0x63;
    command_data[5] = 0xEF;
    this->my_serial_port->tx_data_.append(command_data, 6);
    this->my_serial_port->ChangeTxState(true);
    waitKey(20);
    qDebug()<<"rxevent is"<<my_serial_port->rx_event_;
    my_serial_port->rx_event_ = false;
    is_response_length = my_serial_port->request_data_.size();
    qDebug()<<"resize is"<<my_serial_port->request_data_.size();

    if (is_response_length == 14)
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
    char command_data[6] = { 0x00 };
    command_data[0] = 0xFF;
    command_data[1] = 0x30;
    command_data[2] = 0x30;
    command_data[3] = 0x00;
    command_data[4] = 0x63;
    command_data[5] = 0xEF;
    this->my_serial_port->tx_data_.append(command_data, 6);
    this->my_serial_port->ChangeTxState(true);
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

   this->my_serial_port->ChangeTxState(true);
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


    this->my_serial_port->tx_data_.append(command_data, 7);
    this->my_serial_port->ChangeTxState(true);
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

bool PTZCommand::ReturnPTZ(const double cpan_angle, const double ctilt_angle)
{
    char ccpan_angle[5] = { 0 };
    char cctilt_angle[5] = { 0 };
    int i = 0;
    char command_data[14] = {0x00};

    double curcpan_angle = GetPTZPanAngle();
    if ((curcpan_angle >101) || (curcpan_angle <-101))
        return false;
    double curctilt_angle = GetPTZTiltAngle();
    if ((curctilt_angle >31) || (curctilt_angle <-31))
        return false;
    double set_cpan_angle = curcpan_angle + cpan_angle;
    double set_ctilt_angle = curctilt_angle + ctilt_angle;

   int pan_angle = static_cast<int>(set_cpan_angle / 0.1125 + 32768);
   _itoa_s(pan_angle, ccpan_angle, 16);
    for (i = 0; i<5; i++)
       if ((ccpan_angle[i] >= 'a') && (ccpan_angle[i] <= 'z')) ccpan_angle[i] -= 32;

    int tilt_angle = static_cast<int>(set_ctilt_angle / 0.1125 + 32768);
    _itoa_s(tilt_angle, cctilt_angle, 16);
    for (i = 0; i<5; i++)        if ((cctilt_angle[i] >= 'a') && (cctilt_angle[i] <= 'z')) cctilt_angle[i] -= 32;

    command_data[0] = 0xFF;
    command_data[1] = 0x30;
    command_data[2] = 0x30;
    command_data[3] = 0x00;
    command_data[4] = 0x62;
    for(int  i = 0;i<4;i++)
    {
        command_data[i+5] = ccpan_angle[i];
    }
    for(int  i = 0;i<4;i++)
    {
        command_data[i+9] = ccpan_angle[i];
    }
    command_data[13] = 0xEF;
    this->my_serial_port->tx_data_.append(command_data, 14);
    this->my_serial_port->ChangeTxState(true);

}

void PTZCommand::PTZcontrol(Point oldPoint, Point newPoint,int frame_num)
{
    int pan_intg,tilt_intg;
    int pan_speed;
    int tilt_speed;
    Point set_point_;
    if(frame_num == 2)
    {
        last_x_state_2 = newPoint.x-oldPoint.x;
        last_y_state_2 = newPoint.y-oldPoint.y;
     }
    else if(frame_num==4)
    {
        last_x_state_ = newPoint.x-oldPoint.x;
        last_y_state_ = newPoint.y-oldPoint.y;
    }
    else
    {
        now_x_state_ = newPoint.x-oldPoint.x;
        now_y_state_ = newPoint.y-oldPoint.y;
        pan_intg+=now_x_state_;
        tilt_intg+=now_y_state_;
        set_point_.x=now_x_state_+0.2*(now_x_state_-last_x_state_);//+0.2*(now_x_state_-2*last_x_state_+last_x_state_2);
        set_point_.y=now_y_state_+0.2*(now_y_state_-last_y_state_);//+0.2*(now_y_state_-2*last_y_state_+last_y_state_2);
        //set_point_.x=//0.75*now_x_state_*0.8*0.8+0.2*(now_x_state_-last_x_state_);//+0.01*pan_intg;

        if((abs(now_x_state_)<10)&&(abs(now_y_state_)<10))
        {
           Stop();
           waitKey(20);
        }
        else
        {
            if(abs(now_x_state_)<50)
            {
                pan_speed = (abs(set_point_.x)*1.5*0.85*1.2);//0.5*2*2);
            }
            if(abs(now_x_state_)>=50)
            {
                pan_speed = (abs(set_point_.x)*1.25*0.85*1.2);//*0.3*2*2);
            }
            if(pan_speed>800)
                pan_speed = 800;
            PanSpeedSet(pan_speed);
            if(abs(now_y_state_)<50)
            {
                tilt_speed = (abs(set_point_.y)*1.2*2*0.85*0.85*1.2);//*0.8*0.5*2);
            }
            else
            {
                tilt_speed = (abs(set_point_.y)*0.6*2*0.85*0.85*1.2);//*0.8*0.2*2);
            }
            if(tilt_speed>628)
                tilt_speed=628;
            TiltSpeedSet( tilt_speed);
            Sleep(50);
    AutoTurn(now_x_state_,now_y_state_,last_x_state_,last_y_state_);

    last_x_state_2=last_x_state_;
    last_y_state_2=last_y_state_;
    last_y_state_ = now_y_state_;
    last_x_state_ = now_x_state_;
    }
}
}
void PTZCommand::AutoTurn(int now_x,int now_y,int last_x,int last_y)
{
    if(abs(now_x)<abs(now_y))
        {
            if(last_x*now_x<0)
            {
                Stop();
              //  waitKey(15);
            }
            if(now_x>0)
            {
                if((last_x>0)&&(now_x-last_x>10))
                {
                    Stop();
                //    waitKey(15);
                }
                AutoRight(false);
            }
            if(now_x<0)
            {
                if((last_x<0)&&(now_x-last_x<-10))
                {
                    Stop();
                 //   waitKey(15);
                }
                AutoLeft(false);
            }
        }

    if(last_y*now_y<0)
            {
                Stop();
            //    waitKey(15);
            }
    if(now_y>0)
            {
                if((last_y>0)&&(now_y-last_y>10))
                {
                    Stop();
                  //  waitKey(15);
                }
                AutoDown(false);
            }

    if(now_y<0)
            {
                if((last_y<0)&&(now_y-last_y<-10))
                {
                    Stop();
                 //   waitKey(15);
                }
                AutoUp(false,5);
            }


    if(abs(now_x)>abs(now_y))
    {
        if(last_x*now_x<0)
        {
            Stop();
         //   waitKey(15);
        }
        if(now_x>0)
        {
            if((last_x>0)&&(now_x-last_x>10))
            {
                Stop();
               // waitKey(15);
            }
            AutoRight(false);
        }
        if(now_x<0)
        {
            if((last_x<0)&&(now_x-last_x<-10))
            {
                Stop();
              //  waitKey(15);
            }
            AutoLeft(false);
        }
    }

}

void PTZCommand::AutoZoom(int height,int width)
{
int now_zoom=GetPTZZoomPos();
float p_height=height/480,p_width=width/640;
if(p_height<0.2&&p_width<0.2) ZoomSet(p_height*0.33/now_zoom);
else if(p_height>0.5) ZoomSet(p_height*0.33/now_zoom);
else if(p_width>0.5) ZoomSet(p_width*0.33/now_zoom);
else ZoomStop();
    /*if(height<100&&width<260)
{
    ZoomIn();
    waitKey(15);
    ZoomStop();
}
else if(height>380||width>540)
{
    ZoomOut();
    waitKey(15);
    ZoomStop();
}
else
    ZoomStop();
*/
}

void PTZCommand::CloseCom()
{
    my_serial_port->StopCom();
}

