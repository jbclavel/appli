#include <QApplication>
#include <QtGui>
#include "MainWindow.h"
#include "MyArea.h"
#include "PHIO.h"
#include "Exceptions.h"
#include "Area.h"
#include <stdio.h>
#include <qthread.h>
#include <iostream>
#include "ConnectionSettings.h"

MainWindow::MainWindow(){

    // title
    setWindowTitle("gPH");

    // icon
    setWindowIcon(QIcon("gph.png"));

    // min size
    setMinimumWidth(600);
    setMinimumHeight(400);

    // menu
    menuFile =          menuBar()->addMenu("&File");
    menuEdit =          menuBar()->addMenu("&Edit");
    menuView =          menuBar()->addMenu("&View");
    menuStyles =        menuBar()->addMenu("&Styles");
    menuWindow =     menuBar()->addMenu("&Window");
    menuComputation =   menuBar()->addMenu("&Computation");
    menuHelp =          menuBar()->addMenu("&Help");

    // actions for the menus:

    // actions for the menu File
    actionNew = menuFile->addAction("New");
    actionOpen = menuFile->addAction("Open...");
    menuFile->addSeparator();
    actionSaveas = menuFile->addAction("Save as...");
    menuExport = menuFile->addMenu("Export");
    actionPng = menuExport->addAction("PNG graph");
    actionDot = menuExport->addAction("DOT graph");
    actionExportXMLData = menuExport->addAction("Style and Layout");
    menuImport = menuFile->addMenu("Import");
    actionForimport = menuImport->addAction("Au travail Remi !");
    menuFile->addSeparator();
    actionClose = menuFile->addAction("Close");
    actionQuit = menuFile->addAction("Quit");

    // disable what does not work well
    actionNew->setEnabled(false);
    actionForimport->setEnabled(false);


    // shortcuts for the menu File
    actionNew->setShortcut(     QKeySequence(Qt::CTRL + Qt::Key_N));
    actionOpen->setShortcut(    QKeySequence(Qt::CTRL + Qt::Key_O));
    actionSaveas->setShortcut(  QKeySequence(Qt::CTRL + Qt::Key_S));
    actionQuit->setShortcut(    QKeySequence(Qt::CTRL + Qt::Key_Q));
    actionForimport->setShortcut(    QKeySequence(Qt::CTRL + Qt::Key_I));


    // connect the menu File
    QObject::connect(actionQuit,    SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(actionOpen,    SIGNAL(triggered()), this, SLOT(openTab()));
    QObject::connect(actionSaveas,  SIGNAL(triggered()), this, SLOT(save()));
    QObject::connect(actionPng,     SIGNAL(triggered()), this, SLOT(exportPng()));
    QObject::connect(actionClose,   SIGNAL(triggered()), this, SLOT(closeTab()));
    QObject::connect(actionExportXMLData, SIGNAL(triggered()), this, SLOT(exportXMLMetadata()));
    QObject::connect(actionDot, SIGNAL(triggered()), this, SLOT(exportDot()));
    QObject::connect(actionForimport, SIGNAL(triggered()), this, SLOT(openTab()));

    // actions for the menu Edit
    actionUndo = menuEdit->addAction("Undo");
    actionRedo = menuEdit->addAction("Redo");

    // disable what does not work well
    actionUndo->setEnabled(false);
    actionRedo->setEnabled(false);

    // actions for the menu View
    actionAdjust = menuView->addAction("Adjust View");
    actionZoomIn = menuView->addAction("Zoom In");
    actionZoomOut = menuView->addAction("Zoom Out");

    actionShowInit = menuView->addAction("Show initial state");
    actionHighlight = menuView->addAction("Highlight possible actions");
    actionHide = menuView->addAction("Hide actions");
    actionDisplayDetailed = menuView->addAction("Display detailed cooperativities");

    actionShowInit->setCheckable(true);
    actionHighlight->setCheckable(true);

    // connect to the menu View
    QObject::connect(actionAdjust,    SIGNAL(triggered()), this, SLOT(adjust()));
    QObject::connect(actionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));
    QObject::connect(actionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));

    // shortcuts for the menu View
    actionAdjust->setShortcut(  QKeySequence(Qt::CTRL + Qt::Key_L));
    actionZoomIn->setShortcut(  QKeySequence(Qt::CTRL + Qt::Key_Plus));
    actionZoomOut->setShortcut(  QKeySequence(Qt::CTRL + Qt::Key_Minus));

    // disable what does not work well
    actionShowInit->setEnabled(false);
    actionHighlight->setEnabled(false);
    actionHide->setEnabled(false);
    actionDisplayDetailed->setEnabled(false);


    //actions for the menu Styles
    actionBackgroundColor = menuStyles->addAction("Set background color");
    actionSortColor = menuStyles->addAction("Set sorts color");
    menuDefaultStyles = menuStyles->addMenu("Default Styles");
    actionNaturalStyle = menuDefaultStyles->addAction("Positive contrast");
    actionNegativeStyle = menuDefaultStyles->addAction("Negative contrast");
    actionPrintStyle = menuDefaultStyles->addAction("Print");    

    //connect to the menu Styles
    QObject::connect(actionBackgroundColor, SIGNAL(triggered()), this, SLOT(changeBackgroundColor()));
    QObject::connect(actionSortColor, SIGNAL(triggered()), this, SLOT(changeSortColor()));
    QObject::connect(actionNaturalStyle, SIGNAL(triggered()), this, SLOT(positiveContrast()));
    QObject::connect(actionNegativeStyle, SIGNAL(triggered()), this, SLOT(negativeContrast()));
    QObject::connect(actionPrintStyle, SIGNAL(triggered()), this, SLOT(printStyle()));


    //actions for the menu Workspace
    actionHideShowText = menuWindow->addAction("Hide / Show Text");
    actionChangeTextBackgroundColor = menuWindow->addAction("Set Text Background Color");
    menuWindow->addSeparator();
    actionHideShowTree = menuWindow->addAction("Hide / Show Tree");

    //connect to the menu Workspace
    QObject::connect(actionHideShowText, SIGNAL(triggered()), this, SLOT(hideShowText()));
    QObject::connect(actionChangeTextBackgroundColor, SIGNAL(triggered()), this, SLOT(changeTextBackgroundColor()));
    QObject::connect(actionHideShowTree, SIGNAL(triggered()), this, SLOT(hideShowTree()));


    // actions for the menu Computation
    actionFindFixpoints = menuComputation->addAction("Find fixpoints...");
    actionComputeReachability = menuComputation->addAction("Compute reachability...");
    actionRunStochasticSimulation = menuComputation->addAction("Run stochastic simulation...");
    actionCheckModelType = menuComputation->addAction("Check model type (binary or multivalued)");
    actionStatistics = menuComputation->addAction("Statistics...");
    menuComputation->addSeparator();
    actionConnection = menuComputation->addAction("New Connection");

    // disable what does not work well
    actionComputeReachability->setEnabled(false);
    actionCheckModelType->setEnabled(false);

    // connect the menu Computation
    QObject::connect(actionFindFixpoints, SIGNAL(triggered()), this, SLOT(findFixpoints()));
    QObject::connect(actionComputeReachability, SIGNAL(triggered()), this, SLOT(computeReachability()));
    QObject::connect(actionRunStochasticSimulation, SIGNAL(triggered()), this, SLOT(runStochasticSimulation()));
    QObject::connect(actionCheckModelType, SIGNAL(triggered()), this, SLOT(checkModelType()));
    QObject::connect(actionStatistics, SIGNAL(triggered()), this, SLOT(statistics()));
    QObject::connect(actionConnection, SIGNAL(triggered()), this, SLOT(openConnection()));


    // action for the menu Help
    actionHelp = menuHelp->addAction("Help !");

    // disable what does not work well
    actionHelp->setEnabled(false);

    // main area
    this->centraleArea = new QMdiArea();
    setCentralWidget(centraleArea);
    centraleArea->setViewMode(QMdiArea::TabbedView);

    // management of the menus (enabled/disabled)
    QObject::connect(this->centraleArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(disableMenu(QMdiSubWindow*)));

    if(this->getCentraleArea()->subWindowList().isEmpty()){
        this->actionClose->setEnabled(false);
        this->actionSaveas->setEnabled(false);
        this->actionPng->setEnabled(false);
        this->actionDot->setEnabled(false);
        this->actionExportXMLData->setEnabled(false);
        this->actionForimport->setEnabled(false);
        this->actionAdjust->setEnabled(false);
        this->actionZoomOut->setEnabled(false);
        this->actionZoomIn->setEnabled(false);
        this->actionBackgroundColor->setEnabled(false);
        this->actionSortColor->setEnabled(false);
        this->actionNaturalStyle->setEnabled(false);
        this->actionNegativeStyle->setEnabled(false);
        this->actionPrintStyle->setEnabled(false);
        this->actionHideShowText->setEnabled(false);
        this->actionChangeTextBackgroundColor->setEnabled(false);
        this->actionHideShowTree->setEnabled(false);
        this->actionFindFixpoints->setEnabled(false);
        this->actionRunStochasticSimulation->setEnabled(false);
        this->actionStatistics->setEnabled(false);
    }

}


MainWindow::~MainWindow() {
    delete centraleArea;
}


QMdiArea* MainWindow::getCentraleArea() {
    return this->centraleArea;
}


// get all open files' paths
std::vector<QString> MainWindow::getAllPaths() {
    int size = this->getCentraleArea()->subWindowList().size();
    std::vector<QString> allPaths;
    QString path;
    for(int n=0; n<size; n++) {
        path = ((Area*) this->getCentraleArea()->subWindowList()[n]->widget())->path;
        allPaths.push_back(path);
    }
    return allPaths;
}


// open a new tab
MyArea* MainWindow::openTab() {

        // OpenFile dialog
        QFileDialog* filedialog = new QFileDialog(this);
        QString file = filedialog->getOpenFileName(this, "Open...");
        QDialog* mb = new QDialog(filedialog);
        mb->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

        // TODO refactor using early returns
        if(file!=NULL) {

            QFileInfo pathInfo(file);
            std::vector<QString> allPath = this->getAllPaths();
            int size = allPath.size();
            bool alreadyOpen = false;

            // check if the file is already open
            for(int i=0;i<size;i++) {
                if(allPath[i]==file) {
                   alreadyOpen = true;
                    break;
                }
            }

            if(!alreadyOpen) {

                //Affichage de la fenêtre de chargement

                QLabel* dialogue = new QLabel(mb);
                mb->setWindowTitle("Please wait...");
                QMovie* gif = new QMovie("loading_gif.gif");
                gif->start();
                dialogue->setMovie(gif);
                dialogue->show();
                mb->open();

               // sleep(5);

                //need a std::string instead of a QString
                std::string path =	file.toStdString();                

                // parse file
                Area *area = new Area(this, QString::fromStdString(path));
                area->mainWindow = this;


                try {

                    // render graph
                    PHPtr myPHPtr = PHIO::parseFile(path);
                    area->myArea->setPHPtr(myPHPtr);
					myPHPtr->render();
                    PHScenePtr scene = myPHPtr->getGraphicsScene();
                    area->myArea->setScene(&*scene);

                    // set the pointer of the treeArea
                    area->treeArea->myPHPtr = myPHPtr;
                    //set the pointer of the treeArea
                    area->treeArea->myArea = area->myArea;
                    // build the tree in the treeArea
                    area->treeArea->build();

                    // call the PH string and write it in the text area (dump)
                    //std::string string(myPHPtr->toString());
                    //area->textArea->setPlainText(QString::fromStdString(string));

                    // call the PH file and write it in the text area (same as .ph)
                    QFile fichier(file);
                    fichier.open(QIODevice::ReadOnly);
                    QByteArray data;
                    data = fichier.readAll();
                    QString ligne(data);
                    area->textArea->setPlainText(ligne);

                    // make the subwindow for the new tab
                    QMdiSubWindow *theNewTab = this->getCentraleArea()->addSubWindow(area);
                    QString fileName(pathInfo.fileName());
                    theNewTab->setWindowTitle(fileName);
                    this->enableMenu();                    

                    mb->close();
                    this->setWindowState(Qt::WindowMaximized);

                    return area->myArea;

                } catch(exception_base& argh) {
                    mb->close();
                    QMessageBox::critical(this, "Error", "Extension not recognized. Only ph files are accepted.");
                    return NULL;
                }
            }


            else {
                mb->close();
                QMessageBox::critical(this, "Error", "This file is already opened!");
                return NULL;
            }



        } else {
            mb->close();
            return NULL;
        }
}


// close a tab
void MainWindow::closeTab() {

    // if there is at least one subwindow, close the current one
    if(!this->getCentraleArea()->subWindowList().isEmpty()) {
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();
        subWindow->close();
    } else {
        QMessageBox::critical(this, "Error", "No file opened!");
    }
}


// save a graph
void MainWindow::save() {

    if(!this->getCentraleArea()->subWindowList().isEmpty()){
        // get the current subwindow
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();

        // SaveFile dialog
        QString fichier = QFileDialog::getSaveFileName(this, "Save file");

        // need a std::string instead of a QString
        std::string path =	fichier.toStdString();

        // need the PHPtr which is associated with the subwindow
        //PHPtr ph= ((MyArea*) subWindow->widget())->getPHPtr();
        PHPtr ph= ((Area*) subWindow->widget())->myArea->getPHPtr();

        // save file
        PHIO::writeToFile (path, ph);
        //this->newph.remove();

    } else {
        QMessageBox::critical(this, "Error", "No file opened!");
    }
}


// export methods

void MainWindow::exportPng() {
	
    if(!this->getCentraleArea()->subWindowList().isEmpty()){
        // get the current subwindow
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();

        // SaveFile dialog
        QString fichier = QFileDialog::getSaveFileName(this, "Export as .png file", QString(), "*.png");

        // need the PHPtr which is associated with the subwindow
        PHPtr ph= ((Area*) subWindow->widget())->myArea->getPHPtr();

        // save as PNG
		PHIO::exportToPNG(ph, fichier);
		
    } else QMessageBox::critical(this, "Error", "No file opened!");
	
}

void MainWindow::exportDot() {

    if(!this->getCentraleArea()->subWindowList().isEmpty()){
        // get the current subwindow
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();

        // SaveFile dialog
        QString fichier = QFileDialog::getSaveFileName(this, "Export as .dot file", QString(), "*.dot");

        // add .dot to the name if necessary
        if (fichier.indexOf(QString(".dot"), 0, Qt::CaseInsensitive) < 0){
            fichier += ".dot";
        }

        // need the String file of the Dot
        QString str= QString::fromStdString(((Area*) subWindow->widget())->myArea->getPHPtr()->toDotString());

        QFile file(fichier);
        if (!file.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this, "Error", "Sorry, unable to open file.");
            file.errorString();
            return;
        }
        else{
            QDataStream out(&file);
            out.setVersion(QDataStream::Qt_4_5);
            out << str;
        }

    } else QMessageBox::critical(this, "Error", "No file opened!");

}

// method to export style and layout data to XML format
void MainWindow::exportXMLMetadata(){

    if(!this->getCentraleArea()->subWindowList().isEmpty()){

        // SaveFile dialog
        QString xmlFile = QFileDialog::getSaveFileName(this, "Export preferences", QString(), "*.xml");

        // add .dot to the name if necessary
        if (xmlFile.indexOf(QString(".xml"), 0, Qt::CaseInsensitive) < 0){
            xmlFile += ".xml";
        }

        // open file if possible and write XML tree into it
        QFile output(xmlFile);
        if (!output.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this, "Error", "Sorry, unable to open file.");
            output.errorString();
            return;
        } else {
            PHIO::exportXMLMetadata(this, output);
        }

    } else QMessageBox::critical(this, "Error", "No file opened!");

}

// method to adjust the view
void MainWindow::adjust()
{
    // get the widget in the centrale area
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    // get the myArea (middle) part and fit the view
    view->myArea->fitInView(view->myArea->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}

// method to zoom In
void MainWindow::zoomIn()
{
    // get the widget in the central area
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    // get the myArea (middle) part and call the method associated to zoom in
    view->myArea->zoomIn();
}

// method to zoom out
void MainWindow::zoomOut()
{
    // get the widget in the central area
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    // get the myArea (middle) part and call the method associated to zoom out
    view->myArea->zoomOut();
}

void MainWindow::searchSort()
{
    // get the widget in the centrale area
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    // get the treeArea (left) part and call the method associated to search a sort
    view->treeArea->searchSort();
}


// method to change the background color
void MainWindow::changeBackgroundColor() {

    // open a color dialog and get the color chosen
    QColor color = QColorDialog::getColor();

    // get the widget in the centrale area
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();

    if(!color.isValid()){
        return ;
    } else {
        // If the color chosen is valid, get the myArea (middle) part and set the backgroundbrush of the PH Scene
        view->myArea->getPHPtr()->getGraphicsScene()->setBackgroundBrush(color);
    }
}


// method to change the sorts color
void MainWindow::changeSortColor() {

    // open a color dialog and get the color chosen
    QColor color = QColorDialog::getColor();

    // get the widget in the central area
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    // get the map of all the gsorts in the myArea, related to the name of the sorts
    map<string, GSortPtr> sortList = view->myArea->getPHPtr()->getGraphicsScene()->getGSorts();

    if (!color.isValid()) {
        return ;
    } else {
        map<string, GSortPtr>::iterator it;
        for(it=sortList.begin(); it!=sortList.end(); it++) {
            // for all the GSort in the map, set the brush
            it->second->getRect()->setBrush(QBrush(QColor(color)));
        }
    }
}


// method to set the default style: positive
void MainWindow::positiveContrast() {

    // get the widget in the central area
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    // get the map of all the gsorts
    map<string, GSortPtr> sortList = view->myArea->getPHPtr()->getGraphicsScene()->getGSorts();

    // set the background color to white
    view->myArea->getPHPtr()->getGraphicsScene()->setBackgroundBrush(QColor(255,255,255));

    // set the sorts brush to dark
    map<string, GSortPtr>::iterator it;
    for(it=sortList.begin(); it!=sortList.end(); it++) {
        it->second->getRect()->setPen(QPen(QColor(0,51,102)));
        it->second->getRect()->setBrush(QBrush(QColor(0,51,102)));
    }

    // get all the processes of the PH scene
    std::vector<GProcessPtr> processes = view->myArea->getPHPtr()->getGraphicsScene()->getProcesses();
    // set the color ellipse to transparent
    for (GProcessPtr &a: processes){
        a->getEllipseItem()->setPen(QPen(Qt::black, 1));
        a->getEllipseItem()->setBrush(QBrush(QColor(220,220,220)));
    }
}

// method to set the default style: negative
void MainWindow::negativeContrast() {

    // get the widget in the central area
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    // get the map of all the gsorts associated to their names
    map<string, GSortPtr> sortList = view->myArea->getPHPtr()->getGraphicsScene()->getGSorts();

    // set the background color to dark grey
    view->myArea->getPHPtr()->getGraphicsScene()->setBackgroundBrush(QColor(31,31,31));

    // set the sorts brush to clear
    map<string, GSortPtr>::iterator it;
    for(it = sortList.begin(); it != sortList.end(); it++) {
        it->second->getRect()->setPen(QPen(QColor(7,54,66)));
        it->second->getRect()->setBrush(QBrush(QColor(100,100,100)));
    }
    // get all the processes of the PH scene
    std::vector<GProcessPtr> processes = view->myArea->getPHPtr()->getGraphicsScene()->getProcesses();
    // set the color ellipse to transparent
    for (GProcessPtr &a: processes){
        a->getEllipseItem()->setPen(QPen(Qt::black, 1));
        a->getEllipseItem()->setBrush(QBrush(QColor(160,160,160)));
    }
}

// method to set the default style: print
void MainWindow::printStyle() {

    // get the widget in the central area
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    // get the map of all the gsorts associated to their names
    map<string, GSortPtr> sortList = view->myArea->getPHPtr()->getGraphicsScene()->getGSorts();

    // set the background color to white
    view->myArea->getPHPtr()->getGraphicsScene()->setBackgroundBrush(Qt::white);

    // set the brush color to black
    map<string, GSortPtr>::iterator it;
    for(it = sortList.begin(); it != sortList.end(); it++) {
        it->second->getRect()->setPen(QPen(Qt::black, 4));
        it->second->getRect()->setBrush(Qt::NoBrush);
    }

    // get all the processes of the PH scene
    std::vector<GProcessPtr> processes = view->myArea->getPHPtr()->getGraphicsScene()->getProcesses();
    // set the color ellipse to transparent
    for (GProcessPtr &a: processes){
        a->getEllipseItem()->setPen(QPen(Qt::black, 3));
        a->getEllipseItem()->setBrush(Qt::NoBrush);
    }


}

// hide / show the text area. Called by the signal actionHideShowText
void MainWindow::hideShowText(){
    // get the widget in the central area, cast it to Area (to use the methods)
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    // cal the method to hide or show text
    view->hideOrShowText();
}

// change the text background color in the text area. Called by the signal actionChangeTextBackgroundColor
void MainWindow::changeTextBackgroundColor(){
    // open a color dialog and get the color chosen
    QColor color = QColorDialog::getColor();
    // get the widget in the central area
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();

    if (!color.isValid()) {
        return ;
    } else {
        // call the method in textArea to set the background color to the color chosen
        view->textArea->changeBackgroundColor(color);
    }
}

// hide the tree area. Called by the signal actionHideTree
void MainWindow::hideShowTree(){
    // get the widget in the central area, cast it to Area (to use the methods)
    Area* view = (Area*) this->getCentraleArea()->currentSubWindow()->widget();
    // call the method to hide or show the tree
    view->hideOrShowTree();
}




// main method for the computation menu
void MainWindow::compute(QString program, QStringList arguments, QString fileName) {

    // start process
    QProcess *myProcess = new QProcess();

    myProcess->start(program, arguments);

    if (!myProcess->waitForStarted())
        throw pint_program_not_found() << file_info("phc");

    // read result
    QByteArray err;
    QByteArray out;
    while (!myProcess->waitForFinished()) {
        err += myProcess->readAllStandardError();
        out += myProcess->readAllStandardOutput();
    }
    err += myProcess->readAllStandardError();
    out += myProcess->readAllStandardOutput();
    delete myProcess;

    // pop up for the errors
    if(!err.isEmpty()){

        //correct a false error message for ph-stable
        if(program==QString("ph-stable")) {
            if( !(QString(err).contains(fileName)) || fileName.isEmpty() ) {
                QMessageBox::critical(this, program+".error", err);
            }
        } else {
            //correct a false error message for ph-exec
            if(program!=QString("ph-exec")) {
                QMessageBox::critical(this, program+".error", err);
            }
        }
    }

    //pop up for the output
    if(!out.isEmpty()){

        QMessageBox::information(this, program+".output", out);

    }


}


void MainWindow::findFixpoints() {

    QString program = "ph-stable";
    QStringList arguments;

    // get the filename associated with the current subWindow
    QString fileName;
    if(this->getCentraleArea()->currentSubWindow() != 0) {
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();
        fileName = ((Area*) subWindow->widget())->path;
    } else {
        fileName = "";
    }

    // give the arguments
    arguments << "--no-debug" << "-i" << fileName;

    // call MainWindow::compute
    this->compute(program, arguments, fileName);
}


void MainWindow::computeReachability() {

    QString program = "ph-reach";
    QStringList arguments;

    // get the filename associated with the current subWindow
    QString fileName;
    if(this->getCentraleArea()->currentSubWindow() != 0){ // if a subWindow exists
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();
        fileName = ((Area*) subWindow->widget())->path;
    } else {
        fileName = "";
    }

    //ask the user the state which is tested
    bool ok = false;
    QString state = QInputDialog::getText(this, "reachability", "Which state do you want to test ?", QLineEdit::Normal, QString(), &ok);

    if (ok && !state.isEmpty()) {
        // give the arguments
        arguments << "--no-debug" << "-i" << fileName << state.at(0) << state.at(1) ;

        //call MainWindow::compute
        this->compute(program, arguments);
    }
}


void MainWindow::runStochasticSimulation() {

    QString program = "ph-exec";
    QStringList arguments;

    // get the filename associated with the current subWindow
    QString fileName;
    if(this->getCentraleArea()->currentSubWindow() != 0) { // if a subWindow exists
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();
        fileName = ((Area*) subWindow->widget())->path;
    } else {
        fileName = "";
    }

    /*//ici
    QString out1 = QString::fromUtf8(out.data());
    QString err1 = QString::fromUtf8(err.data());
    QMessageBox::information(this, "program", program);
    //for (int i = 0; i < arguments.size(); ++i){
    //QMessageBox::information(this, "test err", arguments.at(i));
    //}
    QMessageBox::information(this, "out", out1);
    QMessageBox::information(this, "err", err1);
    //QMessageBox::information(this, "state", state);
    QString az;
    QString ae ;
    if (ok== false){
         az = "false";
    }else{
        az= "true";
    }
    if (!state.isEmpty()== false){
         ae = "false";
    }else{
        ae= "true";
    }
    QMessageBox::information(this, "ok", az);//ok =true && !state.isEmpty()
    QMessageBox::information(this, "!state.isEmpty()", ae);//ok =true && !state.isEmpty()
*/

    //a  la

    //ask the user for duration and output directory
    bool ok1 = false;
    QString duration = QInputDialog::getText(this, "stochastic simulation", "Give a duration", QLineEdit::Normal, QString(), &ok1);

    if(ok1 && !duration.isEmpty()) {
        QString outputdirectory = QFileDialog::getExistingDirectory(this, "output directory");

        if (!outputdirectory.isEmpty()) {
            // give the arguments
            arguments << "--no-debug" << "-i" << fileName << duration << outputdirectory;

            //call MainWindow::compute
            this->compute(program, arguments);
        }
    }
}


// NOT IMPLEMENTED!
// TODO implement it
void MainWindow::checkModelType(){
    QString program = "";
    QStringList arguments;
    arguments << "gruik" << "gruik";
    this->compute(program, arguments);
}


void MainWindow::statistics(){

    QString program = "ph-stat";
    QStringList arguments;

    // get the filename associated with the current subWindow
    // TODO factorize the following lines (present in every pint program execution method)
    QString fileName;
    if(this->getCentraleArea()->currentSubWindow() != 0) { // if a subWindow exists
        QMdiSubWindow *subWindow = this->getCentraleArea()->currentSubWindow();
        fileName = ((Area*) subWindow->widget())->path;
    } else {
        fileName = "";
    }

    // give the arguments
    arguments << "--no-debug" << "-i" << fileName;

    // call MainWindow::compute
    this->compute(program, arguments);
}


//open connection settings window
void MainWindow::openConnection(){

    ConnectionSettingsWindow = new ConnectionSettings();
    ConnectionSettingsWindow->show();
}

// disable menus when no open, active tabs
void MainWindow::disableMenu(QMdiSubWindow* subwindow){
    if(subwindow==0&&this->getCentraleArea()->subWindowList().isEmpty()) {
        this->actionClose->setEnabled(false);
        this->actionSaveas->setEnabled(false);
        this->actionPng->setEnabled(false);
        this->actionDot->setEnabled(false);
        this->actionExportXMLData->setEnabled(false);
        this->actionForimport->setEnabled(false);
        this->actionAdjust->setEnabled(false);
        this->actionZoomIn->setEnabled(false);
        this->actionZoomOut->setEnabled(false);
        this->actionBackgroundColor->setEnabled(false);
        this->actionSortColor->setEnabled(false);
        this->actionNaturalStyle->setEnabled(false);
        this->actionNegativeStyle->setEnabled(false);
        this->actionPrintStyle->setEnabled(false);
        this->actionHideShowText->setEnabled(false);
        this->actionChangeTextBackgroundColor->setEnabled(false);
        this->actionHideShowTree->setEnabled(false);
        this->actionFindFixpoints->setEnabled(false);
        this->actionComputeReachability->setEnabled(false);
        this->actionRunStochasticSimulation->setEnabled(false);
        this->actionStatistics->setEnabled(false);
    }
}


// enable menus when at least one open, active tab
void MainWindow::enableMenu(){
    if(!this->getCentraleArea()->subWindowList().isEmpty()){
        this->actionClose->setEnabled(true);
        this->actionSaveas->setEnabled(true);
        this->actionPng->setEnabled(true);
        this->actionDot->setEnabled(true);
        this->actionExportXMLData->setEnabled(true);
        this->actionForimport->setEnabled(true);
        this->actionAdjust->setEnabled(true);
        this->actionZoomIn->setEnabled(true);
        this->actionZoomOut->setEnabled(true);
        this->actionBackgroundColor->setEnabled(true);
        this->actionSortColor->setEnabled(true);
        this->actionNaturalStyle->setEnabled(true);
        this->actionNegativeStyle->setEnabled(true);
        this->actionPrintStyle->setEnabled(true);
        this->actionHideShowText->setEnabled(true);
        this->actionChangeTextBackgroundColor->setEnabled(true);
        this->actionHideShowTree->setEnabled(true);
        this->actionFindFixpoints->setEnabled(true);
        this->actionComputeReachability->setEnabled(true);
        this->actionRunStochasticSimulation->setEnabled(true);
        this->actionStatistics->setEnabled(true);
    }
}
