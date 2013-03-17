#include "ChoixLigne.h"

//constructor and destructor
ChoixLigne::ChoixLigne(){
}
ChoixLigne::~ChoixLigne(){
}

//getteur and setteur
    //choixnom
QString ChoixLigne::getChoixNom(){
    return choixNom;
}
void ChoixLigne::setChoixNom(QString newChoixNom){
    choixNom = newChoixNom;
}

    //choixParam
QString ChoixLigne::getChoixParam(){
    return choixParam;
}
void ChoixLigne::setChoixParam(QString newChoixParam){
    choixParam = newChoixParam;
}

    //choixPrefix
QString ChoixLigne::getChoixPrefix(){
    return choixPrefix;
}
void ChoixLigne::setChoixPrefix(QString newChoixPrefix){
    choixPrefix = newChoixPrefix;
}




