#include "ConnectionSettings.h"
#include <vector>


ConnectionSettings::ConnectionSettings():
    QWidget()
{
    // First group : Define the new function
    name = new QLineEdit;
    program = new QLineEdit;
    nbArg = new QSpinBox;
    QMessageBox::information(this, "nbArg", nbArg->text());

    nbArg->setValue(0);
    nbArgPrcdt = nbArg->text().toInt();
    QMessageBox::information(this, "nbArg", nbArg->text());
    QMessageBox::information(this, "nbArg", QString::number(nbArgPrcdt));

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
    connect(Cancel, SIGNAL(clicked()), this, SLOT(quit()));
    connect(nbArg, SIGNAL(valueChanged(int)), this, SLOT(buildTable()));


    //Mise en page générale
    globalLayout = new QVBoxLayout;
    globalLayout->addWidget(groupDefinition);
    globalLayout->addWidget(groupTable);
    globalLayout->addLayout(boutonsLayout);

    setLayout(globalLayout);
    setWindowTitle("Connection Settings");
    resize(400, 450);

}

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

        ConnectionSettings::~ConnectionSettings(){

            QMessageBox::information(this, "nbArg", nbArg->text());

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
                    QMessageBox::information(this, "nbArg", QString::number(i));
                }
            }
QMessageBox::information(this, "nbArg", nbArg->text());
           // nbArg->setValue(0);
         QMessageBox::information(this, "nbArg", nbArg->text());
          //  nbArgPrcdt = nbArg->text().toInt();

            QMessageBox::information(this, "nbArg", nbArg->text());
            name->~QLineEdit();
            program->~QLineEdit();
            nbArg->~QSpinBox();
            //QMessageBox::information(this, "nbArg", nbArg->text());

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
               /*
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
                }*/



        //std::vector<QLabel*> tabArgNumber;
        //std::vector<QComboBox*> tabArgType ;
        //std::vector<QLineEdit*> tabArgSuf;
        //std::vector<QCheckBox*> tabArgfacul;
        //int nbArgPrcdt;


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


        //QLabel *argNumber = new QLabel("Argument 1 :", this);
        //argNumber->setFont(QFont("Comic Sans MS", 10, QFont::Bold, false));

        //argType = new QComboBox(this);
        //argType->addItems(argTypeList);

        //facultatif = new QCheckBox("Facultatif ?");

        //gridTable->addWidget(tabArgNumber[1], 0, 0);
        //gridTable->addWidget(tabArgType[1], 0, 1);
        //gridTable->addWidget(tabArgfacul[1],0,3);



