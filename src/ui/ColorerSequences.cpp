#include "ColorerSequences.h"
#include <vector>
#include <iostream>

ColorerSequences::ColorerSequences(QTextDocument *parent): QSyntaxHighlighter(parent)
{

}

void ColorerSequences::highlightBlock(const QString &text)
{
    //number of words to be highlighted
    int nbMotEnValeur=25;

    //initialise the vectors
    //tabPattern : vector of the patterns
    //tabClassFormat : vector of the fonts (bold and color here)
    std::vector<QTextCharFormat> tabClassFormat(nbMotEnValeur);
    std::vector<QString> tabPattern(nbMotEnValeur);
    std::vector<QRegExp> tabExpression(nbMotEnValeur);
    std::vector<int> tabIndex(nbMotEnValeur);

    //define the patterns
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

    //QBrush ponctuation(QColor("#d7d3db"));
    QBrush ponctuation(QColor("#7f7f7f"));
    //QBrush comment(QColor("#d7d3db"));
    QBrush comment(QColor("#949494"));
    //QBrush stoach(QColor("#ffff54"));
    QBrush stoach(QColor("#e7a516"));
    //QBrush instruction(Qt::red);
    QBrush instruction("#ff3237");

    //define the colors for each pattern
    tabClassFormat[0].setForeground(ponctuation);
    tabClassFormat[1].setForeground(ponctuation);
    tabClassFormat[2].setForeground(ponctuation);
    tabClassFormat[3].setForeground(ponctuation);
    tabClassFormat[4].setForeground(stoach);
    tabClassFormat[5].setForeground(ponctuation);
    tabClassFormat[6].setForeground(ponctuation);
    tabClassFormat[7].setForeground(ponctuation);
    tabClassFormat[8].setForeground(ponctuation);
    tabClassFormat[9].setForeground(ponctuation);
    tabClassFormat[10].setForeground(ponctuation);
    tabClassFormat[11].setForeground(instruction);
    tabClassFormat[12].setForeground(instruction);
    tabClassFormat[13].setForeground(instruction);
    tabClassFormat[14].setForeground(ponctuation);
    tabClassFormat[15].setForeground(instruction);
    tabClassFormat[16].setForeground(instruction);
    tabClassFormat[17].setForeground(instruction);
    tabClassFormat[18].setForeground(instruction);
    tabClassFormat[19].setForeground(instruction);
    tabClassFormat[20].setForeground(instruction);
    tabClassFormat[21].setForeground(instruction);
    tabClassFormat[22].setForeground(instruction);
    tabClassFormat[23].setForeground(instruction);
    tabClassFormat[24].setForeground(comment);

    //match color to pattern
    for (int i=0 ; i<nbMotEnValeur ; i++)
    {
        tabClassFormat[i].setFontItalic(true);

        if(i != 24){

            tabClassFormat[i].setFontWeight(QFont::Bold);
            tabClassFormat[i].setFontItalic(false);
        }

        tabExpression[i].setPattern(tabPattern[i]);
        tabIndex[i]=text.indexOf(tabExpression[i]);
        while (tabIndex[i] >= 0) {
            int length = tabExpression[i].matchedLength();
            setFormat(tabIndex[i], length, tabClassFormat[i]);
            tabIndex[i] = text.indexOf(tabExpression[i], tabIndex[i] + length);
       }
    }
}

ColorerSequences::~ColorerSequences()
{

}

