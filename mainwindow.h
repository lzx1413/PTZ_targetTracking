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
    void startTracking();
    targetTracking *target;

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
