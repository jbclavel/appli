#include "ConnectionSettings.h"
#include <vector>
#include "FuncFrame.h"
#include "ArgumentFrame.h"



ConnectionSettings::ConnectionSettings():
    QWidget()
{
    // First group : Define the new function
    name = new QLineEdit;
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
    connect(Cancel, SIGNAL(clicked()), this, SLOT(quit()));
    connect(Save, SIGNAL(clicked()), this, SLOT(importXMLSettings()));
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





void ConnectionSettings::exportXMLSettings(){

    QFile output("xmlConnectionSettings.xml");

    if (!output.open(QIODevice::WriteOnly)){
        QMessageBox::critical(this, "Error", "Sorry, unable to open file.");
        output.errorString();
        return;
    } else {

        QXmlStreamWriter writerStream(&output);

        writerStream.setAutoFormatting(true);
        writerStream.writeStartDocument();

        writerStream.writeStartElement("FunctionSettings");

        writerStream.writeStartElement("Function");

        writerStream.writeStartElement("Definition");
            writerStream.writeTextElement("name", name->text());
            writerStream.writeTextElement("program", program->text());
            writerStream.writeTextElement("nbArgument", nbArg->text());
        writerStream.writeEndElement();

        for (int i = 0; i < nbArg->text().toInt(); i++){

            writerStream.writeStartElement("ArgumentsDefinition");
                writerStream.writeTextElement("ArgNumber", tabArgNumber[i]->text());
                writerStream.writeTextElement("ArgType", tabArgType[i]->currentText());
                writerStream.writeTextElement("ArgSuf", tabArgSuf[i]->text());
                writerStream.writeTextElement("ArgFacul", QString::number(tabArgfacul[i]->isChecked()));
            writerStream.writeEndElement();
        }

        writerStream.writeEndElement();
        writerStream.writeEndElement();
        writerStream.writeEndDocument();

        output.close();

    }
}


void ConnectionSettings::importXMLSettings(){

    int functCpt = 0;
    int argCpt = 0;
    tabArgument.push_back(new std::vector<ArgumentFrame*>());

    tabArgument[tabArgument.size()-1]->push_back(new ArgumentFrame());
    tabArgument[0]->at(0)->getArgNumber();
        tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->setArgNumber("1");
        tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->setArgType("1");
        tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->setArgSuf("1");
        tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->setArgFac("0");


    tabFunction.push_back(new FuncFrame());
        tabFunction[tabFunction.size()-1]->setNameFunction("1") ;
        tabFunction[tabFunction.size()-1]->setProgram("1") ;
        tabFunction[tabFunction.size()-1]->setNbArgument("1") ;
        tabFunction[tabFunction.size()-1]->setArguments(tabArgFunct);
        QMessageBox::information(this, "err", tabFunction[tabFunction.size()-1]->getNameFunction());

    QFile input("xmlConnectionSettings.xml");
    QXmlStreamReader readerStream;
    input.open(QFile::ReadOnly | QFile::Text);
    readerStream.setDevice(&input);

    //Le but de cette boucle est de parcourir le
    //fichier et de vérifier si l'on est au début d'un élément.
    readerStream.readNext();
    while (!readerStream.atEnd())
    {
        QMessageBox::information(this, "err", "celui la");

                while (readerStream.name() == "Function")
                {
                    QMessageBox::information(this, "err", "apres function ");

                    readerStream.readNext(); // On va au prochain token
                    // Tant que celui-ci n'est pas un élément de départ on avance au token suivant
                    while(readerStream.isStartElement()==false)
                    readerStream.readNext();
QMessageBox::information(this, "err", "apres function dans while ");

                    if(readerStream.name() == "Definition")
                    {
                        readerStream.readNext();
                        while(readerStream.isStartElement()==false)
                        readerStream.readNext();
                        if(readerStream.name() == "name")
                        {
                            tabFunction[tabFunction.size()-1]->setNameFunction(readerStream.readElementText());
                            readerStream.readNext();
                            QMessageBox::information(this, "err", tabFunction[tabFunction.size()-1]->getNameFunction());

                            while(readerStream.isStartElement()==false)
                            readerStream.readNext();
                        }
                        if(readerStream.name() == "program")
                        {
                            tabFunction[tabFunction.size()-1]->setProgram(readerStream.readElementText()) ;
                            readerStream.readNext();
                            QMessageBox::information(this, "err", tabFunction[tabFunction.size()-1]->getProgram());

                            while(readerStream.isStartElement()==false)
                            readerStream.readNext();
                        }
                        if(readerStream.name() == "nbArgument")
                        {
                            tabFunction[tabFunction.size()-1]->setNbArgument(readerStream.readElementText()) ;
                            QMessageBox::information(this, "err", tabFunction[tabFunction.size()-1]->getNbArgument());

                            functCpt+=1;
                            QMessageBox::information(this, "functCpt", QString::number(functCpt));
                            while(readerStream.isStartElement()==false)
                            readerStream.readNext();

                        }

                    }

      QMessageBox::information(this, "err", "avant argument setting");

                    while(readerStream.name() == "ArgumentsDefinition")
                    {
                        readerStream.readNext();
                        while(readerStream.isStartElement()==false)
                            readerStream.readNext();
                        if(readerStream.name() == "ArgNumber")
                        {
                            tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->setArgNumber(readerStream.readElementText());
                            readerStream.readNext();
                            QMessageBox::information(this, "err", tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->getArgNumber());

                            while(readerStream.isStartElement()==false)
                            readerStream.readNext();
                        }
                        if(readerStream.name() == "ArgType")
                        {

                            tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->setArgType(readerStream.readElementText());
                            readerStream.readNext();
                            QMessageBox::information(this, "err", tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->getArgType());

                            while(readerStream.isStartElement()==false)
                            readerStream.readNext();
                        }
                        if(readerStream.name() == "ArgSuf")
                        {
                            tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->setArgSuf(readerStream.readElementText());
                            readerStream.readNext();
                            QMessageBox::information(this, "err", tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->getArgSuf());

                            while(readerStream.isStartElement()==false)
                            readerStream.readNext();
                        }
                        if(readerStream.name() == "ArgFacul")
                        {
                            tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->setArgFac(readerStream.readElementText());
                            QMessageBox::information(this, "err", tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->getArgFac());

                          /*  if(readerStream.isEndElement()==true ){
                                readerStream.readNext();
                                if(readerStream.isEndElement()==true){
                                    readerStream.readNext();
                                     if(readerStream.isEndElement()==true){
                                         input.close();
                                         QMessageBox::information(this, "err", "closing");
                                     }
                                }
                            }
                            //else{
*/
                            argCpt+=1;
                            QMessageBox::information(this, "argCpt", QString::number(argCpt));

                            while(readerStream.isStartElement()==false) //&& readerStream.atEnd()==false)
                                if(readerStream.atEnd()==true){
                                    QMessageBox::information(this, "err", "just break");

                                 //input.close();
                                    break;

                                }else{
                                readerStream.readNext();

                                }


                        }
                        QMessageBox::information(this, "err", "viens d'etre ajouté");
                        //while(readerStream.isStartElement()==false)
                        //readerStream.readNext();

                    }
                    while(readerStream.isStartElement()==false)
                        if(readerStream.atEnd()==true){
                            QMessageBox::information(this, "err", "just break 2");
                            //input.close();
                            break;
                            }else{
                    readerStream.readNext();
                    QMessageBox::information(this, "err", "apres function dans while 2");
                        }


                }



        readerStream.readNext(); // On va au prochain token
        QMessageBox::information(this, "err", "pose un souci?");
    }
    QMessageBox::information(this, "err", "closing");

    input.close();


}


/*
void ConnectionSettings::exportXMLSettings(){

    if(!this->getCentraleArea()->subWindowList().isEmpty()){

        // SaveFile dialog
        QString xmlFile = QFileDialog::getSaveFileName(this, "Export Settings", QString(), "*.xml");

        // open file if possible and write XML tree into it
        QFile output(xmlFile);
        if (!output.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this, "Error", "Sorry, unable to open file.");
            output.errorString();
            return;
        } else {
            PHIO::exportXMLMetadata(this, output);
        }

    } else QMessageBox::critical(this, "Error", "No file opened!");

}
*/

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



