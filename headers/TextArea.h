#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <QTextEdit>
#include <QColor>

/**
  * @class TextArea
  * @brief Text Widget extends QTextEdit
  *
  */
class TextArea : public QTextEdit
{
    Q_OBJECT
public:

    /**
      * @brief constructor
      * @brief QWidget parent, the widget containing the TextArea, which is the Area
      *
      */
    TextArea(QWidget *parent);

    /**
      * @brief changes the text widget background color, called from a signal in the main window
      *
      */
    void changeBackgroundColor(QColor);

    /**
      * @brief getter of nberEdit attribut
      *
      */
    int getNberEdit();

    /**
      * @brief setter of nberEdit attribut
      *
      */
    void setNberEdit(int);

private :

    int nberEdit;

signals:

public slots:

    /**
      * @brief method to count change of the text area
      *
      */
    void onTextEdit();

};

#endif // TEXTAREA_H
