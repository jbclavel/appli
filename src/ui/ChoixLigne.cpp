#include "ChoixLigne.h"


ChoixLigne::ChoixLigne(){
}
ChoixLigne::~ChoixLigne(){
}


QString ChoixLigne::getChoixNom(){
    return choixNom;
}

void ChoixLigne::setChoixNom(QString newChoixNom){
    choixNom = newChoixNom;
}

QString ChoixLigne::getChoixParam(){
    return choixParam;
}

void ChoixLigne::setChoixParam(QString newChoixParam){
    choixParam = newChoixParam;
}

QString ChoixLigne::getChoixPrefix(){
    return choixPrefix;
}

void ChoixLigne::setChoixPrefix(QString newChoixPrefix){
    choixPrefix = newChoixPrefix;
}




