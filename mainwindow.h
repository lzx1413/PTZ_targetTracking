#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"targetTracking.h"

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


private:
    Ui::MainWindow *ui_;

};

#endif // MAINWINDOW_H
