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

    QString getChoixPrefix();
    void setChoixPrefix(QString newChoixPrefix);

private :
    QString choixNom;
    QString choixParam;
    QString choixPrefix;

};

#endif // CHOIXLIGNE_H
