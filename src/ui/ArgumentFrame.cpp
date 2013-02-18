#include "ArgumentFrame.h"


ArgumentFrame::ArgumentFrame(){
}
ArgumentFrame::~ArgumentFrame(){
}


QString ArgumentFrame::getArgNumber(){
    return argNumber;
}

void ArgumentFrame::setArgNumber(QString newArgNumber){
    argNumber = newArgNumber;
}

QString ArgumentFrame::getArgSuf(){
    return argSuf;
}

void ArgumentFrame::setArgSuf(QString newArgSuf){
    argSuf = newArgSuf;
}

QString ArgumentFrame::getArgType(){
    return argType;
}

void ArgumentFrame::setArgType(QString newArgType){
    argType = newArgType;
}

QString ArgumentFrame::getArgFac(){
    return argFac;
}

void ArgumentFrame::setArgFac(QString newArgFac){
    argFac = newArgFac;
}

QString ArgumentFrame::getArgOutline(){
    return argOutline;
}

void ArgumentFrame::setArgOutline(QString newArgOutline){
    argOutline = newArgOutline;
}





