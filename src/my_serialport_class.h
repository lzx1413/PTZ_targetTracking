#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <stdio.h>
#include <QtGlobal>
#include<QMutex>
#include"information_feedback_class.h"

/***********串口类*****************/
//通过继承QThread类来实现在单独线程运行串口的操作
//重写run函数实现
class MySerialPort : public QThread
{
	Q_OBJECT
public:
    MySerialPort();
    ~MySerialPort();
    volatile bool rx_event_;  //串口回复状态
    QString port_num_;  //串口名称
    InformationFeedback information_; //反馈信息
    void SetMessage(const QString &message);
    void SetPortnum(const QString &num);
    void StopCom();
    void StartCom();
    void ChangeTxState(bool stat);
    void ChangeRxState(bool stat);
    void ChangeComState(bool stat);
    QByteArray get_request_data_();
    void set_tx_data_(QByteArray a);
    QByteArray request_data_;  //串口回复的数据
    QByteArray tx_data_;  //向串口发送的数据

signals:
	void request(const QString &s);
    void ComRecive();

protected:
    void run();

private:
    QString message_str_ ;
    volatile bool com_opened_;
    volatile bool com_stopped_;
    volatile bool tx_event_;
    QMutex mutex;

};

#endif // MYTHREAD_H
