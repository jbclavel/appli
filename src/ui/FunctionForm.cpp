#include "FunctionForm.h"
#include <vector>
#include "ConnectionSettings.h"
#include "MainWindow.h"


std::vector<FuncFrame*> ConnectionSettings::tabFunction;
std::vector< std::vector<ArgumentFrame*>* > ConnectionSettings::tabArgument;
QStringList ConnectionSettings::argTypeList;

FunctionForm::FunctionForm():
    QWidget()
{
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

}

void FunctionForm::quit(){

    choix->~QComboBox();
    Yes->~QPushButton();
    Cancel->~QPushButton();
    buttonLayout->~QHBoxLayout();
    this->~FunctionForm();

}

FunctionForm::~FunctionForm(){
    }


void FunctionForm::openConnectionForm(){

    functionChosen = choix->currentText();
    choix->~QComboBox();
    Yes->~QPushButton();
    Cancel->~QPushButton();
    buttonLayout->~QHBoxLayout();

    for (int i=0; i< ConnectionSettings::tabFunction.size() ; i++ ){
        if(functionChosen == ConnectionSettings::tabFunction[i]->getNameFunction()){
            indexFctChosen = i;

        }
    }


    for(int i=0 ; i< ConnectionSettings::tabFunction[indexFctChosen]->getNbArgument().toInt() ; i++){

        switch(ConnectionSettings::argTypeList.indexOf(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()))
            {
            case 0 :   //text
                {
            tabLineEdit.push_back(new QLineEdit);
            tabNomLine.push_back(new QString(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgNumber()));
            tabQFormLayout.push_back(new QFormLayout);
            tabQFormLayout[i]->addRow(*(tabNomLine[i]) +" (Suffixe : "+
                                      ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()
                                      +")", tabLineEdit[i]);

            tabGroupBox.push_back(new QGroupBox("Specify the "+
                                      ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                                          +" argument : "+
                                      ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));

            tabGroupBox[i]->setLayout(tabQFormLayout[i]);

            break;}
            case 1:   //process
                {
            tabLineEdit.push_back(new QLineEdit);
            tabNomLine.push_back(new QString(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgNumber()));
            tabQFormLayout.push_back(new QFormLayout);
            tabQFormLayout[i]->addRow(*(tabNomLine[i]) +" (Suffixe : "+
                                      ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()
                                      +")", tabLineEdit[i]);

            tabGroupBox.push_back(new QGroupBox("Specify the "+
                                      ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                                          +" argument : "+
                                      ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));

            tabGroupBox[i]->setLayout(tabQFormLayout[i]);

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
        tabQFormLayout[i-1]->~QFormLayout();
        tabGroupBox[i-1]->~QGroupBox();
        tabNomLine[i-1]->~QString();

        tabLineEdit.pop_back();
        tabQFormLayout.pop_back();
        tabGroupBox.pop_back();
        tabNomLine.pop_back();
    }

        Ok->~QPushButton();
        back->~QPushButton();
        buttonLayout2->~QHBoxLayout();
        totalLayout->~QVBoxLayout();

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

        totalLayout = new QVBoxLayout;
        totalLayout->addWidget(choix);
        totalLayout->addLayout(buttonLayout);

        connect(Yes, SIGNAL(clicked()), this, SLOT(openConnectionForm()));
        connect(Cancel, SIGNAL(clicked()), this, SLOT(quit()));

        setLayout(totalLayout);

}

void FunctionForm::launchCompute(){

    QString program ="ph-reach";
    QStringList arguments;

    arguments << "--no-debug" << "-i" << MainWindow::fileName << "a" << "1" ;



    MainWindow::compute(program, arguments, MainWindow::fileName);

}

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


