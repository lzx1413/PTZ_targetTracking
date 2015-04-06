#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"targetTracking.h"
#include<QTimer>
#include<QImage>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void StartTracking();
    TargetTracking *target_;
    void keyPressEvent(QKeyEvent*e);
    void keyReleaseEvent(QKeyEvent*);
    void DisplayMat(Mat frame);
    void  camaraGet();
private slots:
    void OpenCamera();
    void ReadFrame(void);
    void CloseCamera();
    void TakingPictures();
    void ShowFaceName();
private:
    Ui::MainWindow *ui_;
    QTimer *timer_;
    QImage *imag_;
    CvCapture *cam_;
    IplImage  *frame_;
    Mat face_;
    QImage face2show_;
    bool keypressflag_ = false;
    bool up_pressed = false;
    bool down_pressed = false;
    bool right_pressed=false;
    bool left_pressed = false;
    bool space_pressed = false;
};

#endif // MAINWINDOW_H
