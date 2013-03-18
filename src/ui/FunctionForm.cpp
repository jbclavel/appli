#include "FunctionForm.h"
#include <vector>
#include "ConnectionSettings.h"
#include "MainWindow.h"


// les trois vecteurs ci dessous sont les 3 vecteurs statiques qui sont initialisés
// à l'ouverture de l'application lors de l'import du fichier XML xmlComputationSettings
// ils enregistrent tous les paramètres interessants pour le lancement des fonctions
std::vector<FuncFrame*> ConnectionSettings::tabFunction;
std::vector< std::vector<ArgumentFrame*>* > ConnectionSettings::tabArgument;
std::vector< std::vector< std::vector<ChoixLigne*>*>*> ConnectionSettings::tabChoix;

// cette liste de Qstring est une variable statique.
// elle représente tous les types d'arguments (l'ordre est très important)
// cf MainWindow.cpp
QStringList ConnectionSettings::argTypeList;

FunctionForm::FunctionForm(QString fileName):
    QDialog()
{
    //variable à initialiser a zero au début
    indexFilePH=0;
    indexFile=0;
    indexDirec=0;
    indexFileNotExisting=0;
    //permet d'avoir le chemin
    pathTab =fileName;

    //première fenêtre
        //combobox
    choix = new QComboBox;

    for (int i=0; i<(int)ConnectionSettings::tabFunction.size();i++ ){
        choix->addItem(ConnectionSettings::tabFunction[i]->getNameFunction());
    }

        //boutons
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

//slot appelé en cliquant sur le bouton cancel de la premiere fenêtre
//qui a pour fonction de quitter la fenêtre
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

//destructeur
FunctionForm::~FunctionForm(){}

//slot appelé en cliquant sur le bouton ok de la premiere fenêtre
// qui a pour fonction d'ouvrir la seconde fenêtre
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
            //qline edit : champ texte simple
                tabLineEdit.push_back(new QLineEdit);

                tabQFormLayout.push_back(new QFormLayout);
                    if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                        tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                    }else{
                        tabQFormLayout[i]->addRow("Prefix : "+
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
            //qspinbox : fenetre ou on ne peut mettre qu'un entier
                tabLineEdit.push_back(new QSpinBox);
                reinterpret_cast<QSpinBox*>(tabLineEdit[i])->setMaximum(10000);

                tabQFormLayout.push_back(new QFormLayout);
                    if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                        tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                    }else{
                        tabQFormLayout[i]->addRow("Prefix : "+
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
            //qspinbox : fenetre ou on ne peut mettre qu'un réel
            tabLineEdit.push_back(new QDoubleSpinBox);
            reinterpret_cast<QDoubleSpinBox*>(tabLineEdit[i])->setDecimals(15);
            reinterpret_cast<QDoubleSpinBox*>(tabLineEdit[i])->setRange(-10000,10000);

            tabQFormLayout.push_back(new QFormLayout);
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                    tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                }else{
                    tabQFormLayout[i]->addRow("Prefix : "+
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
            //Qcombobox :liste de choix : vrai ou faux
                tabLineEdit.push_back(new QComboBox);
                    reinterpret_cast<QComboBox*> (tabLineEdit[i])->addItem("true");
                    reinterpret_cast<QComboBox*> (tabLineEdit[i])->addItem("false");

                tabQFormLayout.push_back(new QFormLayout);
                    if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                        tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                    }else{
                        tabQFormLayout[i]->addRow("Prefix : "+
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
            case 4:   //"Process Sequence"
                {
            //qline edit : simple champ texte
            //structure : le séparateur est l'espace
                tabLineEdit.push_back(new QLineEdit);

                tabQFormLayout.push_back(new QFormLayout);
                    if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                        tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                    }else{
                        tabQFormLayout[i]->addRow("Prefix : "+
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
        case 5:   //"Process Set"
            {
            //qline edit : simple champ texte
            //structure : le séparateur est l'espace
            tabLineEdit.push_back(new QLineEdit);

            tabQFormLayout.push_back(new QFormLayout);
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                    tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                }else{
                    tabQFormLayout[i]->addRow("Prefix : "+
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
            //champ texte + bouton parcourir (juste fichier .ph)
            //le bouton alimente le champ texte
                tabLineEdit.push_back(new QLineEdit);
                tabButtonFilePH.push_back(new QPushButton("Browse"));
                connect(tabButtonFilePH[indexFilePH], SIGNAL(clicked()), this, SLOT(getNamePH()));


                tabQFormLayout.push_back(new QFormLayout);
                    if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                        tabQFormLayout[i]->addRow("Without any Prefix", tabLineEdit[i]);
                    }else{
                        tabQFormLayout[i]->addRow("Prefix : "+
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
            //champ texte + bouton parcourir (tt type de fichier)
            //le bouton alimente le champ texte
            tabLineEdit.push_back(new QLineEdit);
            tabButtonFile.push_back(new QPushButton("Browse"));
            connect(tabButtonFile[indexFile], SIGNAL(clicked()), this, SLOT(getName()));


            tabQFormLayout.push_back(new QFormLayout);
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                    tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                }else{
                    tabQFormLayout[i]->addRow("Prefix : "+
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
            //champ texte + bouton parcourir (juste des dossiers)
            //le bouton alimente le champ texte
                {
                tabLineEdit.push_back(new QLineEdit);
                tabButtonDirec.push_back(new QPushButton("Browse"));
                connect(tabButtonDirec[indexDirec], SIGNAL(clicked()), this, SLOT(getDirectoryName()));


                tabQFormLayout.push_back(new QFormLayout);
                    if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                        tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                    }else{
                        tabQFormLayout[i]->addRow("Prefix : "+
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
            //Qcombo box : liste de choix alimentée par l'utilisateur averti (info ds xmlComputationSettings.xml)
                tabLineEdit.push_back(new QComboBox);
                for(int m=0; m<(int)ConnectionSettings::tabChoix[indexFctChosen]->at(i)->size() ; m++){
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
            //champ texte + bouton parcourir (juste des dossiers)
            //le bouton alimente le champ texte
            //l'utilisateur n'a plus qu'à mettre un nom de fichier (celui qu'il veut créer)
        tabLineEdit.push_back(new QLineEdit);
        tabButtonFileNotExisting.push_back(new QPushButton("Browse"));
        connect(tabButtonFileNotExisting[indexFileNotExisting], SIGNAL(clicked()), this, SLOT(getDirectoryNameFileNotExisting()));


        tabQFormLayout.push_back(new QFormLayout);
            if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
            }else{
                tabQFormLayout[i]->addRow("Prefix : "+
                    ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf(), tabLineEdit[i]);
            }
        tabQcheckBox.push_back(new QCheckBox("Taken into account"));
        tabQHBox.push_back(new QHBoxLayout);
            tabQHBox[i]->addWidget(tabQcheckBox[i]);
            tabQHBox[i]->addLayout(tabQFormLayout[i]);
            tabQHBox[i]->addWidget(tabButtonFileNotExisting[indexFileNotExisting]);

            if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgFac()=="0"){ //if argument is not fac
                tabQcheckBox[i]->setChecked(true);
                tabQcheckBox[i]->setEnabled(false);
            }else{
                tabLineEdit[i]->setEnabled(false);
                tabButtonFileNotExisting[indexFileNotExisting]->setEnabled(false);
            }
        connect(this->tabQcheckBox[i], SIGNAL(stateChanged(int)), this, SLOT(enableForm(int)));

        tabGroupBox.push_back(new QGroupBox("Argument "+ QString::number(i+1)+
                            +" : (Type : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()
                            +") Caption : " + ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgOutline()));
        tabGroupBox[i]->setLayout(tabQHBox[i]);

        indexFileNotExisting+=1;
    break;}
        case 11:   //"Argument"
            {
            //qline edit : champ texte alimenté par l'utilisateur avertit (fichier xmlComputationSetting.xml)
            //champ grisé : modification  interdite
            tabLineEdit.push_back(new QLineEdit);
            reinterpret_cast<QLineEdit*>(tabLineEdit[i])->setText(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf());
            tabLineEdit[i]->setEnabled(false);

            tabQFormLayout.push_back(new QFormLayout);
            tabQFormLayout[i]->addRow("Argument : ", tabLineEdit[i]);

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
        case 12:   //"Current File"
            {
            //qline edit : champ texte alimenté par le fichier ouvert
            //champ grisé : modification  interdite
            tabLineEdit.push_back(new QLineEdit);
            reinterpret_cast<QLineEdit*>(tabLineEdit[i])->setText(MainWindow::mwThis->pathCurrentWindow());
            tabLineEdit[i]->setEnabled(false);

            tabQFormLayout.push_back(new QFormLayout);
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()==""){
                    tabQFormLayout[i]->addRow("Without any prefix", tabLineEdit[i]);
                }else{
                    tabQFormLayout[i]->addRow("Prefix : "+
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
            }
        totalLayout->addWidget(tabGroupBox[i]);
        }

    //creation des boutons
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

//slot appelé en cliquant sur le bouton back
//fonction de retour à la fenêtre de choix d'une function
void FunctionForm::fctBack(){

        //destructeur
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
        for(int j=tabButtonFileNotExisting.size(); j>0; j--){
            tabButtonFileNotExisting[j-1]->~QPushButton();
            tabButtonFileNotExisting.pop_back();
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
    indexFileNotExisting=0;


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

//slot appelé après avoir cliqué sur le bouton ok qi les tests sont ok
// qui a pour but de lancer la fonction
void FunctionForm::launchCompute(){

   // nom du program
   QString program = ConnectionSettings::tabFunction[indexFctChosen]->getProgram();

   //list des arguments
   QStringList arguments;

   //recupération  des arguments dans les différentes fenêtres
    for(int i=0; i<(int)ConnectionSettings::tabArgument[indexFctChosen]->size(); i++){
            if(tabQcheckBox[i]->isChecked()){
            switch(ConnectionSettings::argTypeList.indexOf(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()))
                {
            case 0 : //"Text"
            case 6 : //"File .ph"
            case 7 : //"File"
            case 8 : //"Folder"
            case 10 : //"File not existing"
            case 12 : //"Current File"
            {
                //ici recuperation des info dans un simple qlineedit
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()!=""){
                    arguments << ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf();
                }
                arguments  << reinterpret_cast<QLineEdit*>(tabLineEdit[i])->text();
            break;
            }
            case 11 : //"Argument"
            {
                //ici recuperation des infos dans un simple qlineedit mais sans préfixe
                arguments  << reinterpret_cast<QLineEdit*>(tabLineEdit[i])->text();
            break;
            }
            case 1 : //"Integer"
            case 2 : //"Real"
            {
                //ici recuperation des info dans un qspinbox
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()!=""){
                    arguments << ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf();
                }
                arguments  << reinterpret_cast<QSpinBox*>(tabLineEdit[i])->text();
            break;
            }
            case 3 : //"Boolean
            {
                //ici recuperation des info dans un qcombobox
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()!=""){
                    arguments << ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf();
                }
            arguments << reinterpret_cast<QComboBox*>(tabLineEdit[i])->currentText();
            break;
            }
            case 4 : //"Process Sequence"
            {
                //ici recuperation des info dans un simple qlineedit
                //mais avec un traitement : à partir du texte, on enlève l'espace de fin s'il existe,
                //on crée une liste de mot en utilisant le separateur "espace"
                //exemple : texte : a 1 b 2
                //-->
                //liste[0]=a
                //liste[1]=1
                //liste[2]=b
                //liste[3]=2
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()!=""){
                    arguments << ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf();
                }

            QString motPS = reinterpret_cast<QLineEdit*>(tabLineEdit[i])->text();
            QString motPSFinal;
            if(motPS.at(motPS.size()-1)==' '){
                for(int p = 0 ; p < motPS.size()-1 ; p++){
                    motPSFinal.push_back(motPS[p]);
                }
            }else{
                motPSFinal=motPS;
            }

            QStringList a = MainWindow::mwThis->wordList(motPSFinal);

            for (int j=0; j< a.size(); j++){
                    arguments << a[j];
                }
            break;
            }
            case 5 : //"Process Set"
            {
                //ici recuperation des info dans un simple qlineedit
                //mais avec un traitement : à partir du texte, on enlève l'espace de fin s'il existe,
                //on crée une liste de mot en utilisant le separateur "espace"
                //on recrée un texte en insèrant des "," entre les sorts
                //exemple : texte : a 1 b 2
                //-->
                //liste[0]=a
                //liste[1]=1
                //liste[2]=b
                //liste[3]=2
                //-->
                //texte recréé : "a 1,b 2"
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf()!=""){
                    arguments << ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgSuf();
                }

            QString motPS = reinterpret_cast<QLineEdit*>(tabLineEdit[i])->text();
            QString motPSFinal;

            if(motPS.at(motPS.size()-1)==' '){
                for(int p = 0 ; p < motPS.size()-1 ; p++){
                    motPSFinal.push_back(motPS[p]);
                }
            }else{
                motPSFinal=motPS;
            }

            QStringList a = MainWindow::mwThis->wordList(motPSFinal);
            QString mot;//= """";
            QString motFinal;
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
            for(int i=0; i< mot.size()-1 ;i++){
                motFinal+=mot[i];
            }
            arguments << ""+ motFinal +"" ;
            break;
            }
            case 9 : //"Choice"
            {
                //qcombobox : liste de choix
                //mais on ne recupère pas ce qui est affiché dans la combobox
                //mais le paramètre associé dans le fichier xmlComputationSettings.xml
            int num;
            for(int u = 0; u< (int)ConnectionSettings::tabChoix[indexFctChosen]->at(i)->size(); u++){
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

    //creation d'un texte comprenant tous les arguments
    QString poiu;
    for(int po=0; po < arguments.size();po++){
        poiu+=arguments[po]+" ";
    }

    //affichage de la fenetre "etesvous sur de vouloir lancer la fonction"
    int reponse = QMessageBox::question(this, "Functio Form validation : " + program, "Do you really want to launch the function (check settings if there is...)  ? <br> Function : "+ program +" "+poiu,
                            QMessageBox::No | QMessageBox::Yes);

    if (reponse == QMessageBox::Yes){
        // si oui on lance la fonction et on ferme la fenêtre Functionform
        //sinon on ne fait rein

        //lancement de la fonction
        MainWindow::mwThis->compute(program, arguments);

        //fermeture de la fenêtre
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
                for(int j=tabButtonFileNotExisting.size(); j>0; j--){
                    tabButtonFileNotExisting[j-1]->~QPushButton();
                    tabButtonFileNotExisting.pop_back();
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
            indexFileNotExisting=0;

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

//slot appelé lorsque l'on clique sur ok de la fenetre de lancement
// teste si les champs qui doivent être remplis sont vides
// si ils le sont : message d'erreur et la fonction n'est pas lancée
void FunctionForm::testEmpty(){
    boolean vide = false;
    for(int i=0; i<(int)ConnectionSettings::tabArgument[indexFctChosen]->size(); i++){
        if(tabQcheckBox[i]->isChecked()){
            switch(ConnectionSettings::argTypeList.indexOf(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()))
                {
            case 0 : //"Text"
            case 4 : //"Process Sequence"
            case 5 : //"Process Set"
            case 6 : //"File .ph"
            case 7 : //"File"
            case 8 : //"Folder"
            case 10 : //"File not existing"
            {
                //le test n'est fait que pour les chammps de type qlineedit
                if(reinterpret_cast<QLineEdit*>(tabLineEdit[i])->text()==""){
                    vide=true;
                }
            break;
            }
                }
        }
    }

    if(vide){
        QMessageBox::information(this, "Function Form validation", "Please, fill the mandatory fields !");
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
            //File Not Existing
            int compteurFileNotExisting =0;
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()=="File not existing"){
                    for(int j=0; j<i;j++){
                        if(ConnectionSettings::tabArgument[indexFctChosen]->at(j)->getArgType()=="File not existing"){
                            compteurFileNotExisting +=1;
                        }
                    }
            tabButtonFileNotExisting[compteurFileNotExisting]->setEnabled(true);
            compteurFileNotExisting=0;
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
            int compteurDir=0;
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()=="Folder"){
                    for(int j=0; j<i;j++){
                        if(ConnectionSettings::tabArgument[indexFctChosen]->at(j)->getArgType()=="Folder"){
                            compteurDir +=1;
                        }
                    }
                tabButtonDirec[compteurDir]->setEnabled(false);
                compteurDir=0;
                }
            //File Not Existing
            int compteurFileNotExisting =0;
                if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()=="File not existing"){
                    for(int j=0; j<i;j++){
                        if(ConnectionSettings::tabArgument[indexFctChosen]->at(j)->getArgType()=="File not existing"){
                            compteurFileNotExisting +=1;
                        }
                    }
                tabButtonFileNotExisting[compteurFileNotExisting]->setEnabled(false);
                compteurFileNotExisting=0;
                }
            }
    }
    for(int i =0; i<ConnectionSettings::tabFunction[indexFctChosen]->getNbArgument().toInt() ; i++){
        if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()=="Current File"){
            tabLineEdit[i]->setEnabled(false);
        }
        if(ConnectionSettings::tabArgument[indexFctChosen]->at(i)->getArgType()=="Argument"){
            tabLineEdit[i]->setEnabled(false);
        }
    }
}


//slot : get the .ph file name when the "browse" pushbutton is clicked
void FunctionForm::getNamePH(){
    QString a;
    a = QFileDialog::getOpenFileName(this,"Select File .ph", "/home/", tr("All Files (*.ph)"));
    int num;
        for(int i=0; i<(int)tabButtonFilePH.size(); i++){
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


//slot : get the directory name of the file not existing when the "browse" pushbutton is clicked
void FunctionForm::getDirectoryNameFileNotExisting(){
    QString a;
    a = QFileDialog::getExistingDirectory(this,"Select Directory", "/home/");
    int num;
        for(int i=0; i<(int)tabButtonFileNotExisting.size(); i++){
            if(tabButtonFileNotExisting[i]==QObject::sender()){
                num=i;
            }
        }
    int now=0;
        while(num!=-1){
            if(ConnectionSettings::tabArgument[indexFctChosen]->at(now)->getArgType()=="File not existing"){
                num-=1;
            }
            now+=1;
        }
    reinterpret_cast<QLineEdit*>(tabLineEdit[now-1])->setText(a);
}


//QMessageBox::critical(this, "Error", "1");



