#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <stdio.h>
#include <QtGlobal>
#include"info.h"
/*********************************/
/***********串口类*****************/
//通过继承QThread类来实现在单独线程运行串口的操作
//重写run函数实现
class MyThread : public QThread
{
	Q_OBJECT
public:
    MyThread();
    ~MyThread();
    QByteArray requestData;//收到的回复数据
    QByteArray TxData;//发送数据
    volatile bool rx_event;
    QString portnum;
    info information;
	void setMessage(const QString &message);
	void setPortnum(const QString &num);
	void stop();
	void startCom();
	void changeTxState(bool stat);
	void changeRxState(bool stat);
	void changeComState(bool stat);

signals:
	void request(const QString &s);
	void comRecive();



protected:
	void run();

private:
	QString messageStr;

	volatile bool com_opened;
	volatile bool stopped;
	volatile bool tx_event;

};

#endif // MYTHREAD_H
