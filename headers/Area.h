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

    /**
      * @brief Temporary save of the textArea called by the signal of rightButton
      *
      */

    void editText();

    /**
      * @brief QStringList containing all the text change
      *
      */

    QStringList* listOldText;


    /**
      * @brief int indicating the moment when the user click on Cancel ( 1 : after update, 0 : during edition )
      *
      */

    int typeOfCancel;

    /**
      * @brief Return the temporary file for automatic import/export
      *
      */

    QFile getTempXML();

private:

    QFile tempXML;

signals:

    /**
      * @brief Indicate edition
      *
      */

    void edition();

    /**
      * @brief Moment when the XML temporary file has to be write
      *
      */

    void makeTempXML();

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
      * @brief method to cancel text change clicking on the button
      *
      */
    void cancelEdit();

    /**
      * @brief method to save text change clicking on the button
      *
      */
    void saveEdit(int del = 0);

    /**
      * @brief method call by the signal textChanged()
      *
      */
    void onTextEdit();

    /**
      * @brief method to save all the new textArea into the QStringList
      *
      */
    void setOldText();    

    /**
      * @brief method to show the tooltip about shortcuts of QTextEdit
      *
      */
    void showToolTip();

    /**
      * @brief method to hide the tooltip about shortcuts of QTextEdit
      *
      */
    void hideToolTip();

    /**
      * @brief method to make the XML temporary file before edition
      *
      */
    void tempXMLfile();

    /**
      * @brief method to delete the XML temporary file after update
      *
      */
    void deleteTempXML();

};

#endif // AREA_H
