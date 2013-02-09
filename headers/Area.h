#ifndef AREA_H
#define AREA_H

#include <QWidget>
#include "Area.h"
#include "TextArea.h"
#include "TreeArea.h"
#include "MyArea.h"
#include "MainWindow.h"
#include "ColorerSequences.h"


/**
  * @class Area
  * @brief New Tab extends QWidget
  *
  */
class Area : public QWidget
{
    Q_OBJECT
public:
    /**
      * @brief constructor for Area
      * @param QWidget parent, the widget containing the Area, which is the TabbedView
      *
      */
    Area(QWidget *parent = 0, QString = "");

    /**
      * @brief pointer to the path
      *
      */
    QString path;

    /**
      * @brief Text before edition
      *
      */
    QString oldText;

    /**
      * @brief pointer to the MyArea
      *
      */
    MyArea *myArea;

    /**
      * @brief pointer to the indicatorEdit
      *
      */
    TextArea *indicatorEdit;

    /**
      * @brief pointer to the TextArea;
      *
      */
    TextArea *textArea;

    /**
      * @brief pointer to the treeArea;
      *
      */
    TreeArea *treeArea;

    /**
      * @brief pointer to the MainWindow;
      *
      */
    MainWindow* mainWindow;

    /**
      * @brief hides the text. Called from a signal in MainWindow
      *
      */
    void hideText();

    /**
      * @brief shows the text. Called from a signal in MainWindow
      *
      */
    void showText();

    /**
      * @brief hides the text. Called from a signal in MainWindow
      *
      */
    void hideTree();

    /**
      * @brief shows the text. Called from a signal in MainWindow
      *
      */
    void showTree();


    /**
      * @brief verfication of the text which is going to be save
      *
      */



    /**
      * @brief pointer to the widget containing the hide / show text buttons
      *
      */
    QWidget* textButtonArea;

    /**
      * @brief pointer to the widget containing the hide / show tree button
      *
      */
    QWidget* treeButtonArea;

    /**
      * @brief pointer to the hide / show tree button
      *
      */
    QPushButton* leftButton;

    /**
      * @brief pointer to the hide / show text button
      *
      */
    QPushButton* rightButton;

    /**
      * @brief pointer to the expand / reduce text button
      *
      */
    QPushButton* rightExpandButton;

    /**
      * @brief pointer to edit/readOnly textArea button
      *
      */

    QPushButton* editTextArea;

    /**
      * @brief pointer to save edit text button
      *
      */

    QPushButton* saveTextEdit;

    /**
      * @brief pointer to cancel edit text button
      *
      */

    QPushButton* cancelTextEdit;

    /**
      * @brief pointer to color text in the textArea
      *
      */

    ColorerSequences *colorerSequences;
    void editText();


signals:

public slots:

    /**
      * @brief method to hide or show the text area clicking on the button
      *
      */
    void hideOrShowText();

    /**
      * @brief method to expand or reduce the text area clicking on the button
      *
      */
    void expandOrReduceText();

    /**
      * @brief method to hide or show the text area clicking on the button
      *
      */
    void hideOrShowTree();

    /**
      * @brief method to edit text area clicking on the button
      *
      */

    /**
      * @brief method to cancel text change clicking on the button
      *
      */
    void cancelEdit();

    /**
      * @brief method to save text change clicking on the button
      *
      */
    void confirmEdit();


    void saveEdit();

    void onTextEdit();

};

#endif // AREA_H
