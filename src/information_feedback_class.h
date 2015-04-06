#ifndef INFO_H
#define INFO_H
#include<QString>
#include<QDateTime>
#include<QObject>
class InformationFeedback:public QObject
{
    Q_OBJECT
public:
    InformationFeedback();
    QString feedback_information_;  //存储反馈信息
    void InfoChanged();  //发出信息改变的信号
    void InfoDisplay(QString temp);    //改写信息发出信号
signals:
    void  GetInfomation(QString t_infor);  //信息改变的信号

private:
    QDateTime time_;





};

#endif // INFO_H
