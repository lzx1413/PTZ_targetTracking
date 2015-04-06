#include "information_feedback_class.h"

InformationFeedback::InformationFeedback()
{
}
void InformationFeedback::InfoChanged()
{
    time_ = QDateTime::currentDateTime();
    QString str = time_.toString("yyyy:MM:dd:hh:mm:ss");
    emit GetInfomation(str+feedback_information_);
}
void InformationFeedback::InfoDisplay(QString temp)
{
    feedback_information_.clear();
    feedback_information_.append(temp);
    InfoChanged();
}
