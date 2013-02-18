#ifndef FuncFrame_H
#define FuncFrame_H

#include <vector>
#include "ArgumentFrame.h"

class FuncFrame
{

public:
    FuncFrame();
    ~FuncFrame();

    QString getNameFunction();
    void setNameFunction(QString newNameFunction);

    QString getProgram();
    void setProgram(QString newProgram);

    QString getNbArgument();
    void setNbArgument(QString newNbArgument);

private :
    QString nameFunction;
    QString program;
    QString nbArgument;
};
#endif



