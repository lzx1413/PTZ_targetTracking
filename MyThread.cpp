#include "mythread.h"
#include <QtDebug>
//FOR RS232
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

MyThread::MyThread()
{
	stopped = false;

}
MyThread::~MyThread()
{
    quit();
    wait();
}
void MyThread::run()
{
	QSerialPort *my_serialport = new QSerialPort;

	while (!stopped)
	{
		if (stopped&&com_opened)
		{
			my_serialport->close();
			com_opened = false;

		}
		if (!com_opened)
		{
			try{
				//open com
				qDebug() << "Brush:" << "---open com port------";
				com_opened = true;
				my_serialport->setPortName(portnum);
				my_serialport->open(QIODevice::ReadWrite);
				my_serialport->setBaudRate(9600);
				my_serialport->setDataBits(QSerialPort::Data8);
				my_serialport->setParity(QSerialPort::NoParity);
				my_serialport->setStopBits(QSerialPort::OneStop);
				my_serialport->setFlowControl(QSerialPort::NoFlowControl);
				com_opened = true;
			}
			catch (...)
			{
                qDebug() << "comm error" << endl;
			}
		}

		/*在串口打开而且发送数据更新存在的情况下进行数据发送操作*/
		if (this->com_opened&&this->tx_event)
		{
			this->tx_event = false;
			my_serialport->clear(QSerialPort::AllDirections);//清理通道
            qDebug() << "Brush:" << "send data to "<<this->portnum << this->TxData.length();
            information.infor.clear();
            information.infor.append("send data to"+this->portnum+"\n");
            information.infoChange();

			qDebug() << "arr size:" << this->TxData.length();

			my_serialport->write(this->TxData);//发送数据

			if (my_serialport->waitForBytesWritten(5))
			{
				qDebug() << "Brush:" << "send data success";
				if (my_serialport->waitForReadyRead(1500))  //1s
				{
                    qDebug()<<"have received data";

                   information.infoDisplay("have received data\n");

                    rx_event = true;
					requestData = my_serialport->readAll();//获得回复数据
					while (my_serialport->waitForReadyRead(15))
						requestData += my_serialport->readAll();
                    emit(this->comRecive());//发出收到回复的信号
                    qDebug()<<requestData.toHex().data()<<requestData.size()<<endl;
				}

				else
				{
					qDebug() << "Brush:" << "wait return time out";
                   information.infor.clear();
                    information.infor.append("com wait return time out\n");
                    information.infoChange();
				}
			}
			else
			{
				qDebug() << "Brush:" << "send time out";
               information.infor.clear();
                 information.infor.append("com send time out\n");
                 information.infoChange();
			}
		}
		/*没有发送数据而收到数据时的操作*/
		if (my_serialport->waitForReadyRead(5))  //50ms
		{
			while (my_serialport->waitForReadyRead(5))
				this->msleep(20);
			requestData = my_serialport->readAll();
			emit(this->comRecive());
		}
		if (stopped&&com_opened)
		{
			my_serialport->close();
			com_opened = false;
		}
	}
}

void MyThread::stop()
{
	stopped = true;

}
void MyThread::startCom()
{
	stopped = false;

}
void MyThread::changeComState(bool stat)
{
	com_opened = stat;
}
void MyThread::setMessage(const QString &message)
{
	messageStr = message;

}
void MyThread::setPortnum(const QString &num)
{
	portnum = num;

}
void MyThread::changeTxState(bool stat)
{
	tx_event = stat;
}
void MyThread::changeRxState(bool stat)
{
	rx_event = stat;
}
