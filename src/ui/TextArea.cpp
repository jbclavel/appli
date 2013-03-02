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
    //this->setMaximumHeight(600);
    this->nberEdit = -1;
    this->nberTextChange = 0;
    this->nberLetter = 0;
    this->listLetter = new QStringList();    
    this->setAcceptRichText(true);

    QPalette p = this->palette();
    p.setColor(QPalette::Base, QColor(10, 10, 10));
    this->setPalette(p);
    this->setCurrentFont(QFont("TypeWriter", 10));
    this->setTextColor(QColor("white"));
    this->setCursorWidth(2);
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
/*
void TextArea::keyReleaseEvent(QKeyEvent *event){

    if(event->key() != Qt::Key_Space && event->key() != Qt::Key_Return && event->key() != Qt::Key_Backspace){

        this->listLetter->insert(this->nberLetter, event->text());
        this->nberLetter++;
    }
    else{

        int pos = this->textCursor().position();

        this->appendWord(this->listLetter, pos);
        this->nberLetter = 0;
    }
}*/

void TextArea::appendWord(QStringList* list, int pos){

    if(!list->empty()){

        this->word = "";

        for(int i = 0; i < list->size(); i++){

            this->word.append(list->at(i));
        }

        QFile parseTemp("parseTemp.ph");

        parseTemp.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream flux(&parseTemp);
        flux.setCodec("UTF-8");

        flux << this->toPlainText() << endl;

        QString *file = new QString("parseTemp.ph");
        std::string phFile = file->toStdString();

        try{

            PHIO::parseFile(phFile);

            parseTemp.remove();
            this->setFontUnderline(false);
        }
        catch(ph_parse_error & argh){

            QString text = this->toPlainText();

            int begin = pos-this->nberLetter-1;
            this->setPlainText(text.replace(begin, this->nberLetter, "<u>" + this->word + "</u>"));

            QTextCursor cur = this->textCursor();
            cur.setPosition(pos);
            this->setTextCursor(cur);
            parseTemp.remove();
        }
    }

    list->clear();
    //std::cout << this->word.toStdString() << std::endl;
}
