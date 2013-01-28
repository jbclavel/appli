#include "TextArea.h"

TextArea::TextArea(QWidget *parent) :
    QTextEdit(parent)
{
 this->setMinimumWidth(200);
 this->setMaximumWidth(200);

    QPalette p = this->palette();
    p.setColor(QPalette::Base, QColor(10, 10, 10));
    this->setPalette(p);
    this->setCurrentFont(QFont("TypeWriter", 10));
    this->setTextColor(QColor("white"));

}

void TextArea::changeBackgroundColor(QColor color){
    // get the current palette of the textArea
    QPalette p = this->palette();
    // set the color chosen to the palette
    p.setColor(QPalette::Base, color);
    // set the palette to the textArea
    this->setPalette(p);
}
