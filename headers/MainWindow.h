#pragma once
#include <QMainWindow>
#include "MyArea.h"
#include <qthread.h>
#include "ConnectionSettings.h"
#include <vector>
#include "FunctionForm.h"
#include "ConnectionSettings.h"

/**
  * @file MainWindow.h
  * @brief header for the MainWindow class
  * @author PAPPL_2012
  *
  */


/**
  * @class MainWindow
  * @brief Builds the main window of the program
  * extends QMainWindow
  *
  */
class MainWindow : public QMainWindow{

    Q_OBJECT


public:

    static MainWindow* mwThis;
    QStringList wordList(const QString& text);

    /**
      * @brief constructor: creates the window, the menus and initializes the characteristics
      *
      */
    MainWindow();

    ~MainWindow();

    /**
      * @brief gets centraleArea
      *
      * @return QMdiArea* pointer to the central zone of the window
      *
      */
    QMdiArea* getCentraleArea();

    /**
      * @brief gets the paths of all the PH files that are currently opened
      *
      */
    std::vector<QString> getAllPaths();

    //method for the menu computation
    /**
      * @brief calls the pint prConnectionSettings()ogram with the given arguments
      *
      * @param Qstring the program to execute
      * @param QStringList the arguments to give to the program
      * @param QString (optional) the name of the PH file to parse
      *
      */
    void compute(QString program, QStringList arguments, QString fileName="");

    //enableMenu (in relation with the slot disableMenu)
    /**
      * @brief enables the menus that are related to any open, active tab
      * @note to be updated for each new feature of the application
      *
      */
    void enableMenu();
    QString pathCurrentWindow();


protected:

    /**
      * @brief pointer to the central area of the window
      *
      */
    QMdiArea* centraleArea;
    ConnectionSettings* ConnectionSettingsWindow;
    FunctionForm* FunctionFormWindow;

    // QMenu
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuStyles;
    QMenu *menuWindow;
    QMenu *menuComputation;
    QMenu *menuHelp;

    // actions for the menu File
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSaveas;
    QMenu   *menuExport;
    QAction *actionPng;
    QAction *actionDot;
    QAction *actionExportXMLData;
    QMenu   *menuImport;
    QAction *actionForimport;
    QAction *actionClose;
    QAction *actionQuit;

    // actions for the menu Edit
    QAction *actionUndo;
    QAction *actionRedo;

    // actions for the menu View
    QAction *actionAdjust;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionShowInit;
    QAction *actionHighlight;
    QAction *actionHide;
    QAction *actionDisplayDetailed;

    //actions for the menu Styles
    QAction *actionBackgroundColor;
    QAction *actionSortColor;
    QMenu *menuDefaultStyles;
    QAction *actionNaturalStyle;
    QAction *actionNegativeStyle;
    QAction *actionPrintStyle;

    // actions for the menu Workspace
    QMenu *menuText;
    QAction *actionHideShowText;
    QAction *actionChangeTextBackgroundColor;
    QMenu *menuTree;
    QAction *actionHideShowTree;

    // actions for the menu Computation
    QAction *actionFindFixpoints;
    QAction *actionComputeReachability;
    QAction *actionRunStochasticSimulation;
    QAction *actionCheckModelType;
    QAction *actionStatistics;
    QMenu *menuConnection;
    QAction *actionConnection;
    QAction *actionNewConnection;

    // action for the menu Help
    QAction *actionHelp;

signals:


public slots:

    //menu file

    /**
      * @brief opens a new tab
      *
      * @return MyArea* pointer to newly created MyArea object
      *
      */
    MyArea* openTab();

    /**
      * @brief saves the file
      *
      */
    void save();

    /**
      * @brief closes the active tab
      *
      */
    void closeTab();

    /**
      * @brief exports the current view to PNG file
      *
      */
    void exportPng();

    /**
      * @brief exports the current file to DOT file
      *
      */
    void exportDot();

    /**
      * @brief exports style and layout data to XML format
      *
      */
    void exportXMLMetadata();

    /**
      * @brief imports style and layout data from XML format
      *
      */
    void importXMLMetadata(QString tempXML = "");

    // menu view

    /**
      * @brief fits the scale to see the entire window
      *
      */
    void adjust();


    /**
      * @brief zooms the view in
      *
      */
    void zoomIn();

    /**
      * @brief zooms the view out
      *
      */
    void zoomOut();

    /**
      * @brief let the user set the background color
      *
      */
    void changeBackgroundColor();

    /**
      * @brief let the user set the sorts color
      *
      */
    void changeSortColor();

    /**
      * @brief sets default style: natural contrast (white background)
      *
      */
    void positiveContrast();

    /**
      * @brief sets default style: negative contrast (dark background)
      *
      */
    void negativeContrast();

    /**
      * @brief sets default style: compatible with print (empty sorts: "wired" style)
      *
      */
    void printStyle();

    /**
      * @brief hide / show the text area
      *
      */
    void hideShowText();

    /**
      * @brief change text background color
      *
      */
    void changeTextBackgroundColor();

    /**
      * @brief hide / show the tree area
      *
      */
    void hideShowTree();


    //menu computation

    /**
      * @brief executes pint program: ph-stable
      *
      */
    void findFixpoints();

    /**
      * @brief executes pint program: ph-reach
      *
      */
    void computeReachability();

    /**
      * @brief executes pint program: ph-exec
      *
      */
    void runStochasticSimulation();

    /**
      * @brief checks the type of the model
      *
      */
    void checkModelType();

    /**
      * @brief calls ph-stat functionality of pint
      *
      */
    void statistics();

    /**
      * @brief disables the menus that are related to open, active tabs
      *
      * @param QMdiSubWindow* menu you want to disable
      *
      */
    void disableMenu(QMdiSubWindow* subWindow);

    /**
      * @brief search a sort in the Sort Tree
      *
      */
    void searchSort();

    /**
      * @brief open connection settings window
      * to implement a new function
      *
      */

    void openConnection();

    void openConnectionForm();

    };
