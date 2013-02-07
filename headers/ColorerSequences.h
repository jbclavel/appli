#ifndef DEF_COLORERSEQUENCES
#define DEF_COLORERSEQUENCES

#include <QtGui>
#include <vector>

class ColorerSequences: public QSyntaxHighlighter
{
    Q_OBJECT

public:
    ColorerSequences(QTextDocument *parent = 0);
    ~ColorerSequences();

    std::vector<QTextCharFormat> tabClassFormat;
    std::vector<QString> tabPattern;
    std::vector<QRegExp> tabExpression;
    std::vector<int> tabIndex;



public slots:
    void highlightBlock(const QString &text);

private:


};
#endif
