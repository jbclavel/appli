#include "FuncFrame.h"


FuncFrame::FuncFrame()
    {

}

QString FuncFrame::getNameFunction(){
    return nameFunction;
}

void FuncFrame::setNameFunction(QString newNameFunction){
    nameFunction = newNameFunction;
}

QString FuncFrame::getProgram(){
    return program;
}

void FuncFrame::setProgram(QString newProgram){
    program = newProgram;
}

QString FuncFrame::getNbArgument(){
    return nbArgument;
}

void FuncFrame::setNbArgument(QString newNbArgument){
    nbArgument = newNbArgument;
}

std::vector<ArgumentFrame*> FuncFrame::getArguments(){
    return arguments;
}

void FuncFrame::setArguments(std::vector<ArgumentFrame*> newArguments){
    arguments = newArguments;
}
