#include "info.h"

info::info()
{
}
void info::infoChange()
{
    time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy:MM:dd:hh:mm:ss");
    emit getInfo(str+infor);
}
void info::infoDisplay(QString temp)
{
    infor.clear();
    infor.append(temp);
    infoChange();
}
