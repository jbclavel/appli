#include "FunctionForm.h"
#include <vector>
#include "ConnectionSettings.h"
#include "MainWindow.h"



std::vector<FuncFrame*> ConnectionSettings::tabFunction;
std::vector< std::vector<ArgumentFrame*>* > ConnectionSettings::tabArgument;
QStringList ConnectionSettings::argTypeList;

FunctionForm::FunctionForm(QString fileName):
    QDialog()
{
    compteurFile=0;
    indexFile=0;
    indexDirec=0;
    pathTab =fileName;

    choix = new QComboBox;

    for (int i=0; i<ConnectionSettings::tabFunction.size();i++ ){
        choix->addItem(ConnectionSettings::tabFunction[i]->getNameFunction());
    }

    Yes = new QPushButton("&Yes");
    Cancel = new QPushButton("&Cancel");
    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(Yes);
    buttonLayout->addWidget(Cancel);

    totalLayout = new QVBoxLayout;
    totalLayout->addWidget(choix);
    totalLayout->addLayout(buttonLayout);

    connect(Yes, SIGNAL(clicked()), this, SLOT(openConnectionForm()));
    connect(Cancel, SIGNAL(clicked()), this, SLOT(quit()));

    setLayout(totalLayout);
    setWindowTitle("Function Form");
    setModal(true);
}

void FunctionForm::quit(){
    choix->~QComboBox();
    Yes->~QPushButton();
    Cancel->~QPushButton();
    buttonLayout->~QHBoxLayout();
    totalLayout->~QVBoxLayout();
    this->~FunctionForm();
}

FunctionForm::~FunctionForm(){}

void FunctionForm::openConnectionForm(){

    //which function has been choosen?
    functionChosen = choix->currentText();

    //destroyers of the previous widgets
    choix->~QComboBox();
    Yes->~QPushButton();
    Cancel->~QPushButton();
    buttonLayout->~QHBoxLayout();

    //which number is the function choosen in the tab?
    for (int i=0; i< ConnectionSettings::tabFunction.size() ; i++ ){
        if(functionChosen == ConnectionSettings::tabFunction[i]->getNameFunction()){
            indexFctChosen = i;
        }
    }

    //How many arguments typed as "File" are there in the arguments of the function choosen?
    for (int i=0; i< ConnectionSettings::tabArgument[indexFctChosen]->size(); i++){
        if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()=="File"){
            compteurFile+=1;
        }
    }

    for(int i=0 ; i< ConnectionSettings::tabFunction[indexFctChosen]->getNbArgument().toInt() ; i++){

        switch(ConnectionSettings::argTypeList.indexOf(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()))
            {
            case 0 :   //"Text"
                {
            tabLineEdit.push_back(new QLineEdit);
            tabNomLine.push_back(new QString(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgNumber()));
            tabQFormLayout.push_back(new QFormLayout);
                tabQFormLayout[i]->addRow(*(tabNomLine[i]) +" (Suffixe : "+
                    ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()+")", tabLineEdit[i]);
            tabQcheckBox.push_back(new QCheckBox("Taken into account"));
            tabQHBox.push_back(new QHBoxLayout);
                tabQHBox[i]->addWidget(tabQcheckBox[i]);
                tabQHBox[i]->addLayout(tabQFormLayout[i]);

            if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgFac()=="0"){ //if argument is not fac
                tabQcheckBox[i]->setChecked(true);
                tabQcheckBox[i]->setEnabled(false);
            }else{
                tabLineEdit[i]->setEnabled(false);
            }
            connect(this->tabQcheckBox[i], SIGNAL(stateChanged(int)), this, SLOT(enableForm(int)));

            tabGroupBox.push_back(new QGroupBox("Specify the "+
                  ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()+" argument : "+
                  ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
            tabGroupBox[i]->setLayout(tabQHBox[i]);
            break;}
            case 1:   //"Entier"
                {
            tabLineEdit.push_back(new QSpinBox);
            tabNomLine.push_back(new QString(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgNumber()));
            tabQFormLayout.push_back(new QFormLayout);
                tabQFormLayout[i]->addRow(*(tabNomLine[i]) +" (Suffixe : "+
                    ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()+")", tabLineEdit[i]);
            tabQcheckBox.push_back(new QCheckBox("Taken into account"));
            tabQHBox.push_back(new QHBoxLayout);
                tabQHBox[i]->addWidget(tabQcheckBox[i]);
                tabQHBox[i]->addLayout(tabQFormLayout[i]);

            if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgFac()=="0"){ //if argument is not fac
                tabQcheckBox[i]->setChecked(true);
                tabQcheckBox[i]->setEnabled(false);
            }else{
                tabLineEdit[i]->setEnabled(false);
            }
            connect(this->tabQcheckBox[i], SIGNAL(stateChanged(int)), this, SLOT(enableForm(int)));

            tabGroupBox.push_back(new QGroupBox("Specify the "+
                  ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()+" argument : "+
                  ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
            tabGroupBox[i]->setLayout(tabQHBox[i]);
            break;}
            case 2:   //"Boolean"
                {
            tabLineEdit.push_back(new QComboBox);
                reinterpret_cast<QComboBox*> (tabLineEdit[i])->addItem("True");
                reinterpret_cast<QComboBox*> (tabLineEdit[i])->addItem("False");
            tabNomLine.push_back(new QString(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgNumber()));
            tabQFormLayout.push_back(new QFormLayout);
                tabQFormLayout[i]->addRow(*(tabNomLine[i]) +" (Suffixe : "+
                    ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()+")", tabLineEdit[i]);
            tabQcheckBox.push_back(new QCheckBox("Taken into account"));
            tabQHBox.push_back(new QHBoxLayout);
                tabQHBox[i]->addWidget(tabQcheckBox[i]);
                tabQHBox[i]->addLayout(tabQFormLayout[i]);

            if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgFac()=="0"){ //if argument is not fac
                tabQcheckBox[i]->setChecked(true);
                tabQcheckBox[i]->setEnabled(false);
            }else{
                tabLineEdit[i]->setEnabled(false);
            }
            connect(this->tabQcheckBox[i], SIGNAL(stateChanged(int)), this, SLOT(enableForm(int)));

            tabGroupBox.push_back(new QGroupBox("Specify the "+
                  ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()+" argument : "+
                  ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
            tabGroupBox[i]->setLayout(tabQHBox[i]);
            break;}
            case 3:   //"Process"
                {
            tabLineEdit.push_back(new QLineEdit);
            tabNomLine.push_back(new QString(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgNumber()));
            tabQFormLayout.push_back(new QFormLayout);
                tabQFormLayout[i]->addRow(*(tabNomLine[i]) +" (Suffixe : "+
                    ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()+")", tabLineEdit[i]);
            tabQcheckBox.push_back(new QCheckBox("Taken into account"));
            tabQHBox.push_back(new QHBoxLayout);
                tabQHBox[i]->addWidget(tabQcheckBox[i]);
                tabQHBox[i]->addLayout(tabQFormLayout[i]);

            if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgFac()=="0"){ //if argument is not fac
                tabQcheckBox[i]->setChecked(true);
                tabQcheckBox[i]->setEnabled(false);
            }else{
                tabLineEdit[i]->setEnabled(false);
            }
            connect(this->tabQcheckBox[i], SIGNAL(stateChanged(int)), this, SLOT(enableForm(int)));


            tabGroupBox.push_back(new QGroupBox("Specify the "+
                  ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()+" argument : "+
                  ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
            tabGroupBox[i]->setLayout(tabQHBox[i]);
            break;}
            case 4:   //"File"
                {
            tabLineEdit.push_back(new QLineEdit);
            tabButtonFile.push_back(new QPushButton("Browse"));
            connect(tabButtonFile[indexFile], SIGNAL(clicked()), this, SLOT(getName()));

            tabNomLine.push_back(new QString(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgNumber()));
            tabQFormLayout.push_back(new QFormLayout);
                tabQFormLayout[i]->addRow(*(tabNomLine[i]) +" (Suffixe : "+
                    ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()+")", tabLineEdit[i]);
            tabQcheckBox.push_back(new QCheckBox("Taken into account"));
            tabQHBox.push_back(new QHBoxLayout);
                tabQHBox[i]->addWidget(tabQcheckBox[i]);
                tabQHBox[i]->addLayout(tabQFormLayout[i]);
                tabQHBox[i]->addWidget(tabButtonFile[indexFile]);

            if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgFac()=="0"){ //if argument is not fac
                tabQcheckBox[i]->setChecked(true);
                tabQcheckBox[i]->setEnabled(false);
            }else{
                tabLineEdit[i]->setEnabled(false);
                tabButtonFile[indexFile]->setEnabled(false);
            }
            connect(this->tabQcheckBox[i], SIGNAL(stateChanged(int)), this, SLOT(enableForm(int)));

            tabGroupBox.push_back(new QGroupBox("Specify the "+
                  ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()+" argument : "+
                  ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
            tabGroupBox[i]->setLayout(tabQHBox[i]);

            indexFile+=1;
            break;}
            case 5:   //"Folder"
                {
            tabLineEdit.push_back(new QLineEdit);
            tabButtonDirec.push_back(new QPushButton("Browse"));
            connect(tabButtonDirec[indexDirec], SIGNAL(clicked()), this, SLOT(getDirectoryName()));

            tabNomLine.push_back(new QString(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgNumber()));
            tabQFormLayout.push_back(new QFormLayout);
                tabQFormLayout[i]->addRow(*(tabNomLine[i]) +" (Suffixe : "+
                    ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()+")", tabLineEdit[i]);
            tabQcheckBox.push_back(new QCheckBox("Taken into account"));
            tabQHBox.push_back(new QHBoxLayout);
                tabQHBox[i]->addWidget(tabQcheckBox[i]);
                tabQHBox[i]->addLayout(tabQFormLayout[i]);
                tabQHBox[i]->addWidget(tabButtonDirec[indexDirec]);

            if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgFac()=="0"){ //if argument is not fac
                tabQcheckBox[i]->setChecked(true);
                tabQcheckBox[i]->setEnabled(false);
            }else{
                tabLineEdit[i]->setEnabled(false);
                tabButtonDirec[indexDirec]->setEnabled(false);
            }
            connect(this->tabQcheckBox[i], SIGNAL(stateChanged(int)), this, SLOT(enableForm(int)));

            tabGroupBox.push_back(new QGroupBox("Specify the "+
                  ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()+" argument : "+
                  ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
            tabGroupBox[i]->setLayout(tabQHBox[i]);

            indexDirec+=1;

            break;}
            case 6:   //"Choix"
                {
            tabLineEdit.push_back(new QLineEdit);
            tabNomLine.push_back(new QString(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgNumber()));
            tabQFormLayout.push_back(new QFormLayout);
                tabQFormLayout[i]->addRow(*(tabNomLine[i]) +" (Suffixe : "+
                    ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()+")", tabLineEdit[i]);
            tabQcheckBox.push_back(new QCheckBox("Taken into account"));
            tabQHBox.push_back(new QHBoxLayout);
                tabQHBox[i]->addWidget(tabQcheckBox[i]);
                tabQHBox[i]->addLayout(tabQFormLayout[i]);

            if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgFac()=="0"){ //if argument is not fac
                tabQcheckBox[i]->setChecked(true);
                tabQcheckBox[i]->setEnabled(false);
            }else{
                tabLineEdit[i]->setEnabled(false);
            }
            connect(this->tabQcheckBox[i], SIGNAL(stateChanged(int)), this, SLOT(enableForm(int)));

            tabGroupBox.push_back(new QGroupBox("Specify the "+
                  ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()+" argument : "+
                  ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
            tabGroupBox[i]->setLayout(tabQHBox[i]);
            break;}
            }
        totalLayout->addWidget(tabGroupBox[i]);
        }

    Ok = new QPushButton("&Ok");
    back = new QPushButton("&Back");
    buttonLayout2 = new QHBoxLayout;
    buttonLayout2->addWidget(Ok);
    buttonLayout2->addWidget(back);
    totalLayout->addLayout(buttonLayout2);

    connect(Ok, SIGNAL(clicked()), this, SLOT(launchCompute()));
    connect(back, SIGNAL(clicked()), this, SLOT(fctBack()));
}


void FunctionForm::fctBack(){

    for(int i=tabGroupBox.size(); i>0; i--){
        tabLineEdit[i-1]->~QWidget();
        tabNomLine[i-1]->~QString();
        tabQFormLayout[i-1]->~QFormLayout();
        tabQcheckBox[i-1]->~QCheckBox();
        for(int j=tabButtonFile.size(); j>0; j--){
            tabButtonFile[j-1]->~QPushButton();
            tabButtonFile.pop_back();
        }
        for(int j=tabButtonDirec.size(); j>0; j--){
            tabButtonDirec[j-1]->~QPushButton();
            tabButtonDirec.pop_back();
        }
        tabQHBox[i-1]->~QHBoxLayout();
        tabGroupBox[i-1]->~QGroupBox();

        tabLineEdit.pop_back();
        tabNomLine.pop_back();
        tabQFormLayout.pop_back();
        tabQcheckBox.pop_back();
        tabQHBox.pop_back();
        tabGroupBox.pop_back();
    }


    compteurFile=0;
    indexFile=0;
    indexDirec=0;


        Ok->~QPushButton();
        back->~QPushButton();
        buttonLayout2->~QHBoxLayout();

        //re-build the former window
        choix = new QComboBox;

        for (int i=0; i<ConnectionSettings::tabFunction.size();i++ ){
            choix->addItem(ConnectionSettings::tabFunction[i]->getNameFunction());
        }

        Yes = new QPushButton("&Yes");
        Cancel = new QPushButton("&Cancel");
        buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(Yes);
        buttonLayout->addWidget(Cancel);

        totalLayout->addWidget(choix);
        totalLayout->addLayout(buttonLayout);

        connect(Yes, SIGNAL(clicked()), this, SLOT(openConnectionForm()));
        connect(Cancel, SIGNAL(clicked()), this, SLOT(quit()));

}

void FunctionForm::launchCompute(){

    int reponse = QMessageBox::question(this, "Connection Settings validation", "Do you really want to launch the function with these settings ?",
                            QMessageBox::No | QMessageBox::Yes);

    if (reponse == QMessageBox::Yes)
        {
        QString program = ConnectionSettings::tabFunction[indexFctChosen]->getProgram();
                //"ph-reach";
        QStringList arguments;


        /*
        if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgFac()=="false"){
            tabQcheckBox[i]->setChecked("true");
            tabQcheckBox[i]->setEnabled("false");
        }
  */

        arguments << "--no-debug" << "-i" << pathTab << "a" << "1" ;

        //MainWindow::mwThis->compute(program, arguments, pathTab);

        //destroyers
        for(int i=tabGroupBox.size(); i>0; i--){
            tabLineEdit[i-1]->~QWidget();
            tabNomLine[i-1]->~QString();
            tabQFormLayout[i-1]->~QFormLayout();
            tabQcheckBox[i-1]->~QCheckBox();
            for(int j=tabButtonFile.size(); j>0; j--){
                tabButtonFile[j-1]->~QPushButton();
                tabButtonFile.pop_back();
            }
            for(int j=tabButtonDirec.size(); j>0; j--){
                tabButtonDirec[j-1]->~QPushButton();
                tabButtonDirec.pop_back();
            }
            tabQHBox[i-1]->~QHBoxLayout();
            tabGroupBox[i-1]->~QGroupBox();

            tabLineEdit.pop_back();
            tabNomLine.pop_back();
            tabQFormLayout.pop_back();
            tabQcheckBox.pop_back();
            tabQHBox.pop_back();
            tabGroupBox.pop_back();

        }
        compteurFile=0;
        indexFile=0;
        indexDirec=0;

        Ok->~QPushButton();
        back->~QPushButton();
        buttonLayout2->~QHBoxLayout();
        totalLayout->~QVBoxLayout();
        this->~FunctionForm();

    }
}

//slot
void FunctionForm::enableForm(int state){
    for(int i =0; i<ConnectionSettings::tabFunction[indexFctChosen]->getNbArgument().toInt() ; i++){
        if(tabQcheckBox[i]->isChecked()){
            tabLineEdit[i]->setEnabled(true);
            //File
            int compteur =0;
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()=="File"){
                    for(int j=0; j<i;j++){
                        if(ConnectionSettings::tabArgument[indexFctChosen]->at(j)->getArgType()=="File"){
                            compteur +=1;
                        }
                    }
                tabButtonFile[compteur]->setEnabled(true);
                compteur=0;
                }
            //Directory
            int compteurDir =0;
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()=="Folder"){
                    for(int j=0; j<i;j++){
                        if(ConnectionSettings::tabArgument[indexFctChosen]->at(j)->getArgType()=="Folder"){
                            compteurDir +=1;
                        }
                    }
            tabButtonDirec[compteurDir]->setEnabled(true);
            compteurDir=0;
            }
        }else{
            tabLineEdit[i]->setEnabled(false);
            //File
            int compteur =0;
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()=="File"){
                    for(int j=0; j<i;j++){
                        if(ConnectionSettings::tabArgument[indexFctChosen]->at(j)->getArgType()=="File"){
                            compteur +=1;
                        }
                    }
                tabButtonFile[compteur]->setEnabled(false);
                compteur=0;
                }
            //directory
            int compteurDir =0;
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()=="Folder"){
                    for(int j=0; j<i;j++){
                        if(ConnectionSettings::tabArgument[indexFctChosen]->at(j)->getArgType()=="Folder"){
                            compteurDir +=1;
                        }
                    }
                tabButtonDirec[compteurDir]->setEnabled(false);
                compteurDir=0;
                }
            }
    }
}



void FunctionForm::getName(){
    QString a;
    a = QFileDialog::getOpenFileName(this,tr("Open Image"), "/home/", tr("All Files (*.ph)"));

    int num;
    for(int i=0; i<tabButtonFile.size(); i++){
        if(tabButtonFile[i]==QObject::sender()){
            num=i;
        }
    }

    int now=0;
    while(num!=-1){
        if(ConnectionSettings::tabArgument[indexFctChosen]->at(now)->getArgType()=="File"){
            num-=1;
        }
        now+=1;
    }
    reinterpret_cast<QLineEdit*>(tabLineEdit[now-1])->setText(a);
}


void FunctionForm::getDirectoryName(){

    //QFileDialog* direcDialog = new QFileDialog(this);

    //direcDialog->setMode(QFileDialog::ShowDirsOnly);
    //direcDialog->exec();

    //QWidget *parent = 0,
      //                                 const QString &caption = QString(),
        //                               const QString &dir = QString(),
          //                             const QString &filter = QString(),
      //                                 QString *selectedFilter = 0,
        //                               Options options = 0);

    //QString a;
    //direcDialog->

    QString a;
    //QFileDialog file_dialog();
    a = QFileDialog::getOpenFileName(this,tr("Open Image"), "/home/", tr("All Files (*.ph)"),0, QFileDialog::ShowDirsOnly);
/*

getExistingDirectory(QWidget *parent = 0,
                                        const QString &caption = QString(),
                                        const QString &dir = QString(),
                                        Options options = ShowDirsOnly);




int num;
    for(int i=0; i<tabButtonFile.size(); i++){
        if(tabButtonFile[i]==QObject::sender()){
            num=i;
        }*/
    }
/*
    int now=0;
    while(num!=-1){
        if(ConnectionSettings::tabArgument[indexFctChosen]->at(now)->getArgType()=="File"){
            num-=1;
        }
        now+=1;
    }
    reinterpret_cast<QLineEdit*>(tabLineEdit[now-1])->setText(a);*/


/*
void FunctionForm::change(int largeur)
{
    setFixedSize(largeur, height());

    if (largeur == 600)
    {
        emit agrandissementMax();
    }
}*/
/*
//slot called when the save button is triggered
void ConnectionSettings::validationConnectionSettings(){

    int reponse = QMessageBox::question(this, "Connection Settings validation", "Do you really want to save these settings ?",
                            QMessageBox::No | QMessageBox::Yes);

    if (reponse == QMessageBox::Yes)
        {
            exportXMLSettings();
            QMessageBox::information(this, "Connection Setting Validated", "Export done");
            this->quit();
        }
}

//QMessageBox::critical(this, "Error", "No file opened!");
*/


