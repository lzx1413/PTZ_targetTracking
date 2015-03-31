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
    bool keypressflag_;
    bool up_pressed;
    bool down_pressed;
    bool right_pressed;
    bool left_pressed;
};

#endif // MAINWINDOW_H
