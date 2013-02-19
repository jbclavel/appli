#ifndef FUNCTIONFORM_H
#define FUNCTIONFORM_H

#include <QtGui>
//#include "ArgumentFrame.h"
//#include "FuncFrame.h"

class FunctionForm : public QDialog
{
    Q_OBJECT

    public:
        FunctionForm(QString fileName);
        ~FunctionForm();

        //std::vector<QLabel*> tabArgNumber;
        //std::vector<QComboBox*> tabArgType ;
        //std::vector<QLineEdit*> tabArgSuf;
        //std::vector<QCheckBox*> tabArgfacul;
        //int nbArgPrcdt;

    private slots:
        //void buildTable();
        //void quit();
        //void exportXMLSettings();
        //void validationConnectionSettings();
        void openConnectionForm();
        void quit();
        void fctBack();
        void launchCompute();


    private:
        QString pathTab;
        QComboBox *choix;
        QPushButton *Yes;
        QPushButton *Cancel;
        QHBoxLayout *buttonLayout;
        QVBoxLayout *totalLayout;

        QString functionChosen;
        int indexFctChosen;
        std::vector<QGroupBox*> tabGroupBox;
        std::vector<QFormLayout*> tabQFormLayout;
        std::vector<QWidget*> tabLineEdit;
        std::vector<QString*> tabNomLine;


        QPushButton *Ok;
        QPushButton *back;
        QHBoxLayout *buttonLayout2;



};
        /*
        QLineEdit *name;
        QLineEdit *program;
        QSpinBox *nbArg;
        QFormLayout *definitionLayout;
        QGroupBox *groupDefinition;

        //Groupe : Table
        QGridLayout *gridTable;
            //en-tête
        QLabel *enTeteArgNum ;
        QLabel *enTeteArgTyp ;
        QLabel *enTeteArgSuf ;
        QLabel *enTeteArgFac ;
            //Argument types list
        QStringList argTypeList;

        QVBoxLayout *tableLayout;
        QGroupBox *groupTable;

        //button
        QPushButton *Save;
        QPushButton *Cancel;
        QHBoxLayout *boutonsLayout;

        //Mise en page générale
        QVBoxLayout *globalLayout;
*/

#endif // FUNCTIONFORM_H
