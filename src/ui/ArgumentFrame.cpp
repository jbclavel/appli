#include "ArgumentFrame.h"

//constructor and destructor
ArgumentFrame::ArgumentFrame(){
}
ArgumentFrame::~ArgumentFrame(){
}

//getter and setter
    //argNumber
QString ArgumentFrame::getArgNumber(){
    return argNumber;
}
void ArgumentFrame::setArgNumber(QString newArgNumber){
    argNumber = newArgNumber;
}

    //argSuf
QString ArgumentFrame::getArgSuf(){
    return argSuf;
}
void ArgumentFrame::setArgSuf(QString newArgSuf){
    argSuf = newArgSuf;
}

    //argType
QString ArgumentFrame::getArgType(){
    return argType;
}
void ArgumentFrame::setArgType(QString newArgType){
    argType = newArgType;
}

    //argFac
QString ArgumentFrame::getArgFac(){
    return argFac;
}
void ArgumentFrame::setArgFac(QString newArgFac){
    argFac = newArgFac;
}

    //argOutLine
QString ArgumentFrame::getArgOutline(){
    return argOutline;
}
void ArgumentFrame::setArgOutline(QString newArgOutline){
    argOutline = newArgOutline;
}





