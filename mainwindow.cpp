#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QColor>
#include<QKeyEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
//    ptzComm = new PTZComm;
    target_ = new TargetTracking;

    ui_->infoDisplay->setTextColor(QColor(255,255,255));
    ui_->infoDisplay->setTextBackgroundColor(QColor(0,0,0));
    QLabel *permanent  = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
    permanent->setText("lzx1444@gmail.com");
    ui_->statusBar->addPermanentWidget(permanent);

    connect(ui_->stop_tracking_,&QPushButton::clicked,target_,&TargetTracking::set_exit_flag);

    /****************窗口美化部分***************************/
    //setWindowFlags(windowFlags() | Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint);
    /****************窗口背景********************************/

    QPixmap pixmap = QPixmap("D:/bg3.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    /********************串口控制部分*********************/
    connect(target_->ptz_command_,&PTZCommand::SetComNum,ui_->comNumber,&QLineEdit::setText);
    connect(ui_->comClose,&QPushButton::clicked,target_->ptz_command_,&PTZCommand::CloseCom);
    connect(ui_->comOpen,&QPushButton::clicked,target_->ptz_command_,&PTZCommand::CommInit);
    //ui_->comNumber->setText("asfasdf");
    /**********PT相关控制部分******************************/
    connect(this->ui_->PTZ_home,&QPushButton::clicked,target_->ptz_command_,&PTZCommand::Home);
    connect(this->ui_->PTZ_left,&QPushButton::pressed,target_->ptz_command_,&PTZCommand::ManuLeft);
    connect(this->ui_->PTZ_left,&QPushButton::released,target_->ptz_command_,&PTZCommand::Stop);
    connect(this->ui_->PTZ_right,&QPushButton::pressed,target_->ptz_command_,&PTZCommand::ManuRight);
    connect(this->ui_->PTZ_right,&QPushButton::released,target_->ptz_command_,&PTZCommand::Stop);
    connect(this->ui_->PTZ_up,&QPushButton::pressed,target_->ptz_command_,&PTZCommand::ManuUp);
    connect(this->ui_->PTZ_up,&QPushButton::released,target_->ptz_command_,&PTZCommand::Stop);
    connect(this->ui_->PTZ_down,&QPushButton::pressed,target_->ptz_command_,&PTZCommand::ManuDown);
    connect(this->ui_->PTZ_down,&QPushButton::released,target_->ptz_command_,&PTZCommand::Stop);
    connect(this->ui_->stop,&QPushButton::clicked,target_->ptz_command_,&PTZCommand::Stop);

    ui_->ZoomChange->setMinimum(0);
    ui_->ZoomChange->setMaximum(128);
    ui_->ZoomChange->setValue(0);
    ui_->ZoomNumber->setMaximum(128);
    ui_->ZoomNumber->setMaximum(128);
    ui_->PanSpeed->setMaximum(800);
    ui_->PanSpeed->setMinimum(8);
    ui_->PanSpeed->setValue(800);
    ui_->TiltSpeed->setMaximum(622);
    ui_->TiltSpeed->setMinimum(8);
    ui_->TiltSpeed->setValue(622);
    connect(this->ui_->PanSpeed,&QSlider::valueChanged,target_->ptz_command_,&PTZCommand::PanSpeedSet);
     connect(this->ui_->TiltSpeed,&QSlider::valueChanged,target_->ptz_command_,&PTZCommand::TiltSpeedSet);
    connect(this->ui_->ZoomChange,&QSlider::valueChanged,target_->ptz_command_,&PTZCommand::ZoomSet);
    connect(this->ui_->ZoomChange,&QSlider::valueChanged,this->ui_->ZoomNumber,&QSpinBox::setValue);
    connect(this->ui_->comOpen,&QPushButton::clicked,target_->ptz_command_->my_serial_port,&MySerialPort::StartCom);
    connect(this->ui_->comClose,&QPushButton::clicked,target_->ptz_command_->my_serial_port,&MySerialPort::StopCom);
    ui_->comNumber->setText(target_->ptz_command_->my_serial_port->port_num_);
   /**********************跟踪控制部分**********************************/
   connect(this->ui_->startTracking,&QPushButton::clicked,target_,&TargetTracking::tracking);


/***********************信息显示部分****************************/
connect(&this->target_->ptz_command_->my_serial_port->information_,&InformationFeedback::GetInfomation,ui_->infoDisplay,&QTextEdit::append);

/************************键盘控制相关变量***********************/
keypressflag_ = false;
up_pressed = false;
down_pressed = false;
right_pressed = false;
left_pressed = false;

/**********************视频显示*************************/
cam_ = NULL;
timer_ = new QTimer(this);
imag_ = new QImage();
connect(this->timer_,&QTimer::timeout,this,&MainWindow::ReadFrame);
connect(ui_->startvideo, &QPushButton::clicked, this, &MainWindow::OpenCamera);
connect(ui_->takepic, &QPushButton::clicked, this, &MainWindow::TakingPictures);
connect(ui_->closevideo, &QPushButton::clicked, this, &MainWindow::CloseCamera);

}

MainWindow::~MainWindow()
{
    delete ui_;
    delete target_;
}
void MainWindow::StartTracking()
{
    target_->tracking();
}

/*******************键盘映射部分*************************/
void MainWindow::keyPressEvent(QKeyEvent *e)
{

    if(e->key()==Qt::Key_Up&&!e->isAutoRepeat())
    {
        if(!keypressflag_)
        {
        target_->ptz_command_->ManuUp();
        up_pressed = true;
        }
    }
    if(e->key()==Qt::Key_Down&&!e->isAutoRepeat())
    {
        if(!keypressflag_)
        {
        target_->ptz_command_->ManuDown();
        down_pressed = true;
        }
    }
    if(e->key()==Qt::Key_Right&&!e->isAutoRepeat())
    {
        if(!keypressflag_)
        {
        target_->ptz_command_->ManuRight();
        right_pressed = true;
        }
    }
    if(e->key()==Qt::Key_Left&&!e->isAutoRepeat())
    {
        if(!keypressflag_)
        {
        target_->ptz_command_->ManuLeft();
        left_pressed = true;
        }
    }

    keypressflag_ = true;
}

void MainWindow::keyReleaseEvent(QKeyEvent*e)
{
    if(e->key()==Qt::Key_Up&&up_pressed&&!e->isAutoRepeat())
    {
        if(keypressflag_)
        {
        target_->ptz_command_->Stop();
        up_pressed=false;
        }
    }
    if(e->key()==Qt::Key_Down&&down_pressed&&!e->isAutoRepeat())
    {
        if(keypressflag_)
        {
        target_->ptz_command_->Stop();
        down_pressed=false;
        }
    }
    if(e->key()==Qt::Key_Right&&right_pressed&&!e->isAutoRepeat())
    {
        if(keypressflag_)
        {
        target_->ptz_command_->Stop();
        right_pressed=false;
        }
    }
    if(e->key()==Qt::Key_Left&&left_pressed&&!e->isAutoRepeat())
    {
        if(keypressflag_)
        {
        target_->ptz_command_->Stop();
        left_pressed=false;
        }
    }

    keypressflag_ = false;
}



//void MainWindow::DisplayMat(Mat mat)
//{
//     cv::Mat rgb;
//     QImage img;
//     if(mat.channels()==3)
//     {
//         cv::cvtColor(mat,rgb,CV_BGR2RGB);
//         img = QImage((const uchar*)(rgb.data),rgb.cols,rgb.rows,rgb.cols*rgb.channels(),QImage::Format_RGB888);
//     }
//     else
//     {
//         img = QImage((const uchar*)(mat.data),mat.cols,mat.rows,mat.cols*mat.channels(),QImage::Format_Indexed8);
//     }
//     ui_->video->setPixmap(QPixmap::fromImage(img));
//     ui_->video->resize(ui_->video->pixmap()->size());
//     ui_->video->show();

//}
void MainWindow::OpenCamera()
{
    cam_ = cvCreateCameraCapture(0);//打开摄像头，从摄像头中获取视频

    timer_->start(33);              // 开始计时，超时则发出timeout()信号
}

/*********************************
********* 读取摄像头信息 ***********
**********************************/
void MainWindow::ReadFrame()
{
    frame_ = cvQueryFrame(cam_);// 从摄像头中抓取并返回每一帧
    // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
     QImage image = QImage((const uchar*)frame_->imageData, frame_->width, frame_->height, QImage::Format_RGB888).rgbSwapped();
    ui_->video->setPixmap(QPixmap::fromImage(image));  // 将图片显示到label上
}

/*************************
********* 拍照 ***********
**************************/
void MainWindow::TakingPictures()
{

}

/*******************************
***关闭摄像头，释放资源，必须释放***
********************************/
void MainWindow::CloseCamera()
{
    timer_->stop();         // 停止读取数据。

    cvReleaseCapture(&cam_);//释放内存；
}

