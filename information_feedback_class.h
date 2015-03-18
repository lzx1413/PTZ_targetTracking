#ifndef INFO_H
#define INFO_H
#include<QString>
#include<QDateTime>
/****************************************************/
//用于存储程序内反馈信息并与桌面相关显示控件相结合的类
/****************************************************/
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
    QDateTime time_;  //用于在信息前面加入时间信息
  //  DISALLOW_COPY_AND_ASSIGN(InformationFeedback);




};

#endif // INFO_H
