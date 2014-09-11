#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <stdio.h>
#include <QtGlobal>
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
    QByteArray request_data_;  //串口回复的数据
    QByteArray tx_data_;  //向串口发送的数据
    volatile bool rx_event_;  //串口回复状态
    QString port_num_;  //串口名称
    InformationFeedback information_; //反馈信息
    void SetMessage(const QString &message);
    void SetPortnum(const QString &num);  //设置串口名称
    void StopCom();  //暂停串口
    void StartCom();  //打开串口
    void ChangeTxState(bool stat);  //改变发送状态
    void ChangeRxState(bool stat);  //改变回复状态
    void ChangeComState(bool stat);  //改变串口状态

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

};

#endif // MYTHREAD_H
