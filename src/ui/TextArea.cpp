#include <iostream>
#include <QApplication>
#include <QtGui>
#include "TextArea.h"
#include "PHIO.h"
#include "Exceptions.h"

TextArea::TextArea(QWidget *parent) :
    QTextEdit(parent)
{
    this->setMinimumWidth(200);
    this->setMaximumWidth(200);
    this->nberEdit = -1;
    this->nberTextChange = 0;
    QPalette p = this->palette();
    p.setColor(QPalette::Base, QColor(207, 226, 243));
    this->setPalette(p);
    this->setTextColor(QColor(46,46,46));
}


void TextArea::changeBackgroundColor(QColor color){
    // get the current palette of the textArea
    QPalette p = this->palette();
    // set the color chosen to the palette
    p.setColor(QPalette::Base, color);
    // set the palette to the textArea
    this->setPalette(p);
}

void TextArea::onTextEdit(){

    this->nberEdit++;
}

void TextArea::decNberTextChange(){

    this->nberTextChange--;
}

int TextArea::getNberEdit(){

    return this->nberEdit;
}

void TextArea::setNberEdit(int a){

    this->nberEdit = a;
}

int TextArea::getNberTextChange(){

    return this->nberTextChange;
}

void TextArea::setNberTextChange(int a){

    this->nberTextChange = a;
}

void TextArea::incrementeNberTextChange(){

    this->nberTextChange++;
}
