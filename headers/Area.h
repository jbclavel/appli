#ifndef AREA_H
#define AREA_H

#include <QWidget>
#include "Area.h"
#include "TextArea.h"
#include "TreeArea.h"
#include "MyArea.h"
#include "MainWindow.h"


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
      * @brief pointer to the MyArea
      *
      */
    MyArea *myArea;

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

};

#endif // AREA_H
