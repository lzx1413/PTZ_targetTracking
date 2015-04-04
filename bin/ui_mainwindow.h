/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_3;
    QGroupBox *horizontalGroupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *info;
    QTextEdit *infoDisplay;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *startTracking;
    QPushButton *stop_tracking_;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QSlider *PanSpeed;
    QSlider *TiltSpeed;
    QPushButton *PTZ_right;
    QPushButton *stop;
    QSlider *ZoomChange;
    QPushButton *PTZ_up;
    QPushButton *PTZ_left;
    QPushButton *PTZ_home;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLineEdit *comNumber;
    QPushButton *comClose;
    QPushButton *comOpen;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QSpinBox *ZoomNumber;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *PTZ_down;
    QGroupBox *model_train;
    QLabel *video;
    QPushButton *startvideo;
    QPushButton *closevideo;
    QPushButton *training;
    QLabel *photo1;
    QLabel *name1;
    QPushButton *flag_of_training;
    QSpinBox *template_num_;
    QLabel *label_9;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(1247, 796);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setFocusPolicy(Qt::StrongFocus);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setToolButtonStyle(Qt::ToolButtonFollowStyle);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setFocusPolicy(Qt::StrongFocus);
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(-1, 9, 431, 671));
        gridLayout_3 = new QGridLayout(gridLayoutWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalGroupBox_3 = new QGroupBox(gridLayoutWidget);
        horizontalGroupBox_3->setObjectName(QStringLiteral("horizontalGroupBox_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(horizontalGroupBox_3->sizePolicy().hasHeightForWidth());
        horizontalGroupBox_3->setSizePolicy(sizePolicy1);
        horizontalLayout_3 = new QHBoxLayout(horizontalGroupBox_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_3->setContentsMargins(-1, -1, 1, -1);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        info = new QLabel(horizontalGroupBox_3);
        info->setObjectName(QStringLiteral("info"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        info->setFont(font);

        verticalLayout_2->addWidget(info);

        infoDisplay = new QTextEdit(horizontalGroupBox_3);
        infoDisplay->setObjectName(QStringLiteral("infoDisplay"));
        infoDisplay->setEnabled(true);
        infoDisplay->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(infoDisplay);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        startTracking = new QPushButton(horizontalGroupBox_3);
        startTracking->setObjectName(QStringLiteral("startTracking"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(startTracking->sizePolicy().hasHeightForWidth());
        startTracking->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(startTracking);

        stop_tracking_ = new QPushButton(horizontalGroupBox_3);
        stop_tracking_->setObjectName(QStringLiteral("stop_tracking_"));
        sizePolicy2.setHeightForWidth(stop_tracking_->sizePolicy().hasHeightForWidth());
        stop_tracking_->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(stop_tracking_);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_2);


        gridLayout_3->addWidget(horizontalGroupBox_3, 0, 0, 1, 1);

        groupBox = new QGroupBox(gridLayoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 417, 317));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(3);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        PanSpeed = new QSlider(layoutWidget);
        PanSpeed->setObjectName(QStringLiteral("PanSpeed"));
        PanSpeed->setOrientation(Qt::Vertical);

        gridLayout->addWidget(PanSpeed, 3, 6, 5, 1);

        TiltSpeed = new QSlider(layoutWidget);
        TiltSpeed->setObjectName(QStringLiteral("TiltSpeed"));
        TiltSpeed->setOrientation(Qt::Vertical);

        gridLayout->addWidget(TiltSpeed, 3, 7, 5, 1);

        PTZ_right = new QPushButton(layoutWidget);
        PTZ_right->setObjectName(QStringLiteral("PTZ_right"));

        gridLayout->addWidget(PTZ_right, 4, 2, 1, 1);

        stop = new QPushButton(layoutWidget);
        stop->setObjectName(QStringLiteral("stop"));

        gridLayout->addWidget(stop, 7, 1, 1, 1);

        ZoomChange = new QSlider(layoutWidget);
        ZoomChange->setObjectName(QStringLiteral("ZoomChange"));
        ZoomChange->setTracking(false);
        ZoomChange->setOrientation(Qt::Vertical);

        gridLayout->addWidget(ZoomChange, 3, 4, 5, 1);

        PTZ_up = new QPushButton(layoutWidget);
        PTZ_up->setObjectName(QStringLiteral("PTZ_up"));

        gridLayout->addWidget(PTZ_up, 3, 1, 1, 1);

        PTZ_left = new QPushButton(layoutWidget);
        PTZ_left->setObjectName(QStringLiteral("PTZ_left"));

        gridLayout->addWidget(PTZ_left, 4, 0, 1, 1);

        PTZ_home = new QPushButton(layoutWidget);
        PTZ_home->setObjectName(QStringLiteral("PTZ_home"));

        gridLayout->addWidget(PTZ_home, 4, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        comNumber = new QLineEdit(layoutWidget);
        comNumber->setObjectName(QStringLiteral("comNumber"));
        comNumber->setReadOnly(true);
        comNumber->setClearButtonEnabled(true);

        horizontalLayout->addWidget(comNumber);


        verticalLayout->addLayout(horizontalLayout);

        comClose = new QPushButton(layoutWidget);
        comClose->setObjectName(QStringLiteral("comClose"));

        verticalLayout->addWidget(comClose);

        comOpen = new QPushButton(layoutWidget);
        comOpen->setObjectName(QStringLiteral("comOpen"));
        comOpen->setFocusPolicy(Qt::StrongFocus);

        verticalLayout->addWidget(comOpen);


        gridLayout->addLayout(verticalLayout, 9, 0, 1, 3);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 8, 4, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setWeight(50);
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 1, 1, 2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 4, 1, 1);

        ZoomNumber = new QSpinBox(layoutWidget);
        ZoomNumber->setObjectName(QStringLiteral("ZoomNumber"));
        sizePolicy2.setHeightForWidth(ZoomNumber->sizePolicy().hasHeightForWidth());
        ZoomNumber->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(ZoomNumber, 5, 5, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 8, 6, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 1, 6, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 8, 7, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 1, 7, 1, 1);

        PTZ_down = new QPushButton(layoutWidget);
        PTZ_down->setObjectName(QStringLiteral("PTZ_down"));

        gridLayout->addWidget(PTZ_down, 5, 1, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 1);

        model_train = new QGroupBox(centralWidget);
        model_train->setObjectName(QStringLiteral("model_train"));
        model_train->setGeometry(QRect(440, 10, 811, 671));
        model_train->setFlat(false);
        video = new QLabel(model_train);
        video->setObjectName(QStringLiteral("video"));
        video->setGeometry(QRect(10, 20, 640, 480));
        video->setPixmap(QPixmap(QString::fromUtf8(":/picture/2.jpg")));
        video->setScaledContents(true);
        startvideo = new QPushButton(model_train);
        startvideo->setObjectName(QStringLiteral("startvideo"));
        startvideo->setGeometry(QRect(10, 520, 101, 28));
        closevideo = new QPushButton(model_train);
        closevideo->setObjectName(QStringLiteral("closevideo"));
        closevideo->setGeometry(QRect(150, 520, 101, 28));
        training = new QPushButton(model_train);
        training->setObjectName(QStringLiteral("training"));
        training->setGeometry(QRect(480, 520, 111, 28));
        photo1 = new QLabel(model_train);
        photo1->setObjectName(QStringLiteral("photo1"));
        photo1->setGeometry(QRect(10, 550, 101, 91));
        name1 = new QLabel(model_train);
        name1->setObjectName(QStringLiteral("name1"));
        name1->setGeometry(QRect(120, 620, 72, 15));
        flag_of_training = new QPushButton(model_train);
        flag_of_training->setObjectName(QStringLiteral("flag_of_training"));
        flag_of_training->setGeometry(QRect(310, 520, 93, 28));
        template_num_ = new QSpinBox(model_train);
        template_num_->setObjectName(QStringLiteral("template_num_"));
        template_num_->setGeometry(QRect(660, 70, 71, 22));
        label_9 = new QLabel(model_train);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(660, 30, 141, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1247, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        horizontalGroupBox_3->setTitle(QString());
        info->setText(QApplication::translate("MainWindow", "information", 0));
        startTracking->setText(QApplication::translate("MainWindow", "RUN", 0));
        stop_tracking_->setText(QApplication::translate("MainWindow", "EXIT", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "control", 0));
        PTZ_right->setText(QApplication::translate("MainWindow", "RI", 0));
        stop->setText(QApplication::translate("MainWindow", "stop", 0));
        PTZ_up->setText(QApplication::translate("MainWindow", "UP", 0));
        PTZ_left->setText(QApplication::translate("MainWindow", "LE", 0));
        PTZ_home->setText(QApplication::translate("MainWindow", "HO", 0));
        label_4->setText(QApplication::translate("MainWindow", "serialport", 0));
        comNumber->setText(QString());
        comClose->setText(QApplication::translate("MainWindow", "open port", 0));
        comOpen->setText(QApplication::translate("MainWindow", "close port ", 0));
        label_2->setText(QApplication::translate("MainWindow", "0", 0));
        label->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "128", 0));
        label_5->setText(QApplication::translate("MainWindow", "8", 0));
        label_6->setText(QApplication::translate("MainWindow", "800", 0));
        label_7->setText(QApplication::translate("MainWindow", "8", 0));
        label_8->setText(QApplication::translate("MainWindow", "622", 0));
        PTZ_down->setText(QApplication::translate("MainWindow", "DW", 0));
        model_train->setTitle(QApplication::translate("MainWindow", "video", 0));
        video->setText(QString());
        startvideo->setText(QApplication::translate("MainWindow", "start video", 0));
        closevideo->setText(QApplication::translate("MainWindow", "close video", 0));
        training->setText(QApplication::translate("MainWindow", "train", 0));
        photo1->setText(QString());
        name1->setText(QString());
        flag_of_training->setText(QApplication::translate("MainWindow", "train flag", 0));
        label_9->setText(QApplication::translate("MainWindow", "template number", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
