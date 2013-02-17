#ifndef FUNCTIONFORM_H
#define FUNCTIONFORM_H

#include <QtGui>
//#include "ArgumentFrame.h"
//#include "FuncFrame.h"

class FunctionForm : public QWidget
{
    Q_OBJECT

    public:
        FunctionForm();
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

    private:
        QComboBox *choix;
        QPushButton *Yes;
        QPushButton *Cancel;
        QHBoxLayout *buttonLayout;
        QVBoxLayout *totalLayout;

        QComboBox *choixa;
        QPushButton *Yesa;
        QPushButton *Cancela;
        QVBoxLayout *totalLayouta;



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
