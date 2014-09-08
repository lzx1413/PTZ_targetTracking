#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QColor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ptzComm = new PTZComm;
    target = new targetTracking;
    target->ptzComm->CommInit();
    target-> ptzComm->PTZ_Init();
    ui->infoDisplay->setTextColor(QColor(255,255,255));
    ui->infoDisplay->setTextBackgroundColor(QColor(0,0,0));
    QLabel *permanent  = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
    permanent->setText("lzx1444@gmail.com");
    ui->statusBar->addPermanentWidget(permanent);
    /****************窗口美化部分***************************/
    //setWindowFlags(windowFlags() | Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint);
    /****************窗口背景********************************/
    QPixmap pixmap = QPixmap("D:/bg3.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
    /**********PT相关控制部分******************************/
    connect(this->ui->PTZ_home,&QPushButton::clicked,target->ptzComm,&PTZComm::Home);
    connect(this->ui->PTZ_left,&QPushButton::clicked,target->ptzComm,&PTZComm::Left);
    connect(this->ui->PTZ_right,&QPushButton::clicked,target->ptzComm,&PTZComm::Right);
    connect(this->ui->PTZ_up,&QPushButton::clicked,target->ptzComm,&PTZComm::Up);
    connect(this->ui->PTZ_down,&QPushButton::clicked,target->ptzComm,&PTZComm::Down);
    connect(this->ui->stop,&QPushButton::clicked,target->ptzComm,&PTZComm::Stop);

    ui->ZoomChange->setMinimum(0);
    ui->ZoomChange->setMaximum(128);
    ui->ZoomChange->setValue(0);
    ui->ZoomNumber->setMaximum(128);
    connect(this->ui->ZoomChange,&QSlider::valueChanged,target->ptzComm,&PTZComm::ZoomSet);
    connect(this->ui->ZoomChange,&QSlider::valueChanged,this->ui->ZoomNumber,&QSpinBox::setValue);
    connect(this->ui->comOpen,&QPushButton::clicked,target->ptzComm->comm,&MyThread::startCom);
    connect(this->ui->comClose,&QPushButton::clicked,target->ptzComm->comm,&MyThread::stop);
    ui->comNumber->setText(target->ptzComm->comm->portnum);
   /**********************跟踪控制部分**********************************/
   connect(this->ui->startTracking,&QPushButton::clicked,target,&targetTracking::tracking);


/***********************信息显示部分****************************/
connect(&this->target->ptzComm->comm->information,&info::getInfo,ui->infoDisplay,&QTextEdit::append);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::startTracking()
{
    target->tracking();
}
