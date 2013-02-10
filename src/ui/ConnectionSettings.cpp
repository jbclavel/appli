#include "ConnectionSettings.h"
#include <vector>

//ConnectionSettings::ConnectionSettings(QWidget *parent):
//QWidget(parent)

ConnectionSettings::ConnectionSettings()
{

    // First group : Define the new function
    name = new QLineEdit;
    program = new QLineEdit;
    nbArg = new QSpinBox;

    nbArg->setValue(0);
    nbArgPrcdt = nbArg->text().toInt();

    definitionLayout = new QFormLayout;
    definitionLayout->addRow("Function &name to be displayed", name);
    definitionLayout->addRow("&Program", program);
    definitionLayout->addRow("Number of &argument :", nbArg);

    groupDefinition = new QGroupBox("Define the new function :");
    groupDefinition->setLayout(definitionLayout);

    //Second group : Specify argument
    gridTable = new QGridLayout;

    //combo box's list(argument types)
    argTypeList= QStringList() << "Text" << "Process";


    ConnectionSettings::buildDynamicPage();

    tableLayout = new QVBoxLayout;
    tableLayout->addLayout(gridTable);

    QLabel *enTeteArgNum = new QLabel("", this);
    QLabel *enTeteArgTyp = new QLabel("Type", this);
    QLabel *enTeteArgSuf = new QLabel("Suffix", this);
    QLabel *enTeteArgFac = new QLabel("Facultatif ", this);

    gridTable->addWidget(enTeteArgNum,0, 0);
    gridTable->addWidget(enTeteArgTyp,0, 1);
    gridTable->addWidget(enTeteArgSuf,0, 2);
    gridTable->addWidget(enTeteArgFac,0, 3);

    groupTable = new QGroupBox("Specify argument(s) :");
    groupTable->setLayout(tableLayout);


    //Button Save and Cancel
    Save = new QPushButton("&Save");
    Cancel = new QPushButton("&Cancel");
    boutonsLayout = new QHBoxLayout;
    boutonsLayout->addWidget(Save);
    boutonsLayout->addWidget(Cancel);


    //Mise en page générale
    globalLayout = new QVBoxLayout;
    globalLayout->addWidget(groupDefinition);
    globalLayout->addWidget(groupTable);
    globalLayout->addLayout(boutonsLayout);


    // Connexions des signaux et des slots
        connect(Cancel, SIGNAL(clicked()), qApp, SLOT(quit()));
        //connect(Save, SIGNAL(clicked()), this, SLOT(genererCode()));
        connect(nbArg, SIGNAL(valueChanged(int)), this, SLOT(buildDynamicPage()));
/*
    QGridLayout *Gridlayout = new QGridLayout;
    Gridlayout->addWidget(groupDefinition, 0, 0);
    Gridlayout->addWidget(label, 0, 1);
    Gridlayout->addWidget(table, 0, 2);
    Gridlayout->addWidget(boutonsLayout, 0, 3);
*/

    //validator = new QRegExpValidator(this);
    //nbArg->setValidator(validator);
    //boutonsLayout->setAlignment(Qt::AlignRight);

    //QLabel *label = new QLabel("Specify argument(s) :", this);
    //label->setFont(QFont("Comic Sans MS", 10, QFont::Bold, false));


     setLayout(globalLayout);
     setWindowTitle("Connection Settings");
     resize(400, 450);

     //QLabel *argNumber = new QLabel("Argument 1 :", this);
     //argNumber->setFont(QFont("Comic Sans MS", 10, QFont::Bold, false));

     //argType = new QComboBox(this);
     //argType->addItems(argTypeList);

     //facultatif = new QCheckBox("Facultatif ?");

     //gridTable->addWidget(tabArgNumber[1], 0, 0);
     //gridTable->addWidget(tabArgType[1], 0, 1);
     //gridTable->addWidget(tabArgfacul[1],0,3);


}

     void ConnectionSettings::buildDynamicPage(){

        if(nbArg->text().toInt()>nbArgPrcdt){

            tabArgNumber.push_back(new QLabel("Arg " + nbArg->text() + " :" , this));

            tabArgType.push_back(new QComboBox(this));
            tabArgType[tabArgType.size()-1]->addItems(argTypeList);

            tabArgSuf.push_back(new QLineEdit( this));

            tabArgfacul.push_back(new QCheckBox("Yes"));

            gridTable->addWidget(tabArgNumber[tabArgNumber.size()-1], nbArg->text().toInt(), 0);
            gridTable->addWidget(tabArgType[tabArgType.size()-1], nbArg->text().toInt(), 1);
            gridTable->addWidget(tabArgSuf[tabArgSuf.size()-1], nbArg->text().toInt(), 2);
            gridTable->addWidget(tabArgfacul[tabArgfacul.size()-1],nbArg->text().toInt(),3);

            nbArgPrcdt = nbArg->text().toInt();

        }else if(nbArg->text().toInt()<nbArgPrcdt){

                    tabArgNumber[tabArgNumber.size()-1]->~QLabel ();
                    tabArgType[tabArgType.size()-1]->~QComboBox ();
                    tabArgSuf[tabArgSuf.size()-1]->~QLineEdit ();

                    tabArgfacul[tabArgfacul.size()-1]->~QCheckBox ();

                    tabArgNumber.pop_back();
                    tabArgType.pop_back();
                    tabArgSuf.pop_back();
                    tabArgfacul.pop_back();

                    nbArgPrcdt = nbArg->text().toInt();
            }


     /*for (int i=1 ; i< nbArg->text().toInt()+1 ; i++){

         //il faut supprimer les vecteurs avant d'en recréer.
         //necessiter de recupere l'ancienne valeur de nbArg


         //tabArgNumber[i] = new QLabel("Argument " + QString::number(i) + " :" , this);

         tabArgType[i] = new QComboBox(this);
         tabArgType[i]->addItems(argTypeList);

         tabArgfacul[i] = new QCheckBox("Facultatif ?");


            QMessageBox::information(this, "nbArg", nbArg->text());
            QMessageBox::information(this, "nbArg", QString::number(nbArgPrcdt));
            QMessageBox::information(this, "nbArg", QString::number(tabArgType.size()));

     }*/
 }





