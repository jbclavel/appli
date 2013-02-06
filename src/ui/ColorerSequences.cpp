#include "ColorerSequences.h"

ColorerSequences::ColorerSequences(QTextDocument *parent): QSyntaxHighlighter(parent)
{

}

void ColorerSequences::highlightBlock(const QString &text)
{
    QTextCharFormat myClassFormat;
    myClassFormat.setFontWeight(QFont::Bold);
    myClassFormat.setForeground(Qt::darkMagenta);

    QTextCharFormat myClassFormat2;
    myClassFormat2.setFontWeight(QFont::Bold);
    myClassFormat2.setForeground(Qt::green);

    QString pattern = "process";
    QString pattern2 = "->";

    QRegExp expression(pattern);
    QRegExp expression2(pattern2);

    int index = text.indexOf(expression);
    while (index >= 0) {
        int length = expression.matchedLength();
        setFormat(index, length, myClassFormat);
        index = text.indexOf(expression, index + length);
    }

    int index2 = text.indexOf(expression2);
    while (index2 >= 0) {
        int length = expression2.matchedLength();
        setFormat(index2, length, myClassFormat2);
        index2 = text.indexOf(expression2, index2 + length);
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

