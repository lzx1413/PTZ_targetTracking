#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QColor>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
//    ptzComm = new PTZComm;
    target_ = new TargetTracking;
    //target_->ptz_command_->CommInit();
    //target_-> ptz_command_->PTZ_Init();
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
    QPixmap pixmap = QPixmap("D:/bg.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
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
    connect(this->ui_->ZoomChange,&QSlider::valueChanged,target_->ptz_command_,&PTZCommand::ZoomSet);
    connect(this->ui_->ZoomChange,&QSlider::valueChanged,this->ui_->ZoomNumber,&QSpinBox::setValue);
    connect(this->ui_->comOpen,&QPushButton::clicked,target_->ptz_command_->my_serial_port,&MySerialPort::StartCom);
    connect(this->ui_->comClose,&QPushButton::clicked,target_->ptz_command_->my_serial_port,&MySerialPort::StopCom);
    ui_->comNumber->setText(target_->ptz_command_->my_serial_port->port_num_);
   /**********************跟踪控制部分**********************************/
   connect(this->ui_->startTracking,&QPushButton::clicked,target_,&TargetTracking::tracking);


/***********************信息显示部分****************************/
connect(&this->target_->ptz_command_->my_serial_port->information_,&InformationFeedback::GetInfomation,ui_->infoDisplay,&QTextEdit::append);
}

MainWindow::~MainWindow()
{
    delete ui_;
}
void MainWindow::StartTracking()
{
    target_->tracking();
}
