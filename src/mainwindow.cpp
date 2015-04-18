#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QColor>
#include<QKeyEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    target_ = new TargetTracking;

    ui_->infoDisplay->setTextColor(QColor(255,255,255));
    ui_->infoDisplay->setTextBackgroundColor(QColor(0,0,0));
    QLabel *permanent  = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
    permanent->setText("lzx1444@gmail.com");
    ui_->statusBar->addPermanentWidget(permanent);

    connect(ui_->stop_tracking_,&QPushButton::clicked,target_,&TargetTracking::set_exit_flag);

    /****************窗口美化部分***************************/
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
connect(this->target_,&TargetTracking::GetFaceName,this,&MainWindow::ShowFaceName);
/************************键盘控制相关变量***********************/


/**********************视频显示*************************/
cam_ = NULL;
timer_ = new QTimer(this);
imag_ = new QImage();
connect(this->timer_,&QTimer::timeout,this,&MainWindow::ReadFrame);
connect(ui_->startvideo, &QPushButton::clicked, this, &MainWindow::OpenCamera);
connect(ui_->closevideo, &QPushButton::clicked, this, &MainWindow::CloseCamera);
/************************训练******************************/
ui_->template_num_->setValue(2);
connect(ui_->flag_of_training,&QPushButton::clicked,target_,&TargetTracking::set_flag_of_train);
connect(ui_->name_of_face_,&QLineEdit::textChanged,this->target_,&TargetTracking::AddFaceName);
connect(ui_->training,&QPushButton::clicked,this->target_,&TargetTracking::TrainingModelOfFace);
connect(ui_->template_num_,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this->target_,&TargetTracking::set_num_of_template);

/************************其他*********************************/
connect(ui_->test_button_,&QPushButton::clicked,this->target_,&TargetTracking::TestFunction);
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
    if(e->key()==Qt::Key_Space&&!e->isAutoRepeat())
    {
        if(!keypressflag_)
        {
        target_->ptz_command_->Home();
        space_pressed = true;
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
    if(e->key()==Qt::Key_Space&&space_pressed&&!e->isAutoRepeat())
    {
        if(keypressflag_)
        {
        target_->ptz_command_->Stop();
        space_pressed=false;
        }
    }

    keypressflag_ = false;
}


void MainWindow::OpenCamera()
{
    cam_ = cvCreateCameraCapture(0);//打开摄像头，从摄像头中获取视频

    timer_->start(33);
}

void MainWindow::ReadFrame()
{
    frame_ = cvQueryFrame(cam_);
    // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
     QImage image = QImage((const uchar*)frame_->imageData, frame_->width, frame_->height, QImage::Format_RGB888).rgbSwapped();
    ui_->video->setPixmap(QPixmap::fromImage(image));  // 将图片显示到label上
}

void MainWindow::TakingPictures()
{
 //TODO 截图
}

void MainWindow::CloseCamera()
{
    timer_->stop();
    cvReleaseCapture(&cam_);
}

void MainWindow::ShowFaceName()
{
    face_ =target_->ReturnNoramlizedImage();
    face2show_ = QImage((const unsigned char*)(face_.data), face_.cols, face_.rows, QImage::Format_RGB888).rgbSwapped();
    ui_->photo1->setPixmap(QPixmap::fromImage(face2show_));
    ui_->photo1->resize(ui_->photo1->pixmap()->size());
    ui_->name1->setText(target_->GetNameOfList());


}
