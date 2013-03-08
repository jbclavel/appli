#include "ConnectionSettings.h"
#include <vector>
#include "MainWindow.h"
#include "FuncFrame.h"
#include "ArgumentFrame.h"


ConnectionSettings::ConnectionSettings():
    QDialog()
{
    // First group : Define the new function
    name = new QLineEdit;
    program = new QLineEdit;
    nbArg = new QSpinBox;
    nbArg->findChild<QLineEdit*>()->setReadOnly(true);

    nbArg->setValue(0);
    nbArgPrcdt = nbArg->text().toInt();

//a mettre en fct
    tabChoixPrcdt.clear();
    for (int i=0; i<nbArg->text().toInt() ; i++){
        QString a = tabArgSuf[i]->metaObject()->className();
        if(a=="QSpinBox"){
            tabChoixPrcdt.push_back(reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text());
        }else if(a=="QLineEdit"){
            tabChoixPrcdt.push_back("pas de type choix");
        }
    }

    definitionLayout = new QFormLayout;
    definitionLayout->addRow("Function &name to be displayed", name);
    definitionLayout->addRow("&Program", program);
    definitionLayout->addRow("Number of &argument :", nbArg);

    groupDefinition = new QGroupBox("Define the new function :");
    groupDefinition->setLayout(definitionLayout);

    //Second group : Specify argument
    gridTable = new QGridLayout;

        //call the function which build the table
    ConnectionSettings::buildTable();

    tableLayout = new QVBoxLayout;
    tableLayout->addLayout(gridTable);

    enTeteArgNum = new QLabel("", this);
    enTeteArgTyp = new QLabel("Type", this);
    enTeteArgSuf = new QLabel("Prefix", this);
    enTeteArgFac = new QLabel("Facultative ", this);
    enTeteArgOutline = new QLabel("Outline ", this);

    gridTable->addWidget(enTeteArgNum,0, 0);
    gridTable->addWidget(enTeteArgTyp,0, 1);
    gridTable->addWidget(enTeteArgSuf,0, 2);
    gridTable->addWidget(enTeteArgFac,0, 3);
    gridTable->addWidget(enTeteArgOutline,0, 4);

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
    connect(Save, SIGNAL(clicked()), this, SLOT(testFunctionName()));

    connect(Cancel, SIGNAL(clicked()), this, SLOT(quit()));

    //Mise en page générale
    globalLayout = new QVBoxLayout;
    globalLayout->addWidget(groupDefinition);
    globalLayout->addWidget(groupTable);
    globalLayout->addLayout(boutonsLayout);

    //ajout du scroll
    widget = new QWidget;
    widget->setLayout(globalLayout);
    area = new QScrollArea;
    area->setWidget(widget);
    area->setWidgetResizable(true);

    layoutTotal = new QVBoxLayout;
    layoutTotal->addWidget(area);

    setLayout(layoutTotal);
    setWindowTitle("Connection Settings");
    setModal(true);
    resize(700,300);

}

//build the table
void ConnectionSettings::buildTable(){

    if(nbArg->text().toInt()>nbArgPrcdt){

        tabArgNumber.push_back(new QLabel("Arg " + nbArg->text() + " :" , this));
        tabArgNumber[tabArgNumber.size()-1]->setMinimumHeight(25);

        tabArgType.push_back(new QComboBox(this));
        tabArgType[tabArgType.size()-1]->setMinimumHeight(25);
        tabArgType[tabArgType.size()-1]->addItems(ConnectionSettings::argTypeList);
        connect(tabArgType[tabArgType.size()-1], SIGNAL(activated(QString)), this, SLOT(choixCrea(QString)));
        connect(tabArgType[tabArgType.size()-1], SIGNAL(activated(QString)), this, SLOT(setEnability(QString)));

        tabArgSuf.push_back(new QLineEdit(this));

        tabArgfacul.push_back(new QCheckBox("Yes"));

        tabArgOutline.push_back(new QLineEdit( this));

        //def de rowmax = rangée max
        rowMax = nbArg->text().toInt()-1;
        int ind = rowMax;
        for(int i = 0; i < ind; i++){
            QString a = tabArgSuf[i]->metaObject()->className();
            if(a=="QSpinBox"){
                rowMax += reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text().toInt();
            }
        }

        gridTable->addWidget(tabArgNumber[tabArgNumber.size()-1], rowMax+1 , 0);
        gridTable->addWidget(tabArgType[tabArgType.size()-1], rowMax+1 , 1);
        gridTable->addWidget(tabArgSuf[tabArgSuf.size()-1], rowMax+1 , 2);
        gridTable->addWidget(tabArgfacul[tabArgfacul.size()-1],rowMax+1 ,3);
        gridTable->addWidget(tabArgOutline[tabArgOutline.size()-1],rowMax+1 ,4);

        nbArgPrcdt = nbArg->text().toInt();

    }else if(nbArg->text().toInt()<nbArgPrcdt){

        QString a = tabArgSuf[tabArgSuf.size()-1]->metaObject()->className();
        if(a!="QSpinBox"){

                tabArgNumber[tabArgNumber.size()-1]->~QLabel();
                tabArgType[tabArgType.size()-1]->~QComboBox();

                QString a = tabArgSuf[tabArgSuf.size()-1]->metaObject()->className();
                if(a=="QLineEdit"){
                    reinterpret_cast<QLineEdit*>(tabArgSuf[tabArgSuf.size()-1])->~QLineEdit();
                }else if(a=="QSpinBox"){
                    reinterpret_cast<QSpinBox*>(tabArgSuf[tabArgSuf.size()-1])->~QSpinBox();
                }

                tabArgfacul[tabArgfacul.size()-1]->~QCheckBox();
                tabArgOutline[tabArgOutline.size()-1]->~QLineEdit();

                tabArgNumber.pop_back();
                tabArgType.pop_back();
                tabArgSuf.pop_back();
                tabArgfacul.pop_back();
                tabArgOutline.pop_back();

                nbArgPrcdt = nbArg->text().toInt();
        }else if(reinterpret_cast<QSpinBox*>(tabArgSuf[tabArgSuf.size()-1])->text().toInt()!=0){
            QMessageBox::information(this, "Warning", "You can not delete the last argument because some choice lines still exist. Please, delete some choice lines !");
            nbArg->setValue(nbArg->text().toInt()+1);
        }else{
            tabArgNumber[tabArgNumber.size()-1]->~QLabel();
            tabArgType[tabArgType.size()-1]->~QComboBox();

            QString a = tabArgSuf[tabArgSuf.size()-1]->metaObject()->className();
            if(a=="QLineEdit"){
                reinterpret_cast<QLineEdit*>(tabArgSuf[tabArgSuf.size()-1])->~QLineEdit();
            }else if(a=="QSpinBox"){
                reinterpret_cast<QSpinBox*>(tabArgSuf[tabArgSuf.size()-1])->~QSpinBox();
            }

            tabArgfacul[tabArgfacul.size()-1]->~QCheckBox();
            tabArgOutline[tabArgOutline.size()-1]->~QLineEdit();

            tabArgNumber.pop_back();
            tabArgType.pop_back();
            tabArgSuf.pop_back();
            tabArgfacul.pop_back();
            tabArgOutline.pop_back();

            nbArgPrcdt = nbArg->text().toInt();
    }
    }
    gridTable->update();
    resize(700, 500);

    for(int i=tabArgTypeMem.size(); i>0; i--){
        tabArgTypeMem.pop_back();
    }

    for(int i=0; i<(int)tabArgType.size(); i++){
        tabArgTypeMem.push_back(tabArgType[i]->currentText());
    }
}


//SLOT : close the window
void ConnectionSettings::quit(){

    //remove the table
    if(nbArg->text().toInt()!=0){
        int curseur=0;
        for(int i = nbArg->text().toInt()-1 ; i >= 0 ; i--){
            tabArgNumber[i]->~QLabel();
            tabArgType[i]->~QComboBox();

            QString a = tabArgSuf[i]->metaObject()->className();
            if(a=="QLineEdit"){
                reinterpret_cast<QLineEdit*>(tabArgSuf[i])->~QLineEdit();
             }else if(a=="QSpinBox"){
                int curseurLocal = curseur;
                for(int j=curseurLocal; j<reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text().toInt() + curseurLocal; j++){
                    tabChoixNom[j]->~QLineEdit();
                    tabChoixParam[j]->~QLineEdit();
                    tabChoixPrefix[j]->~QLineEdit();
                    curseur+=1;
                }
                reinterpret_cast<QSpinBox*>(tabArgSuf[i])->~QSpinBox();
            }

            tabArgfacul[i]->~QCheckBox();
            tabArgOutline[i]->~QLineEdit();

            tabArgNumber.pop_back();
            tabArgType.pop_back();
            tabArgSuf.pop_back();
            tabArgfacul.pop_back();
            tabArgOutline.pop_back();

        }
        tabChoixNom.clear();
        tabChoixParam.clear();
        tabChoixPrefix.clear();
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
    enTeteArgOutline->~QLabel();

    tableLayout->~QVBoxLayout();
    groupTable->~QGroupBox();

    //Remove : button
    Save->~QPushButton();
    Cancel->~QPushButton();
    boutonsLayout->~QHBoxLayout();

    //Remove : general layout
    globalLayout->~QVBoxLayout();

    //Remove : scrollbar
    widget->~QWidget();
    area->~QScrollArea();
    layoutTotal->~QVBoxLayout();

    this->~ConnectionSettings();
}

//Detroyer
ConnectionSettings::~ConnectionSettings(){}

//export function
void ConnectionSettings::exportXMLSettings(){

    //this->importXMLSettings();
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

//paste previous functions
       int i;
       int j;
       for(i=0; i<(int)ConnectionSettings::tabFunction.size(); i++){
           writerStream.writeStartElement("Function");

           writerStream.writeStartElement("Definition");
               writerStream.writeTextElement("name", ConnectionSettings::tabFunction[i]->getNameFunction());
               writerStream.writeTextElement("program", ConnectionSettings::tabFunction[i]->getProgram());
               writerStream.writeTextElement("nbArgument", ConnectionSettings::tabFunction[i]->getNbArgument());
           writerStream.writeEndElement();

        for ( j = 0; j < (int)ConnectionSettings::tabArgument[i]->size(); j++){

            writerStream.writeStartElement("ArgumentsDefinition");
               writerStream.writeTextElement("ArgNumber", ConnectionSettings::tabArgument[i]->at(j)->getArgNumber());
                   writerStream.writeTextElement("ArgType", ConnectionSettings::tabArgument[i]->at(j)->getArgType());
                   writerStream.writeTextElement("ArgSuf", ConnectionSettings::tabArgument[i]->at(j)->getArgSuf());
                   writerStream.writeTextElement("ArgFacul", ConnectionSettings::tabArgument[i]->at(j)->getArgFac());
                   writerStream.writeTextElement("ArgOutline", ConnectionSettings::tabArgument[i]->at(j)->getArgOutline());

                   for(int m = 0; m < (int)ConnectionSettings::tabChoix[i]->at(j)->size(); m++){
                       writerStream.writeStartElement("ChoixList");
                           writerStream.writeTextElement("ChoixNom", ConnectionSettings::tabChoix[i]->at(j)->at(m)->getChoixNom());
                           writerStream.writeTextElement("ChoixParam", ConnectionSettings::tabChoix[i]->at(j)->at(m)->getChoixParam());
                           writerStream.writeTextElement("ChoixPrefix", ConnectionSettings::tabChoix[i]->at(j)->at(m)->getChoixPrefix());
                       writerStream.writeEndElement();
                   }
               writerStream.writeEndElement();
           }

           writerStream.writeEndElement();
           }

//add new function
        writerStream.writeStartElement("Function");

        writerStream.writeStartElement("Definition");
            writerStream.writeTextElement("name", name->text());
            writerStream.writeTextElement("program", program->text());
            writerStream.writeTextElement("nbArgument", nbArg->text());
        writerStream.writeEndElement();

        int curseur=0;
        for (int k = 0; k < nbArg->text().toInt(); k++){

            writerStream.writeStartElement("ArgumentsDefinition");
                writerStream.writeTextElement("ArgNumber", tabArgNumber[k]->text());
                writerStream.writeTextElement("ArgType", tabArgType[k]->currentText());

                QString az = tabArgSuf[k]->metaObject()->className();

                if(az=="QLineEdit"){
                   writerStream.writeTextElement("ArgSuf", reinterpret_cast<QLineEdit*>(tabArgSuf[k])->text());
                }else if(az=="QSpinBox"){
                   writerStream.writeTextElement("ArgSuf", reinterpret_cast<QSpinBox*>(tabArgSuf[k])->text());
                }

                writerStream.writeTextElement("ArgFacul", QString::number(tabArgfacul[k]->isChecked()));
                writerStream.writeTextElement("ArgOutline", tabArgOutline[k]->text());
//
                if(az=="QSpinBox"){
                    int curse = curseur;
                    for(int l=curse; l<reinterpret_cast<QSpinBox*>(tabArgSuf[k])->text().toInt()+curse; l++){

                        writerStream.writeStartElement("ChoixList");
                            writerStream.writeTextElement("ChoixNom", tabChoixNom[l]->text());
                            writerStream.writeTextElement("ChoixParam", tabChoixParam[l]->text());
                            writerStream.writeTextElement("ChoixPrefix", tabChoixPrefix[l]->text());
                        writerStream.writeEndElement();
                        curseur+=1;
                    }
                }else{
                    writerStream.writeStartElement("ChoixList");
                        writerStream.writeTextElement("ChoixNom", "pas de type choix");
                        writerStream.writeTextElement("ChoixParam", "pas de type choix");
                        writerStream.writeTextElement("ChoixPrefix", "pas de type choix");
                    writerStream.writeEndElement();
                }

            writerStream.writeEndElement();
        }

        if( nbArg->text().toInt()==0){
            writerStream.writeStartElement("ArgumentsDefinition");
                writerStream.writeTextElement("ArgNumber", "Sans Argument");
                writerStream.writeTextElement("ArgType", "Sans Argument");
                writerStream.writeTextElement("ArgSuf", "Sans Argument");
                writerStream.writeTextElement("ArgFacul", "Sans Argument");
                writerStream.writeTextElement("ArgOutline", "Sans Argument");
            writerStream.writeEndElement();

            writerStream.writeStartElement("ChoixList");
                writerStream.writeTextElement("ChoixNom", "pas de type choix");
                writerStream.writeTextElement("ChoixParam", "pas de type choix");
                writerStream.writeTextElement("ChoixPrefix", "pas de type choix");
            writerStream.writeEndElement();

        }

        writerStream.writeEndElement();
        writerStream.writeEndElement();
        writerStream.writeEndDocument();

        output.close();
    }
    ConnectionSettings::importXMLSettings();
    MainWindow::mwThis->enableMenu();
}

//import function called when the application boots
void ConnectionSettings::importXMLSettings(){

    //reset tabFunction and tabArgument
    if(ConnectionSettings::tabFunction.size()!=0){
        for(int i=0; i<(int)ConnectionSettings::tabFunction.size(); i++){
            ConnectionSettings::tabFunction[i]->~FuncFrame();

            for(int j=0; j<(int)ConnectionSettings::tabArgument[i]->size();j++){
                ConnectionSettings::tabArgument[i]->at(j)->~ArgumentFrame();
                for(int k=0; k<(int)ConnectionSettings::tabChoix[i]->at(j)->size(); k++){
                    ConnectionSettings::tabChoix[i]->at(j)->at(k)->~ChoixLigne();
                }
                ConnectionSettings::tabChoix[i]->at(j)->clear();
            }
            ConnectionSettings::tabArgument[i]->clear();
            ConnectionSettings::tabChoix[i]->clear();
        }
        ConnectionSettings::tabFunction.clear();
        ConnectionSettings::tabArgument.clear();
        ConnectionSettings::tabChoix.clear();

    }

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
                        ConnectionSettings::tabFunction.push_back(new FuncFrame());
                        ConnectionSettings::tabArgument.push_back(new std::vector<ArgumentFrame*>());
                        ConnectionSettings::tabChoix.push_back(new std::vector< std::vector <ChoixLigne*>*>());

                        ConnectionSettings::tabFunction[ConnectionSettings::tabFunction.size()-1]->setNameFunction(readerStream.readElementText());

                        while(readerStream.isStartElement()==false)
                        readerStream.readNext();
                    }
                    if(readerStream.name() == "program")
                    {
                        ConnectionSettings::tabFunction[ConnectionSettings::tabFunction.size()-1]->setProgram(readerStream.readElementText()) ;
                        readerStream.readNext();

                        while(readerStream.isStartElement()==false)
                        readerStream.readNext();
                    }
                    if(readerStream.name() == "nbArgument")
                    {
                        ConnectionSettings::tabFunction[ConnectionSettings::tabFunction.size()-1]->setNbArgument(readerStream.readElementText()) ;

                        while(readerStream.isStartElement()==false)
                        readerStream.readNext();

                    }

                }

                while(readerStream.name() == "ArgumentsDefinition")
                {
                    ConnectionSettings::tabChoix[ConnectionSettings::tabChoix.size()-1]->push_back(new std::vector <ChoixLigne*>());

                    readerStream.readNext();
                    while(readerStream.isStartElement()==false)
                    readerStream.readNext();

                    if(readerStream.name() == "ArgNumber")
                    {
                        ConnectionSettings::tabArgument[ConnectionSettings::tabArgument.size()-1]->push_back(new ArgumentFrame());
                        ConnectionSettings::tabArgument[ConnectionSettings::tabArgument.size()-1]->at(ConnectionSettings::tabArgument[ConnectionSettings::tabArgument.size()-1]->size()-1)->setArgNumber(readerStream.readElementText());
                        readerStream.readNext();

                        while(readerStream.isStartElement()==false)
                        readerStream.readNext();
                    }
                    if(readerStream.name() == "ArgType")
                    {
                        ConnectionSettings::tabArgument[ConnectionSettings::tabArgument.size()-1]->at(ConnectionSettings::tabArgument[ConnectionSettings::tabArgument.size()-1]->size()-1)->setArgType(readerStream.readElementText());
                        readerStream.readNext();

                        while(readerStream.isStartElement()==false)
                        readerStream.readNext();
                    }
                    if(readerStream.name() == "ArgSuf")
                    {
                        ConnectionSettings::tabArgument[ConnectionSettings::tabArgument.size()-1]->at(ConnectionSettings::tabArgument[ConnectionSettings::tabArgument.size()-1]->size()-1)->setArgSuf(readerStream.readElementText());
                        readerStream.readNext();

                        while(readerStream.isStartElement()==false)
                        readerStream.readNext();
                    }
                    if(readerStream.name() == "ArgFacul")
                    {
                        ConnectionSettings::tabArgument[ConnectionSettings::tabArgument.size()-1]->at(ConnectionSettings::tabArgument[ConnectionSettings::tabArgument.size()-1]->size()-1)->setArgFac(readerStream.readElementText());
                        readerStream.readNext();

                        while(readerStream.isStartElement()==false)
                        readerStream.readNext();
                    }
                    if(readerStream.name() == "ArgOutline")
                    {
                        ConnectionSettings::tabArgument[ConnectionSettings::tabArgument.size()-1]->at(ConnectionSettings::tabArgument[ConnectionSettings::tabArgument.size()-1]->size()-1)->setArgOutline(readerStream.readElementText());
                        while(readerStream.isStartElement()==false)
                        readerStream.readNext();

                    }

                        while(readerStream.name() == "ChoixList")
                        {
                            readerStream.readNext();
                            while(readerStream.isStartElement()==false)
                            readerStream.readNext();

                            if(readerStream.name() == "ChoixNom")
                            {
                                ConnectionSettings::tabChoix[ConnectionSettings::tabChoix.size()-1]->at(ConnectionSettings::tabChoix[ConnectionSettings::tabChoix.size()-1]->size()-1)->push_back(new ChoixLigne());
                                ConnectionSettings::tabChoix[ConnectionSettings::tabChoix.size()-1]->at(ConnectionSettings::tabChoix[ConnectionSettings::tabChoix.size()-1]->size()-1)->at(ConnectionSettings::tabChoix[ConnectionSettings::tabChoix.size()-1]->at(ConnectionSettings::tabChoix[ConnectionSettings::tabChoix.size()-1]->size()-1)->size()-1)->setChoixNom(readerStream.readElementText());
                                readerStream.readNext();

                                while(readerStream.isStartElement()==false)
                                readerStream.readNext();
                            }
                            if(readerStream.name() == "ChoixParam")
                            {
                                ConnectionSettings::tabChoix[ConnectionSettings::tabChoix.size()-1]->at(ConnectionSettings::tabChoix[ConnectionSettings::tabChoix.size()-1]->size()-1)->at(ConnectionSettings::tabChoix[ConnectionSettings::tabChoix.size()-1]->at(ConnectionSettings::tabChoix[ConnectionSettings::tabChoix.size()-1]->size()-1)->size()-1)->setChoixParam(readerStream.readElementText());
                                readerStream.readNext();

                                while(readerStream.isStartElement()==false)
                                readerStream.readNext();
                            }
                            if(readerStream.name() == "ChoixPrefix")
                            {
                                ConnectionSettings::tabChoix[ConnectionSettings::tabChoix.size()-1]->at(ConnectionSettings::tabChoix[ConnectionSettings::tabChoix.size()-1]->size()-1)->at(ConnectionSettings::tabChoix[ConnectionSettings::tabChoix.size()-1]->at(ConnectionSettings::tabChoix[ConnectionSettings::tabChoix.size()-1]->size()-1)->size()-1)->setChoixPrefix(readerStream.readElementText());
                                readerStream.readNext();

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
}

//slot called when the save button is triggered
void ConnectionSettings::validationConnectionSettings(){
    QString argPres;
    if(nbArg->text()=="0"){
        argPres= "<font color=red> Without any Argument !</font>";
    }else{
        for(int i=0; i<nbArg->text().toInt(); i++){
            argPres = argPres +"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color= black><b>- Arg " + QString::number(i+1) + " : </b>("
                    + tabArgOutline[i]->text() +") </font>";

            QString az = tabArgSuf[i]->metaObject()->className();
            QString cond;
            if(az=="QLineEdit"){
               cond = reinterpret_cast<QLineEdit*>(tabArgSuf[i])->text();
            }

            if(cond =="" && az != "QSpinBox"){
                argPres += "<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color=green>Without prefix</font>";
            }else if (az != "QSpinBox"){
                argPres += "<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color = green>Prefixe : " + cond + "</font>";
            }

            argPres += "<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Typed as : <font color = red>" + tabArgType[i]->currentText()+"</font>";
            int curseur =0;
            if(tabArgType[i]->currentText()=="Choice"){
                int curse = curseur;
                for(int j=curse; j<reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text().toInt()+curse; j++){
                    if(tabChoixPrefix[j]->text()==""){
                    argPres+="<br>Witout Prefix ; Choice Name : "+ tabChoixNom[j]->text()+" ; Parametre : "+ tabChoixParam[j]->text();
                    curseur+=1;
                    }else{
                        argPres+="<br>Prefix : "+ tabChoixPrefix[j]->text() +" ; Choice Name : "+ tabChoixNom[j]->text()+" ; Parametre : "+ tabChoixParam[j]->text();
                        curseur+=1;
                    }
                }

            }
            if(tabArgfacul[i]->isChecked()){
                argPres += "<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color= blue>Facultative </font>";
            }else{
                argPres += "<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color = blue>Mandatory </font>";
            }
            argPres += "<br>";
        }
    }

    int reponse = QMessageBox::question(this, "Connection Settings Validation",
                "Do you really  want to save these settings ? <br><br> <font color= black><b>Function Name : </b></font>"
                                        + name->text()+"<br> <font color= black><b>Program Name : </b></font>"
                                        + program->text()+"<br>"
                                        + argPres,
                                        QMessageBox::No | QMessageBox::Yes);

    if (reponse == QMessageBox::Yes){
            exportXMLSettings();
            QMessageBox::information(this, "Connection Setting Validated", "Export done");
            this->quit();
    }
}

void ConnectionSettings::testFunctionName(){
    boolean vide = false;
    if(name->text()==""){
        vide=true;
    }
    if(vide){
        QMessageBox::information(this, "Connection Setting Validation", "Please, specify the function name to be displayed");
    }else{
        this->testProgram();
    }
}


void ConnectionSettings::testProgram(){
    boolean vide = false;
    if(program->text()==""){
        vide=true;
    }
    if(vide){
        QMessageBox::information(this, "Connection Setting Validation", "Please, specify the program name");
    }else{
        this->testOutline();
    }
}

void ConnectionSettings::testOutline(){
    boolean vide = false;
    for (int k = 0; k < nbArg->text().toInt(); k++){
        if(tabArgOutline[k]->text()==""){
            vide=true;
        }
    }
    if(vide){
        QMessageBox::information(this, "Connection Setting Validation", "Please, specify all the Outline fields");
    }else{
        this->testChoix();
    }
}

void ConnectionSettings::testChoix(){
    boolean zero=false;
    for(int k = 0; k < nbArg->text().toInt(); k++){
        if(tabArgType[k]->currentText()=="Choice" && reinterpret_cast<QSpinBox*>(tabArgSuf[k])->text()=="0"){
            zero=true;
        }
    }

    boolean vide = false;
    for (int k = 0; k < tabChoixNom.size(); k++){
        if(tabChoixNom[k]->text()=="" || tabChoixParam[k]->text()==""){
            vide=true;
        }
    }
    if(zero){
        QMessageBox::information(this, "Connection Setting Validation", "Please, check your settings : there is at least one choice argument with no choice");
    }else if(vide){
        QMessageBox::information(this, "Connection Setting Validation", "Please, specify all the Choice fields");
    }else{
        this->testNecessaryArgument();
    }
}

void ConnectionSettings::testNecessaryArgument(){
    boolean vide = false;
    for (int k = 0; k < nbArg->text().toInt(); k++){
        if(tabArgType[k]->currentText()=="Necessary argument" ||tabArgType[k]->currentText()=="Current File"){
            if(reinterpret_cast<QLineEdit*>(tabArgSuf[k])->text()==""){
            vide=true;
            }
        }
    }
    if(vide){
        QMessageBox::information(this, "Connection Setting Validation", "Please, specify all the ""Necessary argument"" or ""Current File"" Prefix fields");
    }else{
        this->validationConnectionSettings();
    }
}


void ConnectionSettings::choixCrea(QString param){

    int num;
    for(int i=0; i<(int)tabArgType.size(); i++){
        if(tabArgType[i]==QObject::sender()){
        num=i;
        }
    }

    QString ab = tabArgSuf[num]->metaObject()->className();

    int position = 0;
    for(int i=0; i< num; i++ ){
        QString a = tabArgSuf[i]->metaObject()->className();
        if(a=="QSpinBox"){
            position+= 1 + reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text().toInt();
        }else if(a=="QLineEdit"){
            position+=1;
        }
    }


    if(param=="Choice" && ab !="QSpinBox"){

        reinterpret_cast<QLineEdit*>(tabArgSuf[num])->~QLineEdit();
        tabArgSuf[num] = new QSpinBox(this);
        tabArgSuf[num]->findChild<QLineEdit*>()->setReadOnly(true);

        gridTable->addWidget(tabArgSuf[num], position +1, 2);
        connect(tabArgSuf[num], SIGNAL(valueChanged(int)), this, SLOT(buildChoix()));

        //a mettre en fct
        tabChoixPrcdt.clear();
        for (int i=0; i<nbArg->text().toInt() ; i++){
            QString a = tabArgSuf[i]->metaObject()->className();
            if(a=="QSpinBox"){
                tabChoixPrcdt.push_back(reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text());
            }else if(a=="QLineEdit"){
                tabChoixPrcdt.push_back("pas de type choix");
            }
        }

    }else if(tabArgTypeMem[num]=="Choice" && param!="Choice"){
        if(reinterpret_cast<QSpinBox*>(tabArgSuf[num])->text().toInt()!=0){
           QMessageBox::information(this, "Warning", "You can not delete the last argument because some choice lines still exist. Please, delete some choice lines !");
           tabArgType[num]->setCurrentIndex(ConnectionSettings::argTypeList.indexOf("Choice"));
        }else{

        reinterpret_cast<QSpinBox*>(tabArgSuf[num])->~QSpinBox();
        tabArgSuf[num] = new QLineEdit(this);

        gridTable->addWidget(tabArgSuf[num], position +1, 2);

        //a mettre en fct
        tabChoixPrcdt.clear();
            for (int i=0; i<nbArg->text().toInt() ; i++){
                QString a = tabArgSuf[i]->metaObject()->className();
                if(a=="QSpinBox"){
                    tabChoixPrcdt.push_back(reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text());
                }else if(a=="QLineEdit"){
                    tabChoixPrcdt.push_back("pas de type choix");
                }
            }
        }
    }

    for(int i=tabArgTypeMem.size(); i>0; i--){
        tabArgTypeMem.pop_back();
    }

    for(int i=0; i<(int)tabArgType.size(); i++){
        tabArgTypeMem.push_back(tabArgType[i]->currentText());
    }

}

void ConnectionSettings::buildChoix(){

    // def de tri = nbr de choix en tt
    int nbLigneChoix=0;
    for(int i=0; i<nbArg->text().toInt(); i++){

        QString nat = tabArgSuf[i]->metaObject()->className();
        if(nat=="QSpinBox"){
            nbLigneChoix += reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text().toInt();
        }
    }

    // def de num = numero du sender
    int num;
    for(int i=0; i<(int)tabArgSuf.size(); i++){
        if(tabArgSuf[i]==QObject::sender()){
            num=i;
        }
    }

    // def de ici : somme des spinbox pour i < num
    int ici=0;
    for (int i=0; i<num; i++){
        QString a = tabArgSuf[i]->metaObject()->className();
        if(a=="QSpinBox"){
            ici += reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text().toInt();
        }
    }

    ici+= reinterpret_cast<QSpinBox*>(tabArgSuf[num])->text().toInt();

    int indexTabTampon=0;
    int indexTabTamponParam=0;
    int indexTabTamponPrefix=0;

    if(reinterpret_cast<QSpinBox*>(tabArgSuf[num])->text().toInt()> tabChoixPrcdt[num].toInt()){

        if(tabChoixNom.size()!=0){
            tabTampon.clear();
            for (int i=0; i<(int)tabChoixNom.size() ; i++){
                tabTampon.push_back(tabChoixNom[i]);
            }

            tabChoixNom.clear();

            for (int i=0; i< num; i++ ){

                QString a = tabArgSuf[i]->metaObject()->className();
                int ind=0;

                if(a=="QSpinBox"){
                    while(ind < reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text().toInt() ){
                        tabChoixNom.push_back(tabTampon[indexTabTampon]);
                        ind+=1;
                        indexTabTampon+=1;
                    }
                }
            }

            for(int i=0; i<tabChoixPrcdt[num].toInt(); i++){

                tabChoixNom.push_back(tabTampon[indexTabTampon]);
                indexTabTampon+=1;
            }
        }


        if(tabChoixParam.size()!=0){
            tabTamponParam.clear();
            for (int i=0; i<(int)tabChoixParam.size() ; i++){
                tabTamponParam.push_back(tabChoixParam[i]);
            }

           tabChoixParam.clear();

            for (int i=0; i< num; i++ ){

                QString a = tabArgSuf[i]->metaObject()->className();
                int ind=0;

                if(a=="QSpinBox"){
                    while(ind < reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text().toInt() ){
                        tabChoixParam.push_back(tabTamponParam[indexTabTamponParam]);
                        ind+=1;
                        indexTabTamponParam+=1;
                    }
                }
            }

            for(int i=0; i<tabChoixPrcdt[num].toInt(); i++){

                tabChoixParam.push_back(tabTamponParam[indexTabTamponParam]);
                indexTabTamponParam+=1;
            }
        }

        if(tabChoixPrefix.size()!=0){
            tabTamponPrefix.clear();
            for (int i=0; i<tabChoixPrefix.size() ; i++){
                tabTamponPrefix.push_back(tabChoixPrefix[i]);
            }

           tabChoixPrefix.clear();

            for (int i=0; i< num; i++ ){

                QString a = tabArgSuf[i]->metaObject()->className();
                int ind=0;

                if(a=="QSpinBox"){
                    while(ind < reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text().toInt() ){
                        tabChoixPrefix.push_back(tabTamponPrefix[indexTabTamponPrefix]);
                        ind+=1;
                        indexTabTamponPrefix+=1;
                    }
                }
            }

            for(int i=0; i<tabChoixPrcdt[num].toInt(); i++){

                tabChoixPrefix.push_back(tabTamponPrefix[indexTabTamponPrefix]);
                indexTabTamponPrefix+=1;
            }
        }


        tabChoixNom.push_back(new QLineEdit(this));
        tabChoixNom[tabChoixNom.size()-1]->setPlaceholderText("Name");
        tabChoixParam.push_back(new QLineEdit(this));
        tabChoixParam[tabChoixParam.size()-1]->setPlaceholderText("Parametre");
        tabChoixPrefix.push_back(new QLineEdit(this));
        tabChoixPrefix[tabChoixPrefix.size()-1]->setPlaceholderText("Prefix");


        for (int i= num +1; i< nbArg->text().toInt(); i++ ){
            QString a = tabArgSuf[i]->metaObject()->className();
            int ind=0;
            if(a=="QSpinBox"){
                while(ind < reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text().toInt() ){
                    tabChoixNom.push_back(tabTampon[indexTabTampon]);
                    tabChoixParam.push_back(tabTamponParam[indexTabTamponParam]);
                    tabChoixPrefix.push_back(tabTamponPrefix[indexTabTamponPrefix]);
                    ind+=1;
                    indexTabTampon+=1;
                    indexTabTamponParam+=1;
                    indexTabTamponPrefix+=1;
                }
            }
        }

        int indexGrid = 1 ;
        int indexTabChoixNom =0;
        int indexTabChoixNomLocal=0;

        for(int i = 0; i < nbArg->text().toInt(); i++){
            QString a = tabArgSuf[i]->metaObject()->className();

            if(a=="QLineEdit"){

                gridTable->addWidget(tabArgNumber[i], indexGrid , 0);
                gridTable->addWidget(tabArgType[i], indexGrid , 1);
                gridTable->addWidget(tabArgSuf[i], indexGrid , 2);
                gridTable->addWidget(tabArgfacul[i], indexGrid ,3);
                gridTable->addWidget(tabArgOutline[i], indexGrid ,4);
                gridTable->update();
                indexGrid +=1;



            }else if(a=="QSpinBox"){

                gridTable->addWidget(tabArgNumber[i], indexGrid , 0);
                gridTable->addWidget(tabArgType[i], indexGrid , 1);
                gridTable->addWidget(tabArgSuf[i], indexGrid , 2);
                gridTable->addWidget(tabArgfacul[i], indexGrid ,3);
                gridTable->addWidget(tabArgOutline[i], indexGrid ,4);
                indexGrid +=1;


                while(indexTabChoixNomLocal < reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text().toInt()){

                    gridTable->addWidget(tabChoixPrefix[indexTabChoixNom], indexGrid , 1);
                    gridTable->addWidget(tabChoixNom[indexTabChoixNom], indexGrid , 2);
                    gridTable->addWidget(tabChoixParam[indexTabChoixNom], indexGrid , 3);
                    indexGrid +=1;
                    indexTabChoixNomLocal +=1;
                    indexTabChoixNom+=1;
                }
                indexTabChoixNomLocal=0;
            }
        }

        tabChoixPrcdt.clear();
        for (int i=0; i<nbArg->text().toInt() ; i++){
            QString a = tabArgSuf[i]->metaObject()->className();
            if(a=="QSpinBox"){
                tabChoixPrcdt.push_back(reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text());
            }else if(a=="QLineEdit"){
                tabChoixPrcdt.push_back("pas de type choix");
            }
        }

        }else if(reinterpret_cast<QSpinBox*>(tabArgSuf[num])->text().toInt()<tabChoixPrcdt[num].toInt()){

            tabChoixNom[ici]->~QLineEdit();
            tabChoixParam[ici]->~QLineEdit();
            tabChoixPrefix[ici]->~QLineEdit();
            tabChoixNom.erase(tabChoixNom.begin()+ici);
            tabChoixParam.erase(tabChoixParam.begin()+ici);
            tabChoixPrefix.erase(tabChoixPrefix.begin()+ici);


            int indexGrid = 1 ;
            int indexTabChoixNom =0;
            int indexTabChoixNomLocal=0;

            for(int i = 0; i < nbArg->text().toInt(); i++){
                QString a = tabArgSuf[i]->metaObject()->className();

                if(a=="QLineEdit"){

                    gridTable->addWidget(tabArgNumber[i], indexGrid , 0);
                    gridTable->addWidget(tabArgType[i], indexGrid , 1);
                    gridTable->addWidget(tabArgSuf[i], indexGrid , 2);
                    gridTable->addWidget(tabArgfacul[i], indexGrid ,3);
                    gridTable->addWidget(tabArgOutline[i], indexGrid ,4);
                    gridTable->update();
                    indexGrid +=1;



                }else if(a=="QSpinBox"){

                    gridTable->addWidget(tabArgNumber[i], indexGrid , 0);
                    gridTable->addWidget(tabArgType[i], indexGrid , 1);
                    gridTable->addWidget(tabArgSuf[i], indexGrid , 2);
                    gridTable->addWidget(tabArgfacul[i], indexGrid ,3);
                    gridTable->addWidget(tabArgOutline[i], indexGrid ,4);
                    indexGrid +=1;


                    while(indexTabChoixNomLocal < reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text().toInt()){

                        gridTable->addWidget(tabChoixPrefix[indexTabChoixNom], indexGrid , 1);
                        gridTable->addWidget(tabChoixNom[indexTabChoixNom], indexGrid , 2);
                        gridTable->addWidget(tabChoixParam[indexTabChoixNom], indexGrid , 3);
                        indexGrid +=1;
                        indexTabChoixNomLocal +=1;
                        indexTabChoixNom+=1;
                    }
                    indexTabChoixNomLocal=0;
                }
            }

            tabChoixPrcdt.clear();
            for (int i=0; i<nbArg->text().toInt() ; i++){
                QString a = tabArgSuf[i]->metaObject()->className();
                if(a=="QSpinBox"){
                    tabChoixPrcdt.push_back(reinterpret_cast<QSpinBox*>(tabArgSuf[i])->text());
                }else if(a=="QLineEdit"){
                    tabChoixPrcdt.push_back("pas de type choix");
                }
            }

    }
}

//enable or not the facultative checkbox according to the argument type choosen
void ConnectionSettings::setEnability(QString param){
    for(int i=0; i<tabArgfacul.size(); i++){
        if(tabArgType[i]->currentText()=="Necessary argument" || tabArgType[i]->currentText()=="Current File"){
            tabArgfacul[i]->setChecked(false);
            tabArgfacul[i]->setEnabled(false);
        }else{
            tabArgfacul[i]->setEnabled(true);
        }
        if(tabArgType[i]->currentText()=="Necessary argument"){
            reinterpret_cast<QLineEdit*>(tabArgSuf[i])->setPlaceholderText("Put the argument here");
        }else{
            if(tabArgType[i]->currentText()!="Choice"){
                reinterpret_cast<QLineEdit*>(tabArgSuf[i])->setPlaceholderText("");
            }
        }
    }
}
//QMessageBox::critical(this, "Error", "No");


//MainWindow* castParent = reinterpret_cast<MainWindow*> (parent);//->openConnectionForm();
