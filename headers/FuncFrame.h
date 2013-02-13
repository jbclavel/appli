#ifndef FuncFrame_H
#define FuncFrame_H

#include <vector>
#include "ArgumentFrame.h"

class FuncFrame
{

public:
    FuncFrame();
    QString getNameFunction();
    void setNameFunction(QString newNameFunction);

    QString getProgram();
    void setProgram(QString newProgram);

    QString getNbArgument();
    void setNbArgument(QString newNbArgument);

    std::vector<ArgumentFrame*> getArguments();
    void setArguments(std::vector<ArgumentFrame*> newArguments);



private :
    QString nameFunction;
    QString program;
    QString nbArgument;
    std::vector<ArgumentFrame*> arguments;
};
#endif



