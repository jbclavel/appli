#include "FuncFrame.h"


FuncFrame::FuncFrame(){
}

FuncFrame::~FuncFrame(){
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

