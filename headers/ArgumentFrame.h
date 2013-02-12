#ifndef ARGUMENTFRAME_H
#define ARGUMENTFRAME_H

#include <QtGui>

class ArgumentFrame
{
public:
    ArgumentFrame();
    QString getArgSuf();
    void setArgSuf(QString newArgSuf);
    QString getArgType();
    void setArgType(QString newArgType);
    bool getArgFac();
    void setArgFac(bool newArgFac);


private :
    QString argSuf;
    QString argType;
    bool argFac;
};

#endif
