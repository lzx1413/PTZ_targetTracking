#include <QtDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "my_serialport_class.h"

MySerialPort::MySerialPort()
{
    com_stopped_ = false;

}
MySerialPort::~MySerialPort()
{
    quit();
    wait();
}
void MySerialPort::run()
{
    QSerialPort *my_serialport = new QSerialPort;

    while (!com_stopped_)
    {
        try{
        if (com_stopped_&&com_opened_)
        {
            my_serialport->close();
            com_opened_ = false;

        }
        if (!com_opened_)
        {
            try{
                qDebug() << "Brush:" << "---open com port------";
                com_opened_ = true;
                my_serialport->setPortName(port_num_);
                my_serialport->open(QIODevice::ReadWrite);
                my_serialport->setBaudRate(9600);
                my_serialport->setDataBits(QSerialPort::Data8);
                my_serialport->setParity(QSerialPort::NoParity);
                my_serialport->setStopBits(QSerialPort::OneStop);
                my_serialport->setFlowControl(QSerialPort::NoFlowControl);
                com_opened_ = true;
            }
            catch (...)
            {
                qDebug() << "comm error" << endl;
            }
        }

        /*在串口打开而且发送数据更新存在的情况下进行数据发送操作*/
        if (this->com_opened_&&this->tx_event_)
        {

            this->tx_event_ = false;
            my_serialport->clear(QSerialPort::AllDirections);//清理通道
            qDebug() << "Brush:" << "send data to "<<this->port_num_ << this->tx_data_.length();
            information_.feedback_information_.clear();
            information_.feedback_information_.append("send data to "+this->port_num_+"\n");
            information_.InfoChanged();

            qDebug() << "arr size:" << this->tx_data_.length();

            my_serialport->write(this->tx_data_);//发送数据
            tx_data_.clear();
            if (my_serialport->waitForBytesWritten(50))
            {
                qDebug() << "Brush:" << "send data success";
                if (my_serialport->waitForReadyRead(1000))
                {
                    qDebug()<<"have received data";

                    information_.InfoDisplay("have received data\n");

                    rx_event_ = true;
                    request_data_ = my_serialport->readAll();//获得回复数据
                    emit(this->ComRecive());//发出收到回复的信号
                    qDebug()<<get_request_data_().toHex().data()<<get_request_data_().size()<<endl;
                }

                else
                {
                    qDebug() << "Brush:" << "wait return time out";
                   information_.feedback_information_.clear();
                   information_.feedback_information_.append("com wait return time out\n");
                   information_.InfoChanged();
                }
                   request_data_.clear();
            }
            else
            {
                qDebug() << "Brush:" << "send time out";
                information_.feedback_information_.clear();
                information_.feedback_information_.append("send time out\n");
                information_.InfoChanged();
            }
        }

        /*没有发送数据而收到数据时的操作*/

        if (my_serialport->waitForReadyRead(50))  //50m
        {

            while (my_serialport->waitForReadyRead(5))
                this->msleep(20);
            request_data_ = my_serialport->readAll();

        }
        if (com_stopped_&&com_opened_)
        {
            my_serialport->close();
            com_opened_ = false;
        }
    }
        catch(...)
        {}
    }
}

void MySerialPort::StopCom()
{
    mutex.lock();
    com_stopped_ = true;
    information_.feedback_information_.clear();
    information_.feedback_information_.append("Stop the PTZ");
    information_.InfoChanged();
    mutex.unlock();

}
void MySerialPort::StartCom()
{
    mutex.lock();
    com_stopped_ = false;
    mutex.unlock();
}
void MySerialPort::ChangeComState(bool stat)
{
    mutex.lock();
    com_opened_ = stat;
    mutex.unlock();
}
void MySerialPort::SetMessage(const QString &message)
{
    mutex.lock();
    message_str_ = message;
    mutex.unlock();

}
void MySerialPort::SetPortnum(const QString &num)
{
    mutex.lock();
    port_num_ = num;
    mutex.unlock();

}
void MySerialPort::ChangeTxState(bool stat)
{
    mutex.lock();
    tx_event_ = stat;
    mutex.unlock();
}
void MySerialPort::ChangeRxState(bool stat)
{
    mutex.lock();
    rx_event_ = stat;
    mutex.unlock();
}
void MySerialPort::set_tx_data_(QByteArray a)
{
    mutex.lock();
    tx_data_ = a;
    mutex.unlock();
}

QByteArray MySerialPort::get_request_data_()
{
  return request_data_;

}
