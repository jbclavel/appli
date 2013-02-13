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
    connect(Cancel, SIGNAL(clicked()), this, SLOT(exportXMLSettings()));
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

    this->importXMLSettings();
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

       int i;
       int j;
       for(i=0; i<tabFunction.size(); i++){
           writerStream.writeStartElement("Function");

           writerStream.writeStartElement("Definition");
           writerStream.writeTextElement("name", tabFunction[i]->getNameFunction());
           writerStream.writeTextElement("program", tabFunction[i]->getProgram());
               writerStream.writeTextElement("nbArgument", tabFunction[i]->getNbArgument());
           writerStream.writeEndElement();

          for ( j = 0; j < tabArgument[i]->size(); j++){

               writerStream.writeStartElement("ArgumentsDefinition");
               writerStream.writeTextElement("ArgNumber", tabArgument[i]->at(j)->getArgNumber());
                   writerStream.writeTextElement("ArgType", tabArgument[i]->at(j)->getArgType());
                   writerStream.writeTextElement("ArgSuf", tabArgument[i]->at(j)->getArgSuf());
                   writerStream.writeTextElement("ArgFacul", tabArgument[i]->at(j)->getArgFac());
               writerStream.writeEndElement();
           }

           writerStream.writeEndElement();
           }

//fonction courante
        writerStream.writeStartElement("Function");

        writerStream.writeStartElement("Definition");
            writerStream.writeTextElement("name", name->text());
            writerStream.writeTextElement("program", program->text());
            writerStream.writeTextElement("nbArgument", nbArg->text());
        writerStream.writeEndElement();

        for (int k = 0; k < nbArg->text().toInt(); k++){

            writerStream.writeStartElement("ArgumentsDefinition");
                writerStream.writeTextElement("ArgNumber", tabArgNumber[k]->text());
                writerStream.writeTextElement("ArgType", tabArgType[k]->currentText());
                writerStream.writeTextElement("ArgSuf", tabArgSuf[k]->text());
                writerStream.writeTextElement("ArgFacul", QString::number(tabArgfacul[k]->isChecked()));
            writerStream.writeEndElement();
        }

        if( nbArg->text().toInt()==0){
            writerStream.writeStartElement("ArgumentsDefinition");
                writerStream.writeTextElement("ArgNumber", "Sans Argument");
                writerStream.writeTextElement("ArgType", "Sans Argument");
                writerStream.writeTextElement("ArgSuf", "Sans Argument");
                writerStream.writeTextElement("ArgFacul", "Sans Argument");
            writerStream.writeEndElement();
        }

        writerStream.writeEndElement();
        writerStream.writeEndElement();
        writerStream.writeEndDocument();

        output.close();

    }
}


void ConnectionSettings::importXMLSettings(){

    QFile input("xmlConnectionSettings.xml");
    QXmlStreamReader readerStream;
    input.open(QFile::ReadOnly | QFile::Text);
    readerStream.setDevice(&input);

    readerStream.readNext();
    while (!readerStream.atEnd())
    {
        while (readerStream.name() == "Function")
        {
            readerStream.readNext();
            while(readerStream.isStartElement()==false)
            readerStream.readNext();

                if(readerStream.name() == "Definition")
                {
                    readerStream.readNext();
                    while(readerStream.isStartElement()==false)
                    readerStream.readNext();
                    if(readerStream.name() == "name")
                    {
                        tabFunction.push_back(new FuncFrame());
                        tabArgument.push_back(new std::vector<ArgumentFrame*>());
                        tabFunction[tabFunction.size()-1]->setNameFunction(readerStream.readElementText());

                        while(readerStream.isStartElement()==false)
                        readerStream.readNext();
                    }
                    if(readerStream.name() == "program")
                    {
                        tabFunction[tabFunction.size()-1]->setProgram(readerStream.readElementText()) ;
                        readerStream.readNext();

                        while(readerStream.isStartElement()==false)
                        readerStream.readNext();
                    }
                    if(readerStream.name() == "nbArgument")
                    {
                        tabFunction[tabFunction.size()-1]->setNbArgument(readerStream.readElementText()) ;

                        while(readerStream.isStartElement()==false)
                        readerStream.readNext();

                    }

                }

                while(readerStream.name() == "ArgumentsDefinition")
                {
                    readerStream.readNext();
                    while(readerStream.isStartElement()==false)
                    readerStream.readNext();

                    if(readerStream.name() == "ArgNumber")
                    {
                        tabArgument[tabArgument.size()-1]->push_back(new ArgumentFrame());
                        tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->setArgNumber(readerStream.readElementText());
                        readerStream.readNext();

                        while(readerStream.isStartElement()==false)
                        readerStream.readNext();
                    }
                    if(readerStream.name() == "ArgType")
                    {
                        tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->setArgType(readerStream.readElementText());
                        readerStream.readNext();

                        while(readerStream.isStartElement()==false)
                        readerStream.readNext();
                    }
                    if(readerStream.name() == "ArgSuf")
                    {
                        tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->setArgSuf(readerStream.readElementText());
                        readerStream.readNext();

                        while(readerStream.isStartElement()==false)
                        readerStream.readNext();
                    }
                    if(readerStream.name() == "ArgFacul")
                    {
                        tabArgument[tabArgument.size()-1]->at(tabArgument[tabArgument.size()-1]->size()-1)->setArgFac(readerStream.readElementText());

                        while(readerStream.isStartElement()==false)
                            if(readerStream.atEnd()==true){
                                    break;
                            }else{
                            readerStream.readNext();
                            }
                    }

                }
                while(readerStream.isStartElement()==false)
                    if(readerStream.atEnd()==true){
                        break;
                        }else{
                readerStream.readNext();
                    }
            }
    readerStream.readNext();
    }
    input.close();

    for (int i=0; i <tabFunction.size(); i++){
        tabFunction[i]->setArguments(*(tabArgument[i]));
    }
/*
    QMessageBox::information(this, "err",
        QString::number(tabFunction.size())         +  "\n" +
        QString::number(tabArgument.size())         +  "\n" +
        QString::number(tabArgument[0]->size())     +  "\n" +
        QString::number(tabArgument[1]->size())     +  "\n" +

        tabFunction[0]->getNameFunction()           +  "\n" +
        tabFunction[0]->getProgram()                +  "\n" +
        tabFunction[0]->getNbArgument()             +  "\n" +
        tabFunction[0]->getArguments().at(0)->getArgNumber()    +  "\n" +

            tabArgument[0]->at(0)->getArgNumber()       +  "\n" +
            tabArgument[0]->at(0)->getArgType()         +  "\n" +
            tabArgument[0]->at(0)->getArgSuf()          +  "\n" +
            tabArgument[0]->at(0)->getArgFac()          +  "\n" +

            tabArgument[0]->at(1)->getArgNumber()       +  "\n" +
            tabArgument[0]->at(1)->getArgType()         +  "\n" +
            tabArgument[0]->at(1)->getArgSuf()          +  "\n" +
            tabArgument[0]->at(1)->getArgFac()          +  "\n" +

        tabFunction[1]->getNameFunction()           +  "\n" +
        tabFunction[1]->getProgram()                +  "\n" +
        tabFunction[1]->getNbArgument()             +  "\n" +
        tabFunction[1]->getArguments().at(0)->getArgNumber()    +  "\n" +

            tabArgument[1]->at(0)->getArgNumber()       +  "\n" +
            tabArgument[1]->at(0)->getArgType()         +  "\n" +
            tabArgument[1]->at(0)->getArgSuf()          +  "\n" +
            tabArgument[1]->at(0)->getArgFac()          +  "\n"

            tabArgument[1]->at(1)->getArgNumber()       +  "\n" +
            tabArgument[1]->at(1)->getArgType()         +  "\n" +
            tabArgument[1]->at(1)->getArgSuf()          +  "\n" +
            tabArgument[1]->at(1)->getArgFac()          +  "\n"

);
//QMessageBox::critical(this, "Error", "No file opened!");
*/
}
