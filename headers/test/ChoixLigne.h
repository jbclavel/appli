#ifndef CHOIXLIGNE_H
#define CHOIXLIGNE_H

#include <QtGui>

class ChoixLigne
{
public:
    ChoixLigne();
    ~ChoixLigne();

    QString getChoixNom();
    void setChoixNom(QString newChoixNom);

    QString getChoixParam();
    void setChoixParam(QString newChoixParam);

private :
    QString choixNom;
    QString choixParam;

};

#endif // CHOIXLIGNE_H
