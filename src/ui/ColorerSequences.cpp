#include "ColorerSequences.h"
#include <vector>
#include <iostream>

ColorerSequences::ColorerSequences(QTextDocument *parent): QSyntaxHighlighter(parent)
{

}

void ColorerSequences::highlightBlock(const QString &text)
{
    int nbMotEnValeur=25;

    std::vector<QTextCharFormat> tabClassFormat(nbMotEnValeur);
    std::vector<QString> tabPattern(nbMotEnValeur);
    std::vector<QRegExp> tabExpression(nbMotEnValeur);
    std::vector<int> tabIndex(nbMotEnValeur);

    tabPattern[0]= "\\}";
    tabPattern[1]= "\\{";
    tabPattern[2]= ",";
    tabPattern[3]= "-";
    tabPattern[4]= "@.*";
    tabPattern[5]= "\\+";
    tabPattern[6]= "\\(";
    tabPattern[7]= "\\)";
    tabPattern[8]= "\\[";
    tabPattern[9]= "\\]";
    tabPattern[10]= ";";
    tabPattern[11]= "in ";
    tabPattern[12]= "and ";
    tabPattern[13]= "not ";
    tabPattern[14]= "->";
    tabPattern[15]= "RM";
    tabPattern[16]= "GRN";
    tabPattern[17]= "initial_state";
    tabPattern[18]= "directive";
    tabPattern[19]= "COOPERATIVITY";
    tabPattern[20]= "process";
    tabPattern[21]= "KNOCKDOWN";
    tabPattern[22]= "default_rate";
    tabPattern[23]= "stochasticity_absorption";
    tabPattern[24]= "\\(\\*.*\\*\\)";

    tabClassFormat[0].setForeground(Qt::blue);
    tabClassFormat[1].setForeground(Qt::blue);
    tabClassFormat[2].setForeground(Qt::blue);
    tabClassFormat[3].setForeground(Qt::blue);
    tabClassFormat[4].setForeground(Qt::yellow);
    tabClassFormat[5].setForeground(Qt::blue);
    tabClassFormat[6].setForeground(Qt::blue);
    tabClassFormat[7].setForeground(Qt::blue);
    tabClassFormat[8].setForeground(Qt::blue);
    tabClassFormat[9].setForeground(Qt::blue);
    tabClassFormat[10].setForeground(Qt::blue);
    tabClassFormat[11].setForeground(Qt::red);
    tabClassFormat[12].setForeground(Qt::red);
    tabClassFormat[13].setForeground(Qt::red);
    tabClassFormat[14].setForeground(Qt::blue);
    tabClassFormat[15].setForeground(Qt::red);
    tabClassFormat[16].setForeground(Qt::red);
    tabClassFormat[17].setForeground(Qt::red);
    tabClassFormat[18].setForeground(Qt::red);
    tabClassFormat[19].setForeground(Qt::red);
    tabClassFormat[20].setForeground(Qt::red);
    tabClassFormat[21].setForeground(Qt::red);
    tabClassFormat[22].setForeground(Qt::red);
    tabClassFormat[23].setForeground(Qt::red);
    tabClassFormat[24].setForeground(Qt::green);

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

