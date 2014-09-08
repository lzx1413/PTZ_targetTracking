#ifndef INFO_H
#define INFO_H
#include<QString>
#include<QDateTime>
class info:public QObject
{
    Q_OBJECT
public:
    info();
    QString infor;
    void infoChange();//信息改变时发出信号
    void infoDisplay(QString temp);
signals:
    void  getInfo(QString t_infor);

private:
    QDateTime time;




};

#endif // INFO_H
