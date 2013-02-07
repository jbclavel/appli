#include "Area.h"
#include "QHBoxLayout"
#include "PHIO.h"
#include "IO.h"

Area::Area(QWidget *parent, QString path) :
    QWidget(parent)
{
    this->path = path;

    // call the constructors of all the areas
    this->textArea = new TextArea(this);
    this->textArea->setReadOnly(true);
    this->myArea = new MyArea(this, this->path);
    this->treeArea = new TreeArea(this);

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

    this->editTextArea = new QPushButton("Edit text",this);
    this->editTextArea->setFixedSize(QSize(200,30));

    this->saveTextEdit = new QPushButton("Save",this);
    this->saveTextEdit->setFixedSize(QSize(80,30));
    this->saveTextEdit->setVisible(false);

    this->cancelTextEdit = new QPushButton("Cancel",this);
    this->cancelTextEdit->setFixedSize(QSize(80,30));
    this->cancelTextEdit->setVisible(false);

    // set the global layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(this->treeArea);
    layout->addWidget(this->treeButtonArea);
    layout->addWidget(this->myArea);
    layout->addWidget(this->textButtonArea);    

    QVBoxLayout *VLayout = new QVBoxLayout;
    VLayout->addWidget(this->textArea);
    VLayout->addWidget(this->editTextArea);

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
    QObject::connect(this->editTextArea, SIGNAL(clicked()), this, SLOT(editText()));
    QObject::connect(this->cancelTextEdit, SIGNAL(clicked()), this, SLOT(cancelEdit()));
    QObject::connect(this->textArea, SIGNAL(textChanged()), this->textArea, SLOT(onTextEdit()));
    QObject::connect(this->saveTextEdit, SIGNAL(clicked()), this, SLOT(saveEdit()));

}

void Area::hideText(){
    // get all the subwindows of the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    // hide all the textAreas of those subwindows
    for (QMdiSubWindow* &a: tabs){
        ((Area*)a->widget())->textArea->hide();

        if(!this->editTextArea->isVisible()){

            this->cancelEdit();
        }

        ((Area*)a->widget())->editTextArea->hide();
    }
}

void Area::showText(){
    // get all the subwindows of the central area
    QList<QMdiSubWindow*> tabs = this->mainWindow->getCentraleArea()->subWindowList();
    // show all the textAreas of those subwindows
    for (QMdiSubWindow* &a: tabs){
        ((Area*)a->widget())->textArea->show();
        ((Area*)a->widget())->editTextArea->show();
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
            // change the button
            ((Area*)a->widget())->rightButton->setText("<");
            // hide the button to expand
            ((Area*)a->widget())->rightExpandButton->hide();
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
            // show the button to hide
            ((Area*)a->widget())->rightButton->show();
            // change the button
            ((Area*)a->widget())->rightExpandButton->setText("<");
        }
    }
}

void Area::editText(){

    this->textArea->setReadOnly(false);
    this->editTextArea->setVisible(false);
    this->saveTextEdit->setVisible(true);
    this->cancelTextEdit->setVisible(true);

    this->textArea->setNberEdit(0);
    //this->textArea->insertHtml("<p style='color:green;position:absolute;top:0px;'>Edit...</p><br/><br/>");
}

void Area::cancelEdit(){

    this->textArea->setUndoRedoEnabled(true);

    for(int i = 0; i < this->textArea->getNberEdit(); i++){

        this->textArea->undo();
    }

    this->textArea->setNberEdit(0);

    this->textArea->setReadOnly(true);
    this->editTextArea->setVisible(true);
    this->saveTextEdit->setVisible(false);
    this->cancelTextEdit->setVisible(false);

}

void Area::saveEdit(){

    this->textArea->setUndoRedoEnabled(false);
    this->textArea->setReadOnly(true);
    this->editTextArea->setVisible(true);
    this->saveTextEdit->setVisible(false);
    this->cancelTextEdit->setVisible(false);

    //this->textArea->setNberEdit(0);

    QFile newph(this->path);

    newph.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream flux(&newph);
    flux.setCodec("UTF-8");

    flux << this->textArea->toPlainText() << endl;

}
