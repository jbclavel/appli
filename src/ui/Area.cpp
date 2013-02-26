#include "Area.h"
#include "QHBoxLayout"
#include "PHIO.h"
#include "IO.h"
#include "Exceptions.h"

Area::Area(QWidget *parent, QString path) :
    QWidget(parent)
{
    this->path = path;

    // call the constructors of all the areas
    this->textArea = new TextArea(this);
    this->textArea->setReadOnly(false);
    this->myArea = new MyArea(this, this->path);
    this->treeArea = new TreeArea(this);
    this->indicatorEdit = new TextArea(this);
    this->listOldText = new QStringList();

    //Add text coloration (lie le TextArea)
    colorerSequences = new ColorerSequences(textArea->document());

    // treeArea: create widgets containing the buttons
    this->treeButtonArea = new QWidget(this);
    this->treeButtonArea->setMinimumWidth(12);
    this->treeButtonArea->setMaximumWidth(12);
    this->textButtonArea = new QWidget(this);
    this->textButtonArea->setMinimumWidth(12);
    this->textButtonArea->setMaximumWidth(12);

    // create the buttons
    this->leftButton = new QPushButton("<", this->treeButtonArea);
    this->leftButton->setMaximumWidth(12);
    this->leftButton->setMinimumHeight(70);
    QVBoxLayout *layoutLeft = new QVBoxLayout;
    layoutLeft->addWidget(leftButton);
    layoutLeft->setContentsMargins(0,0,0,0);
    this->treeButtonArea->setLayout(layoutLeft);

    this->rightButton = new QPushButton(">", this->textButtonArea);
    this->rightButton->setMaximumWidth(12);
    this->rightButton->setMinimumHeight(70);
    this->rightExpandButton = new QPushButton("<", this->textButtonArea);
    this->rightExpandButton->setMaximumWidth(12);
    this->rightExpandButton->setMinimumHeight(70);
    QVBoxLayout *layoutRight = new QVBoxLayout;
    layoutRight->addWidget(this->rightButton);
    layoutRight->addWidget(this->rightExpandButton);
    layoutRight->setContentsMargins(0,0,0,0);
    this->textButtonArea->setLayout(layoutRight);

    this->saveTextEdit = new QPushButton("Update",this);
    this->saveTextEdit->setFixedSize(QSize(80,30));
    this->saveTextEdit->setVisible(false);
    this->saveTextEdit->setEnabled(false);
    this->saveTextEdit->setShortcut(QKeySequence((Qt::CTRL + Qt::Key_E)));

    this->cancelTextEdit = new QPushButton("Cancel",this);
    this->cancelTextEdit->setFixedSize(QSize(80,30));
    this->cancelTextEdit->setVisible(false);
    this->cancelTextEdit->setEnabled(false);

    //indicatorEdit preferences

    this->indicatorEdit->setReadOnly(true);
    this->indicatorEdit->changeBackgroundColor(QColor("#F1F1F1"));
    this->indicatorEdit->setFixedSize(QSize(200,27));
    this->indicatorEdit->setTextColor(QColor(228,26,4));
    this->indicatorEdit->setCurrentFont(QFont("TypeWriter",10));
    this->indicatorEdit->setFontWeight(5);
    this->indicatorEdit->setFrameShape(QTextEdit::NoFrame);
    this->indicatorEdit->setFrameShadow(QTextEdit::Plain);
    this->indicatorEdit->setPlainText("Edition...");
    this->indicatorEdit->setVisible(false);
    //Press CTRL+E to save or CTRL+ESC to cancel

    // set the global layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(this->treeArea);
    layout->addWidget(this->treeButtonArea);
    layout->addWidget(this->myArea);
    layout->addWidget(this->textButtonArea);

    QVBoxLayout *VLayout = new QVBoxLayout;
    VLayout->addWidget(this->indicatorEdit);
    VLayout->addWidget(this->textArea);

    QHBoxLayout *options = new QHBoxLayout;
    options->addWidget(this->saveTextEdit);
    options->addWidget(this->cancelTextEdit);

    VLayout->addLayout(options);

    QHBoxLayout *global = new QHBoxLayout;
    global->addLayout(layout);
    global->addLayout(VLayout);

    this->setLayout(global);

    // connect
    QObject::connect(this->leftButton, SIGNAL(clicked()), this, SLOT(hideOrShowTree()));
    QObject::connect(this->rightButton, SIGNAL(clicked()), this, SLOT(hideOrShowText()));
    QObject::connect(this->rightExpandButton, SIGNAL(clicked()), this, SLOT(expandOrReduceText()));
    QObject::connect(this->cancelTextEdit, SIGNAL(clicked()), this, SLOT(cancelEdit()));
    QObject::connect(this->textArea, SIGNAL(textChanged()), this->textArea, SLOT(onTextEdit()));
    QObject::connect(this->saveTextEdit, SIGNAL(clicked()), this, SLOT(saveEdit()));
    QObject::connect(this->textArea, SIGNAL(textChanged()), this, SLOT(onTextEdit()));

    // initialization
    this->textArea->setHidden(true);
    this->rightButton->setText("<");
    this->rightExpandButton->hide();
    this->saveTextEdit->setDefault(false);
    this->cancelTextEdit->setDefault(false);
}

void Area::hideText(){
    // get all the subwindows of the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    // hide all the textAreas of those subwindows
    for (QMdiSubWindow* &a: tabs){

       if(this->indicatorEdit->isVisible()){

            QMessageBox::warning(this, "Warning...", "Please save or cancel edition !");
        }
        else{

            ((Area*)a->widget())->textArea->hide();
        }
    }
}

void Area::showText(){
    // get all the subwindows of the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    // show all the textAreas of those subwindows
    for (QMdiSubWindow* &a: tabs){
        ((Area*)a->widget())->textArea->show();
    }
}

void Area::hideTree(){
    // get all the subwindows of the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    // hide all the treeAreas of those subwindows
    for (QMdiSubWindow* &a: tabs){
        ((Area*)a->widget())->treeArea->hide();
    }
}

void Area::showTree(){
    // get all the subwindows of the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    // show all the treeAreas of those subwindows
    for (QMdiSubWindow* &a: tabs){
        ((Area*)a->widget())->treeArea->show();
    }
}

void Area::hideOrShowTree(){
    // get all the subwindows of the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    // if the current treeArea is hidden, all are hidden
    if(!this->treeArea->isHidden()){
        for (QMdiSubWindow* &a: tabs){
            // hide all the trees
            ((Area*)a->widget())->hideTree();
            // change the button
            ((Area*)a->widget())->leftButton->setText(">");
        }
    }
    else  {
        for (QMdiSubWindow* &a: tabs){
            // show all the trees
            ((Area*)a->widget())->showTree();
            // change the button
            ((Area*)a->widget())->leftButton->setText("<");
        }
    }
}

void Area::hideOrShowText(){
    // get all the subwindows in the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    if(!this->textArea->isHidden()){
        // if the current text area is hidden, all are hidden
        for (QMdiSubWindow* &a: tabs){
            // hide all the textAreas
            ((Area*)a->widget())->hideText();
            if(this->textArea->isHidden())
            {
                // change the button
                ((Area*)a->widget())->rightButton->setText("<");
                // hide the button to expand
                ((Area*)a->widget())->rightExpandButton->hide();                
                ((Area*)a->widget())->saveTextEdit->hide();
                ((Area*)a->widget())->cancelTextEdit->hide();
                ((Area*)a->widget())->indicatorEdit->hide();
            }
        }
    }
    else {
        for (QMdiSubWindow* &a: tabs){
            //show all the treeAreas
            ((Area*)a->widget())->showText();
            // change the button
            ((Area*)a->widget())->rightButton->setText(">");
            // show the button to expand
            ((Area*)a->widget())->rightExpandButton->show();            
            ((Area*)a->widget())->saveTextEdit->show();
            ((Area*)a->widget())->cancelTextEdit->show();
            this->editText();
        }
    }
}

void Area::expandOrReduceText(){
    // get all the subwindows in the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    if (this->textArea->maximumWidth() == 200){
        // if this subwindow is not expanded
        for (QMdiSubWindow* &a: tabs){
            // expand it
            ((Area*)a->widget())->textArea->setMaximumWidth(500);
            ((Area*)a->widget())->textArea->setMinimumWidth(500);
            ((Area*)a->widget())->indicatorEdit->setMinimumWidth(500);
            // hide the button to hide
            ((Area*)a->widget())->rightButton->hide();
            // change the button
            ((Area*)a->widget())->rightExpandButton->setText(">");
        }
    }
    else {
        for (QMdiSubWindow* &a: tabs){
            // reduce it
            ((Area*)a->widget())->textArea->setMaximumWidth(200);
            ((Area*)a->widget())->textArea->setMinimumWidth(200);
            ((Area*)a->widget())->indicatorEdit->setMinimumWidth(200);
            // show the button to hide
            ((Area*)a->widget())->rightButton->show();
            // change the button
            ((Area*)a->widget())->rightExpandButton->setText("<");
        }
    }
}

void Area::editText(){

    this->textArea->setNberEdit(0);
    this->setOldText();
}

void Area::cancelEdit(){

    this->indicatorEdit->setVisible(false);
    int i;

    switch(this->typeOfCancel){

        case 0:
            i = 2;
            break;

        case 1:
            i = 1;
            break;

        default:
            return;
    }

    int a = this->listOldText->size()-i;

    //Put the last update into the textArea
    this->textArea->setPlainText(this->listOldText->at(a));

    this->saveEdit();

    this->cancelTextEdit->setDefault(false);
    this->cancelTextEdit->setEnabled(false);

}

void Area::saveEdit(){

    //temporary file for the text edition

    QFile newph("temp.ph");

    newph.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream flux(&newph);
    flux.setCodec("UTF-8");    

    QString *file = new QString("temp.ph");
    std::string phFile = file->toStdString();

    try{

        //Save new text into new file

        flux << this->textArea->toPlainText() << endl;

        newph.close();

        // render graph
        PHPtr myPHPtr = PHIO::parseFile(phFile);
        this->myArea->setPHPtr(myPHPtr);
        myPHPtr->render();
        PHScenePtr scene = myPHPtr->getGraphicsScene();
        this->myArea->setScene(&*scene);

        // delete the current sortsTree
        this->treeArea->sortsTree->clear();
        // set the pointer of the treeArea
        this->treeArea->myPHPtr = myPHPtr;
        //set the pointer of the treeArea
        this->treeArea->myArea = this->myArea;
        // build the tree in the treeArea
        this->treeArea->build();

        this->indicatorEdit->setVisible(false);       
        this->saveTextEdit->setDefault(false);
        this->textArea->incrementeNberTextChange();        
        this->typeOfCancel = 0;
        this->saveTextEdit->setEnabled(false);        
        this->textArea->setNberEdit(0);
        this->cancelTextEdit->setShortcut(QKeySequence());

        this->setOldText();

        newph.remove();
    }
    catch(ph_parse_error & argh){

        //Catch a parsing error !
        //Put the exception into a QMessageBox critical

        QString phc = "phc";
        QStringList args;
        args << "-l" << "dump" << "-i" << QString::fromUtf8(phFile.c_str()) << "--no-debug";
        QProcess *phcProcess = new QProcess();
        phcProcess->start(phc, args);
        if (!phcProcess->waitForStarted())
            throw pint_program_not_found() << file_info("phc");

        // read result
        QByteArray stderr;
        QByteArray stdout;
        while (!phcProcess->waitForFinished()) {
            stderr += phcProcess->readAllStandardError();
            stdout += phcProcess->readAllStandardOutput();
        }
        stderr += phcProcess->readAllStandardError();
        stdout += phcProcess->readAllStandardOutput();
        delete phcProcess;

        //Use split function to only keep the line number

        QStringList list = QString(stderr).split('"');
        QStringList list2 = list[1].split(":");
        QStringList list3 = list2[0].split(" ");

        //One or more of your expressions are wrong !
        newph.remove();
        QMessageBox::critical(this, "Syntax error !", "One or more of your expressions are wrong !\nPlease check "+list3[0]+" "+list3[1]);
        //return NULL;
    }
    catch(sort_not_found& sort){

        //Catch a error if the user delete a sort before associated actions !
//numéro de ligne +
        QMessageBox::critical(this, "Error !", "Delete the associated actions before the process !");
        //this->textArea->undo();
        //this->cancelEdit();
    }
}

void Area::onTextEdit(){

    this->textArea->setUndoRedoEnabled(true);
    this->typeOfCancel = 1;

    if(this->textArea->getNberEdit() == 0){

        this->saveTextEdit->setDefault(false);
        this->indicatorEdit->setVisible(false);        
        this->saveTextEdit->setEnabled(false);
        this->cancelTextEdit->setEnabled(false);
    }
    else{

        this->saveTextEdit->setDefault(true);
        this->indicatorEdit->setVisible(true);        
        this->saveTextEdit->setEnabled(true);
        this->cancelTextEdit->setEnabled(true);
        this->cancelTextEdit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Escape));
        QToolTip::showText(QPoint(850,80), "Press CTRL+E to save or CTRL+ESC to cancel");
    }
}

void Area::setOldText(){

    this->listOldText->insert(this->textArea->getNberTextChange(), this->textArea->toPlainText());
}
