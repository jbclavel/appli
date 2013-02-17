#include "FunctionForm.h"
#include <vector>
#include "ConnectionSettings.h"

//#include "MainWindow.h"
//#include "FuncFrame.h"
//#include "ArgumentFrame.h"

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

    this->~FunctionForm();
}

FunctionForm::~FunctionForm(){
    //~QWidget(this);
    choix->~QComboBox();
    Yes->~QPushButton();
    Cancel->~QPushButton();
    buttonLayout->~QHBoxLayout();
    //totalLayout->~QVBoxLayout();
}

void FunctionForm::openConnectionForm(){

    QString functionChosen = choix->currentText();
    int indexFctChosen;
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
                QMessageBox::critical(this, "Error", "No file opened!");
                break;
            case 1:   //process
                QMessageBox::critical(this, "Error", "No file process");
                break;

            }

       }

//    totalLayouta = new QVBoxLayout;
  //  totalLayouta->addWidget(choix);

    //setLayout(totalLayouta);

}
    /*
    program = new QLineEdit;
    nbArg = new QSpinBox;
    nbArg->findChild<QLineEdit*>()->setReadOnly(true);

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

        //call the function which build the table
    ConnectionSettings::buildTable();

    tableLayout = new QVBoxLayout;
    tableLayout->addLayout(gridTable);

    enTeteArgNum = new QLabel("", this);
    enTeteArgTyp = new QLabel("Type", this);
    enTeteArgSuf = new QLabel("Suffix", this);
    enTeteArgFac = new QLabel("Facultatif ", this);

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

        // Connexions des signaux et des slots
    connect(nbArg, SIGNAL(valueChanged(int)), this, SLOT(buildTable()));
    connect(Save, SIGNAL(clicked()), this, SLOT(validationConnectionSettings()));
    connect(Cancel, SIGNAL(clicked()), this, SLOT(quit()));

    //Mise en page générale
    globalLayout = new QVBoxLayout;
    globalLayout->addWidget(groupDefinition);
    globalLayout->addWidget(groupTable);
    globalLayout->addLayout(boutonsLayout);

    setLayout(globalLayout);
    setWindowTitle("Connection Settings");
    resize(400, 450);

}

//build the tabel
void ConnectionSettings::buildTable(){

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

                    tabArgNumber[tabArgNumber.size()-1]->~QLabel();
                    tabArgType[tabArgType.size()-1]->~QComboBox();
                    tabArgSuf[tabArgSuf.size()-1]->~QLineEdit();

                    tabArgfacul[tabArgfacul.size()-1]->~QCheckBox();

                    tabArgNumber.pop_back();
                    tabArgType.pop_back();
                    tabArgSuf.pop_back();
                    tabArgfacul.pop_back();

                    nbArgPrcdt = nbArg->text().toInt();
            }
     }


//SLOT : close the window
void ConnectionSettings::quit(){

    this->~ConnectionSettings();
}

//Detroyer
ConnectionSettings::~ConnectionSettings(){

            //remove the table
            if(nbArg->text().toInt()!=0){

                for(int i = nbArg->text().toInt()-1 ; i >= 0 ; i--){
                    tabArgNumber[i]->~QLabel();
                    tabArgType[i]->~QComboBox();
                    tabArgSuf[i]->~QLineEdit();
                    tabArgfacul[i]->~QCheckBox();

                    tabArgNumber.pop_back();
                    tabArgType.pop_back();
                    tabArgSuf.pop_back();
                    tabArgfacul.pop_back();
                }
            }

            //remove the definition group
            name->~QLineEdit();
            program->~QLineEdit();
            nbArg->~QSpinBox();

            definitionLayout->~QFormLayout();
            groupDefinition->~QGroupBox();

            //Remove : Groupe : Table
            gridTable->~QGridLayout();
                //Remove : en-tête
            enTeteArgNum->~QLabel();
            enTeteArgTyp->~QLabel();
            enTeteArgSuf->~QLabel();
            enTeteArgFac->~QLabel();

            tableLayout->~QVBoxLayout();
            groupTable->~QGroupBox();

            //Remove : button
            Save->~QPushButton();
            Cancel->~QPushButton();
            boutonsLayout->~QHBoxLayout();

            //Remove : general layout
            globalLayout->~QVBoxLayout();

}


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


