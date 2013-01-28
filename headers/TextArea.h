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

signals:

public slots:

};

#endif // TEXTAREA_H
