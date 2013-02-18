#ifndef ARGUMENTFRAME_H
#define ARGUMENTFRAME_H

#include <QtGui>

class ArgumentFrame
{
public:
    ArgumentFrame();
    ~ArgumentFrame();

    QString getArgNumber();
    void setArgNumber(QString newArgNumber);

    QString getArgSuf();
    void setArgSuf(QString newArgSuf);

    QString getArgType();
    void setArgType(QString newArgType);

    QString getArgFac();
    void setArgFac(QString newArgFac);

    QString getArgOutline();
    void setArgOutline(QString newArgOutline);


private :
    QString argNumber;
    QString argSuf;
    QString argType;
    QString argFac;
    QString argOutline;

};

#endif
