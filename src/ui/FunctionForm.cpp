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

            //fileName = QFileDialog::getOpenFileName(this,
            //tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
            //QFileDialog* filedialog = new QFileDialog(this);

            //QDialog* mb = new QDialog(filedialog);

            tabLineEdit.push_back(new QLineEdit);

            connect(this->tabLineEdit[i], SIGNAL(textEdited(QString)), this, SLOT(fctBack()));


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
            case 5:   //"Folder"
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

        MainWindow::mwThis->compute(program, arguments, pathTab);

        //destroyers
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
            this->~FunctionForm();

    }
}

//slot
void FunctionForm::enableForm(int state){
    for(int i =0; i<ConnectionSettings::tabFunction[indexFctChosen]->getNbArgument().toInt() ; i++){
        if(tabQcheckBox[i]->isChecked()){
            tabLineEdit[i]->setEnabled(true);
        }else{
            tabLineEdit[i]->setEnabled(false);
        }
    }
}

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


