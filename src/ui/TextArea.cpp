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

void TextArea::keyReleaseEvent(QKeyEvent *event){

    if(event->key() != Qt::Key_Space){

        this->listLetter->insert(this->nberLetter, event->text());
        this->nberLetter++;
    }
    else{
int pos = this->textCursor().position();
std::cout << "position départ : " << pos << std::endl;

        this->appendWord(this->listLetter, pos);
        this->nberLetter = 0;
    }
}

void TextArea::appendWord(QStringList* list, int pos){
std::cout << "entrée fonction : " << pos << std::endl;
    if(!list->empty()){

        this->word = "";

        for(int i = 0; i < list->size(); i++){

            this->word.append(list->at(i));
        }

        try{

               QFile parseTemp("parseTemp.ph");

                    parseTemp.open(QIODevice::WriteOnly | QIODevice::Truncate);
                    QTextStream flux(&parseTemp);
                    flux.setCodec("UTF-8");

                    flux << this->toPlainText() << endl;

                    QString *file = new QString("parseTemp.ph");
                    std::string phFile = file->toStdString();

                    PHIO::parseFile(phFile);

                    parseTemp.remove();
                    this->setFontUnderline(false);
        }
        catch(ph_parse_error & argh){

            //this->word.toUpper();
            QString text = this->toHtml();

            int begin = pos-this->nberLetter-1;

            this->setHtml(text.replace(begin, this->nberLetter, QString("<u>" + this->word + "</u>")));
            //this->setPlainText(text.replace(QString(this->word), QString("<u>" + this->word + "</u>")));

            std::cout << "avant set : " << pos << std::endl;
            QTextCursor cur = this->textCursor();
            cur.setPosition(pos);
            this->setTextCursor(cur);

            //this->setCursor(this->textCursor());
            std::cout << "après : " << this->textCursor().position() << std::endl;
        }
    }

    list->clear();
    //std::cout << this->word.toStdString() << std::endl;
}
