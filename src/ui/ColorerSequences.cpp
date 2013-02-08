#include "ColorerSequences.h"
#include <vector>
#include <iostream>

ColorerSequences::ColorerSequences(QTextDocument *parent): QSyntaxHighlighter(parent)
{

}

void ColorerSequences::highlightBlock(const QString &text)
{
    int nbMotEnValeur=26;

    std::vector<QTextCharFormat> tabClassFormat(nbMotEnValeur);
    std::vector<QString> tabPattern(nbMotEnValeur);
    std::vector<QRegExp> tabExpression(nbMotEnValeur);
    std::vector<int> tabIndex(nbMotEnValeur);

    tabPattern[0]= "\\}";
    tabPattern[1]= "\\{";
    tabPattern[2]= ",";
    tabPattern[3]= "-";
    tabPattern[4]= "@";
    tabPattern[5]= "~";
    tabPattern[6]= "\\+";
    tabPattern[7]= "\\(";
    tabPattern[8]= "\\)";
    tabPattern[9]= "\\[";
    tabPattern[10]= "\\]";
    tabPattern[11]= ";";
    tabPattern[12]= "in ";
    tabPattern[13]= "and ";
    tabPattern[14]= "not ";
    tabPattern[15]= "->";
    tabPattern[16]= "RM";
    tabPattern[17]= "GRN";
    tabPattern[18]= "initial_state";
    tabPattern[19]= "directive";
    tabPattern[20]= "COOPERATIVITY";
    tabPattern[21]= "process";
    tabPattern[22]= "KNOCKDOWN";
    tabPattern[23]= "default_rate";
    tabPattern[24]= "stochasticity_absorption";
    tabPattern[25]= "\\(\\*.*\\*\\)";

    tabClassFormat[0].setForeground(Qt::darkMagenta);
    tabClassFormat[1].setForeground(Qt::green);
    tabClassFormat[2].setForeground(Qt::red);
    tabClassFormat[3].setForeground(Qt::blue);
    tabClassFormat[4].setForeground(Qt::yellow);
    tabClassFormat[5].setForeground(Qt::cyan);
    tabClassFormat[6].setForeground(Qt::cyan);
    tabClassFormat[7].setForeground(Qt::cyan);
    tabClassFormat[8].setForeground(Qt::cyan);
    tabClassFormat[9].setForeground(Qt::cyan);
    tabClassFormat[10].setForeground(Qt::cyan);
    tabClassFormat[11].setForeground(Qt::cyan);
    tabClassFormat[12].setForeground(Qt::cyan);
    tabClassFormat[13].setForeground(Qt::cyan);
    tabClassFormat[14].setForeground(Qt::cyan);
    tabClassFormat[15].setForeground(Qt::cyan);
    tabClassFormat[16].setForeground(Qt::cyan);
    tabClassFormat[17].setForeground(Qt::cyan);
    tabClassFormat[18].setForeground(Qt::cyan);
    tabClassFormat[19].setForeground(Qt::cyan);
    tabClassFormat[20].setForeground(Qt::cyan);
    tabClassFormat[21].setForeground(Qt::cyan);
    tabClassFormat[22].setForeground(Qt::cyan);
    tabClassFormat[23].setForeground(Qt::cyan);
    tabClassFormat[24].setForeground(Qt::cyan);
    tabClassFormat[25].setForeground(Qt::cyan);

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

