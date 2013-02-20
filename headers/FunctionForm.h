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

    signals :


    private slots:
        //void buildTable();
        //void quit();
        //void exportXMLSettings();
        //void validationConnectionSettings();
        void openConnectionForm();
        void quit();
        void fctBack();
        void launchCompute();
        void enableForm(int state);
        void getName();
        void getDirectoryName();


    private:
        QString pathTab;
        int compteurFile;
        int indexFile;
        int indexDirec;


        QComboBox *choix;
        QPushButton *Yes;
        QPushButton *Cancel;
        QHBoxLayout *buttonLayout;
        QVBoxLayout *totalLayout;

        QString functionChosen;
        int indexFctChosen;
        std::vector<QGroupBox*> tabGroupBox;
        std::vector<QFormLayout*> tabQFormLayout;
        std::vector<QHBoxLayout*> tabQHBox;
        std::vector<QCheckBox*> tabQcheckBox;
        std::vector<QWidget*> tabLineEdit;
        std::vector<QString*> tabNomLine;

        std::vector<QPushButton*> tabButtonFile;
        std::vector<QPushButton*> tabButtonDirec;


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
