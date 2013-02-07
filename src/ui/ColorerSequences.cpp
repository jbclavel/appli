#include "ColorerSequences.h"
#include <vector>
#include <iostream>

ColorerSequences::ColorerSequences(QTextDocument *parent): QSyntaxHighlighter(parent)
{

}

void ColorerSequences::highlightBlock(const QString &text)
{
    int nbMotEnValeur=6;

    std::vector<QTextCharFormat> tabClassFormat(nbMotEnValeur);
    std::vector<QString> tabPattern(nbMotEnValeur);
    std::vector<QRegExp> tabExpression(nbMotEnValeur);
    std::vector<int> tabIndex(nbMotEnValeur);

    tabPattern[0]= "process";
    tabPattern[1]= "->";
    tabPattern[2]= "directive";
    tabPattern[3]= "initial_state";
    tabPattern[4]= "@";
    tabPattern[5]= "~";

    tabClassFormat[0].setForeground(Qt::darkMagenta);
    tabClassFormat[1].setForeground(Qt::green);
    tabClassFormat[2].setForeground(Qt::red);
    tabClassFormat[3].setForeground(Qt::blue);
    tabClassFormat[4].setForeground(Qt::yellow);
    tabClassFormat[5].setForeground(Qt::cyan);

    for (int i=0 ; i<nbMotEnValeur ; i++)
    {
       tabClassFormat[i].setFontWeight(QFont::Bold);
       tabExpression[i].setPattern(tabPattern[i]);
       tabIndex[i]=text.indexOf(tabExpression[i]);
       while (tabIndex[i] >= 0) {
           int length = tabExpression[i].matchedLength();
           setFormat(tabIndex[i], length, tabClassFormat[i]);
           tabIndex[i] = text.indexOf(tabExpression[i], tabIndex[i] + length);
       }
    }

  /*
    int index = text.indexOf(tabExpression[0]);
    while (index >= 0) {
        int length = tabExpression[0].matchedLength();
        setFormat(index, length, tabClassFormat[0]);
        index = text.indexOf(tabExpression[0], index + length);
    }

   int index2 = text.indexOf(tabExpression[1]);
    while (index2 >= 0) {
        int length = tabExpression[1].matchedLength();
        setFormat(index2, length, tabClassFormat[1]);
        index2 = text.indexOf(tabExpression[1], index2 + length);
    }
*/
//a garder pour Jb (cplmt info)
/*
    for(int i = 0; i<text.size(); i++)
    {
        if(text.at(i) == QChar('p'))
        {
            setFormat(i, 1, Qt::green);
        }
        else if(text.at(i) == QChar('C'))
        {
            setFormat(i, 1, Qt::blue);
        }
        else if(text.at(i) == QChar('T'))
        {
            setFormat(i, 1, Qt::red);
        }
    }
*/
}

ColorerSequences::~ColorerSequences()
{

};

