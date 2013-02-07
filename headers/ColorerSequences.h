#ifndef DEF_COLORERSEQUENCES
#define DEF_COLORERSEQUENCES

#include <QtGui>

class ColorerSequences: public QSyntaxHighlighter
{
    Q_OBJECT

public:
    ColorerSequences(QTextDocument *parent = 0);
    ~ColorerSequences();

public slots:
    void highlightBlock(const QString &text);

private:


};
#endif
