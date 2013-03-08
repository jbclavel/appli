#include "FunctionForm.h"
#include <vector>
#include "ConnectionSettings.h"
#include "MainWindow.h"



std::vector<FuncFrame*> ConnectionSettings::tabFunction;
std::vector< std::vector<ArgumentFrame*>* > ConnectionSettings::tabArgument;
std::vector< std::vector< std::vector<ChoixLigne*>*>*> ConnectionSettings::tabChoix;

QStringList ConnectionSettings::argTypeList;

FunctionForm::FunctionForm(QString fileName):
    QDialog()
{
    indexFilePH=0;
    indexFile=0;
    indexDirec=0;
    pathTab =fileName;

    choix = new QComboBox;

    for (int i=0; i<(int)ConnectionSettings::tabFunction.size();i++ ){
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

    //ajout du scroll
    widget = new QWidget;
    widget->setLayout(totalLayout);
    area = new QScrollArea;
    area->setWidget(widget);
    area->setWidgetResizable(true);

    layoutTotal = new QVBoxLayout;
    layoutTotal->addWidget(area);


    setLayout(layoutTotal);
    setWindowTitle("Function Form");
    setModal(true);
    resize(600,200);
}

void FunctionForm::quit(){
    choix->~QComboBox();
    Yes->~QPushButton();
    Cancel->~QPushButton();
    buttonLayout->~QHBoxLayout();
    totalLayout->~QVBoxLayout();
    widget->~QWidget();
    area->~QScrollArea();
    layoutTotal->~QVBoxLayout();

    this->~FunctionForm();
}

FunctionForm::~FunctionForm(){}

void FunctionForm::openConnectionForm(){

    resize(800,500);

    //which function has been choosen?
    functionChosen = choix->currentText();

    //destroyers of the previous widgets
    choix->~QComboBox();
    Yes->~QPushButton();
    Cancel->~QPushButton();
    buttonLayout->~QHBoxLayout();

    //which number is the function choosen in the tab?
    for (int i=0; i< (int)ConnectionSettings::tabFunction.size() ; i++ ){
        if(functionChosen == ConnectionSettings::tabFunction[i]->getNameFunction()){
            indexFctChosen = i;
        }
    }
    //in case there is no argument to launch the function
    if(ConnectionSettings::tabFunction[indexFctChosen]->getNbArgument()=="0"){
        this->launchCompute();
    }else{

    //for each argument of the chosen function, create fields as per the argument type
    for(int i=0 ; i< ConnectionSettings::tabFunction[indexFctChosen]->getNbArgument().toInt() ; i++){

        switch(ConnectionSettings::argTypeList.indexOf(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()))
            {
            case 0 :   //"Text"
                {
                tabLineEdit.push_back(new QLineEdit);

                tabQFormLayout.push_back(new QFormLayout);
                    if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                        tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                    }else{
                        tabQFormLayout[i]->addRow("Prefixe : "+
                            ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf(), tabLineEdit[i]);
                    }

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

                tabGroupBox.push_back(new QGroupBox("Argument "+ QString::number(i+1)+
                                    +" : (Type : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                                    +") Caption : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
                tabGroupBox[i]->setLayout(tabQHBox[i]);
            break;}
            case 1:   //"Integer"
                {
                tabLineEdit.push_back(new QSpinBox);
                reinterpret_cast<QSpinBox*>(tabLineEdit[i])->setMaximum(10000);

                tabQFormLayout.push_back(new QFormLayout);
                    if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                        tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                    }else{
                        tabQFormLayout[i]->addRow("Prefixe : "+
                            ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf(), tabLineEdit[i]);
                    }
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

                tabGroupBox.push_back(new QGroupBox("Argument "+ QString::number(i+1)+
                                    +" : (Type : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                                    +") Caption : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
                tabGroupBox[i]->setLayout(tabQHBox[i]);
            break;}
        case 2:   //"Real"
            {
            tabLineEdit.push_back(new QDoubleSpinBox);
            reinterpret_cast<QDoubleSpinBox*>(tabLineEdit[i])->setDecimals(15);
            reinterpret_cast<QDoubleSpinBox*>(tabLineEdit[i])->setRange(-10000,10000);

            tabQFormLayout.push_back(new QFormLayout);
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                    tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                }else{
                    tabQFormLayout[i]->addRow("Prefixe : "+
                        ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf(), tabLineEdit[i]);
                }
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

            tabGroupBox.push_back(new QGroupBox("Argument "+ QString::number(i+1)+
                                +" : (Type : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                                +") Caption : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
            tabGroupBox[i]->setLayout(tabQHBox[i]);
        break;}
            case 3:   //"Boolean"
                {
                tabLineEdit.push_back(new QComboBox);
                    reinterpret_cast<QComboBox*> (tabLineEdit[i])->addItem("True");
                    reinterpret_cast<QComboBox*> (tabLineEdit[i])->addItem("False");

                tabQFormLayout.push_back(new QFormLayout);
                    if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                        tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                    }else{
                        tabQFormLayout[i]->addRow("Prefixe : "+
                            ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf(), tabLineEdit[i]);
                    }
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

                tabGroupBox.push_back(new QGroupBox("Argument "+ QString::number(i+1)+
                                    +" : (Type : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                                    +") Caption : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
                tabGroupBox[i]->setLayout(tabQHBox[i]);
            break;}
            case 4:   //"Process List"
                {
                tabLineEdit.push_back(new QLineEdit);

                tabQFormLayout.push_back(new QFormLayout);
                    if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                        tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                    }else{
                        tabQFormLayout[i]->addRow("Prefixe : "+
                            ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf(), tabLineEdit[i]);
                    }
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


                tabGroupBox.push_back(new QGroupBox("Argument "+ QString::number(i+1)+
                                    +" : (Type : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                                    +") Caption : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
                tabGroupBox[i]->setLayout(tabQHBox[i]);
            break;}
        case 5:   //"Process Group"
            {
            tabLineEdit.push_back(new QLineEdit);

            tabQFormLayout.push_back(new QFormLayout);
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                    tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                }else{
                    tabQFormLayout[i]->addRow("Prefixe : "+
                        ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf(), tabLineEdit[i]);
                }
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


            tabGroupBox.push_back(new QGroupBox("Argument "+ QString::number(i+1)+
                                +" : (Type : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                                +") Caption : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
            tabGroupBox[i]->setLayout(tabQHBox[i]);
        break;}

        case 6:   //"File .ph"
                {
                tabLineEdit.push_back(new QLineEdit);
                tabButtonFilePH.push_back(new QPushButton("Browse"));
                connect(tabButtonFilePH[indexFilePH], SIGNAL(clicked()), this, SLOT(getNamePH()));


                tabQFormLayout.push_back(new QFormLayout);
                    if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                        tabQFormLayout[i]->addRow("Without any Prefix", tabLineEdit[i]);
                    }else{
                        tabQFormLayout[i]->addRow("Prefixe : "+
                            ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf(), tabLineEdit[i]);
                    }
                tabQcheckBox.push_back(new QCheckBox("Taken into account"));
                tabQHBox.push_back(new QHBoxLayout);
                    tabQHBox[i]->addWidget(tabQcheckBox[i]);
                    tabQHBox[i]->addLayout(tabQFormLayout[i]);
                    tabQHBox[i]->addWidget(tabButtonFilePH[indexFilePH]);

                    if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgFac()=="0"){ //if argument is not fac
                        tabQcheckBox[i]->setChecked(true);
                        tabQcheckBox[i]->setEnabled(false);
                    }else{
                        tabLineEdit[i]->setEnabled(false);
                        tabButtonFilePH[indexFilePH]->setEnabled(false);
                    }
                connect(this->tabQcheckBox[i], SIGNAL(stateChanged(int)), this, SLOT(enableForm(int)));

                tabGroupBox.push_back(new QGroupBox("Argument "+ QString::number(i+1)+
                                    +" : (Type : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                                    +") Caption : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
                tabGroupBox[i]->setLayout(tabQHBox[i]);

                indexFilePH+=1;
            break;}
        case 7:   //"File"
            {
            tabLineEdit.push_back(new QLineEdit);
            tabButtonFile.push_back(new QPushButton("Browse"));
            connect(tabButtonFile[indexFile], SIGNAL(clicked()), this, SLOT(getName()));


            tabQFormLayout.push_back(new QFormLayout);
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                    tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                }else{
                    tabQFormLayout[i]->addRow("Prefixe : "+
                        ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf(), tabLineEdit[i]);
                }
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

            tabGroupBox.push_back(new QGroupBox("Argument "+ QString::number(i+1)+
                                +" : (Type : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                                +") Caption : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
            tabGroupBox[i]->setLayout(tabQHBox[i]);

            indexFile+=1;
        break;}

        case 8:   //"Folder"
                {
                tabLineEdit.push_back(new QLineEdit);
                tabButtonDirec.push_back(new QPushButton("Browse"));
                connect(tabButtonDirec[indexDirec], SIGNAL(clicked()), this, SLOT(getDirectoryName()));


                tabQFormLayout.push_back(new QFormLayout);
                    if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                        tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                    }else{
                        tabQFormLayout[i]->addRow("Prefixe : "+
                            ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf(), tabLineEdit[i]);
                    }
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

                tabGroupBox.push_back(new QGroupBox("Argument "+ QString::number(i+1)+
                                    +" : (Type : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                                    +") Caption : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
                tabGroupBox[i]->setLayout(tabQHBox[i]);

                indexDirec+=1;
            break;}
            case 9:   //"Choice"
                {
                tabLineEdit.push_back(new QComboBox);
                for(int m=0; m<ConnectionSettings::tabChoix[indexFctChosen]->at(i)->size() ; m++){
                    reinterpret_cast<QComboBox*>(tabLineEdit[i])->addItem(ConnectionSettings::tabChoix[indexFctChosen]->at(i)->at(m)->getChoixNom());
                }

                tabQFormLayout.push_back(new QFormLayout);
                tabQFormLayout[i]->addRow("Choice : ", tabLineEdit[i]);

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

                tabGroupBox.push_back(new QGroupBox("Argument "+ QString::number(i+1)+
                                    +" : (Type : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                                    +") Caption : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
                tabGroupBox[i]->setLayout(tabQHBox[i]);
            break;}
        case 10:   //"File not existing"
            {
            tabLineEdit.push_back(new QLineEdit);

            tabQFormLayout.push_back(new QFormLayout);
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                    tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                }else{
                    tabQFormLayout[i]->addRow("Prefixe : "+
                        ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf(), tabLineEdit[i]);
                }

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

            tabGroupBox.push_back(new QGroupBox("Argument "+ QString::number(i+1)+
                                +" : (Type : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                                +") Caption : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
            tabGroupBox[i]->setLayout(tabQHBox[i]);
        break;}
        case 11:   //"Necessary argument"
            {
            tabLineEdit.push_back(new QLineEdit);
            reinterpret_cast<QLineEdit*>(tabLineEdit[i])->setText(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf());
            tabLineEdit[i]->setEnabled(false);

            tabQFormLayout.push_back(new QFormLayout);
            tabQFormLayout[i]->addRow("Mandatory Argument : ", tabLineEdit[i]);

            tabQcheckBox.push_back(new QCheckBox("Taken into account"));
            tabQHBox.push_back(new QHBoxLayout);
                tabQHBox[i]->addWidget(tabQcheckBox[i]);
                tabQHBox[i]->addLayout(tabQFormLayout[i]);


            tabQcheckBox[i]->setChecked(true);
            tabQcheckBox[i]->setEnabled(false);

            connect(this->tabQcheckBox[i], SIGNAL(stateChanged(int)), this, SLOT(enableForm(int)));

            tabGroupBox.push_back(new QGroupBox("Argument "+ QString::number(i+1)+
                                +" : (Type : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                                +") Caption : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
            tabGroupBox[i]->setLayout(tabQHBox[i]);
        break;}
        case 12:   //"Current File"
            {
            tabLineEdit.push_back(new QLineEdit);
            reinterpret_cast<QLineEdit*>(tabLineEdit[i])->setText(MainWindow::mwThis->pathCurrentWindow());
            tabLineEdit[i]->setEnabled(false);

            tabQFormLayout.push_back(new QFormLayout);
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                    tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                }else{
                    tabQFormLayout[i]->addRow("Prefixe : "+
                        ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf(), tabLineEdit[i]);
                }

            tabQcheckBox.push_back(new QCheckBox("Taken into account"));
            tabQHBox.push_back(new QHBoxLayout);
                tabQHBox[i]->addWidget(tabQcheckBox[i]);
                tabQHBox[i]->addLayout(tabQFormLayout[i]);

            tabQcheckBox[i]->setChecked(true);
            tabQcheckBox[i]->setEnabled(false);

            connect(this->tabQcheckBox[i], SIGNAL(stateChanged(int)), this, SLOT(enableForm(int)));

            tabGroupBox.push_back(new QGroupBox("Argument "+ QString::number(i+1)+
                                +" : (Type : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                                +") Caption : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
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

    connect(Ok, SIGNAL(clicked()), this, SLOT(testEmpty()));
    connect(back, SIGNAL(clicked()), this, SLOT(fctBack()));
}
}


void FunctionForm::fctBack(){

    for(int i=tabGroupBox.size(); i>0; i--){
        tabLineEdit[i-1]->~QWidget();

        tabQFormLayout[i-1]->~QFormLayout();
        tabQcheckBox[i-1]->~QCheckBox();
        for(int j=tabButtonFilePH.size(); j>0; j--){
            tabButtonFilePH[j-1]->~QPushButton();
            tabButtonFilePH.pop_back();
        }
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

        tabQFormLayout.pop_back();
        tabQcheckBox.pop_back();
        tabQHBox.pop_back();
        tabGroupBox.pop_back();
    }

    indexFilePH=0;
    indexFile=0;
    indexDirec=0;


        Ok->~QPushButton();
        back->~QPushButton();
        buttonLayout2->~QHBoxLayout();

        resize(600,200);

        //re-build the former window
        choix = new QComboBox;

        for (int i=0; i<(int)ConnectionSettings::tabFunction.size();i++ ){
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

    int reponse = QMessageBox::question(this, "Connection Settings validation", "Do you really want to launch the function (check settings if there is...)  ?",
                            QMessageBox::No | QMessageBox::Yes);

    if (reponse == QMessageBox::Yes){
        QString program = ConnectionSettings::tabFunction[indexFctChosen]->getProgram();

        QStringList arguments;

<<<<<<< HEAD
        for(int i=0; i<(int)ConnectionSettings::tabArgument[indexFctChosen]->size(); i++){
=======
        for(int i=0; i<ConnectionSettings::tabArgument[indexFctChosen]->size(); i++){
            if(tabQcheckBox[i]->isChecked()){
>>>>>>> 5c521088e8f570448a0503ed2f62e52d8582cfbe
            switch(ConnectionSettings::argTypeList.indexOf(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()))
                {
            case 0 : //"Text"
            case 1 : //"Integer"
            case 2 : //"Real"
            case 6 : //"File .ph"
            case 7 : //"File"
            case 8 : //"Folder"
            case 10 : //"File not existing"
            case 11 : //"Necessary argument"
            case 12 : //"Current File"
            {
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()!=""){
                    arguments << ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf();
                }
                arguments  << reinterpret_cast<QLineEdit*>(tabLineEdit[i])->text();
            break;
            }
            case 3 : //"Boolean
            {
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()!=""){
                    arguments << ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf();
                }
            arguments << reinterpret_cast<QComboBox*>(tabLineEdit[i])->currentText();
            break;
            }
            case 4 : //"Process List"
            {
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()!=""){
                    arguments << ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf();
                }

            QStringList a = MainWindow::mwThis->wordList(reinterpret_cast<QLineEdit*>(tabLineEdit[i])->text());

            for (int j=0; j< a.size(); j++){
                    arguments << a[j];
                }
            break;
            }
            case 5 : //"Process Group"
            {
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()!=""){
                    arguments << ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf();
                }
            QStringList a = MainWindow::mwThis->wordList(reinterpret_cast<QLineEdit*>(tabLineEdit[i])->text());
            QString mot;//= """";
            int compteur = 0;
            for (int j=0; j< a.size(); j++){
                if(compteur %2 ==0){
                    mot += a[j] +" ";
                    compteur+=1;
                }else{
                    mot += a[j] +",";
                    compteur+=1;
                }
            }
            //mot+="""";

            arguments << ""+mot+"" ;
            break;
            }
            case 9 : //"Choice"
            {
            int num;
            for(int u = 0; u< ConnectionSettings::tabChoix[indexFctChosen]->at(i)->size(); u++){
                if(ConnectionSettings::tabChoix[indexFctChosen]->at(i)->at(u)->getChoixNom()==reinterpret_cast<QComboBox*>(tabLineEdit[i])->currentText()){
                    num=u;
                }
            }
            if(ConnectionSettings::tabChoix[indexFctChosen]->at(i)->at(num)->getChoixPrefix()!=""){
                arguments << ConnectionSettings::tabChoix[indexFctChosen]->at(i)->at(num)->getChoixPrefix() << ConnectionSettings::tabChoix[indexFctChosen]->at(i)->at(num)->getChoixParam();
            }else{
                arguments << ConnectionSettings::tabChoix[indexFctChosen]->at(i)->at(num)->getChoixParam();
            }
            break;
            }
                }                        //"--no-debug" << "-i" << pathTab << "a" "1" ;
        }
        }

        QMessageBox::information(this, "ok", arguments[0]);
                                 //+" "+arguments[1]+" "+arguments[2]
                                 //+" "+arguments[3]+" "+arguments[4]);

        MainWindow::mwThis->compute(program, arguments);

        if(ConnectionSettings::tabFunction[indexFctChosen]->getNbArgument()!="0"){
            //destroyers
            for(int i=tabGroupBox.size(); i>0; i--){
                tabLineEdit[i-1]->~QWidget();

                tabQFormLayout[i-1]->~QFormLayout();
                tabQcheckBox[i-1]->~QCheckBox();
                for(int j=tabButtonFilePH.size(); j>0; j--){
                    tabButtonFilePH[j-1]->~QPushButton();
                    tabButtonFilePH.pop_back();
                }
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

                tabQFormLayout.pop_back();
                tabQcheckBox.pop_back();
                tabQHBox.pop_back();
                tabGroupBox.pop_back();

            }
            indexFilePH=0;
            indexFile=0;
            indexDirec=0;

            Ok->~QPushButton();
            back->~QPushButton();
            buttonLayout2->~QHBoxLayout();
        }
        totalLayout->~QVBoxLayout();

        widget->~QWidget();
        area->~QScrollArea();
        layoutTotal->~QVBoxLayout();

        this->~FunctionForm();
    }
}


void FunctionForm::testEmpty(){
    boolean vide = false;
    for(int i=0; i<(int)ConnectionSettings::tabArgument[indexFctChosen]->size(); i++){
        if(tabQcheckBox[i]->isChecked()){
            switch(ConnectionSettings::argTypeList.indexOf(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()))
                {
            case 0 : //"Text"
            case 4 : //"Process List"
            case 5 : //"Process Group"
            case 6 : //"File .ph"
            case 7 : //"File"
            case 8 : //"Folder"
            case 10 : //"File not existing"
            {
                if(reinterpret_cast<QLineEdit*>(tabLineEdit[i])->text()==""){
                    vide=true;
                }
            break;
            }
                }
        }
    }

    if(vide){
        QMessageBox::information(this, "Computation", "Please, fill the mandatory fields !");
    }else{
        this->launchCompute();
    }
}


//slot : enable the field according to the ("taken into account") checkbox state
void FunctionForm::enableForm(int state){
    for(int i =0; i<ConnectionSettings::tabFunction[indexFctChosen]->getNbArgument().toInt() ; i++){
        if(tabQcheckBox[i]->isChecked()){
            tabLineEdit[i]->setEnabled(true);
            //File .ph
            int compteurPH =0;
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()=="File .ph"){
                    for(int j=0; j<i;j++){
                        if(ConnectionSettings::tabArgument[indexFctChosen]->at(j)->getArgType()=="File .ph"){
                            compteurPH +=1;
                        }
                    }
                tabButtonFilePH[compteurPH]->setEnabled(true);
                compteurPH=0;
                }
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
            //File .ph
            int compteurPH =0;
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()=="File .ph"){
                    for(int j=0; j<i;j++){
                        if(ConnectionSettings::tabArgument[indexFctChosen]->at(j)->getArgType()=="File .ph"){
                            compteurPH +=1;
                        }
                    }
                tabButtonFilePH[compteurPH]->setEnabled(false);
                compteurPH=0;
                }
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
    for(int i =0; i<ConnectionSettings::tabFunction[indexFctChosen]->getNbArgument().toInt() ; i++){
        if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()=="Necessary argument" ||ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()=="Current File"){
            tabLineEdit[i]->setEnabled(false);
        }
    }
}


//slot : get the .ph file name when the "browse" pushbutton is clicked
void FunctionForm::getNamePH(){
    QString a;
    a = QFileDialog::getOpenFileName(this,"Select File", "/home/", tr("All Files (*.ph)"));
    int num;
        for(int i=0; i<tabButtonFilePH.size(); i++){
            if(tabButtonFilePH[i]==QObject::sender()){
                num=i;
            }
        }
    int now=0;
        while(num!=-1){
            if(ConnectionSettings::tabArgument[indexFctChosen]->at(now)->getArgType()=="File .ph"){
                num-=1;
            }
            now+=1;
        }
    reinterpret_cast<QLineEdit*>(tabLineEdit[now-1])->setText(a);
}

//slot : get the file name when the "browse" pushbutton is clicked
void FunctionForm::getName(){
    QString a;
    a = QFileDialog::getOpenFileName(this,"Select File", "/home/");
    int num;
        for(int i=0; i<(int)tabButtonFile.size(); i++){
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


//slot : get the folder name when the "browse" pushbutton is clicked
void FunctionForm::getDirectoryName(){
    QString a;
    a = QFileDialog::getExistingDirectory(this,"Select Directory", "/home/");
    int num;
        for(int i=0; i<(int)tabButtonDirec.size(); i++){
            if(tabButtonDirec[i]==QObject::sender()){
                num=i;
            }
        }
    int now=0;
        while(num!=-1){
            if(ConnectionSettings::tabArgument[indexFctChosen]->at(now)->getArgType()=="Folder"){
                num-=1;
            }
            now+=1;
        }
    reinterpret_cast<QLineEdit*>(tabLineEdit[now-1])->setText(a);
}

//QMessageBox::critical(this, "Error", "1");



