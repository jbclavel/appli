#ifndef HEADER_CONNECTIONSETTINGS
#define HEADER_CONNECTIONSETTINGS

#include <QtGui>
#include "ArgumentFrame.h"
#include "FuncFrame.h"


class ConnectionSettings : public QWidget
{
    Q_OBJECT


    public:
        ConnectionSettings();
        ~ConnectionSettings();
        std::vector<QLabel*> tabArgNumber;
        std::vector<QComboBox*> tabArgType ;
        std::vector<QLineEdit*> tabArgSuf;
        std::vector<QCheckBox*> tabArgfacul;
        int nbArgPrcdt;

        static std::vector<FuncFrame*> tabFunction;
        static std::vector<ArgumentFrame*> tabArgument;


    private slots:
        void buildTable();
        void quit();
        void exportXMLSettings();
        void importXMLSettings();


    private:
        //Groupe : définition
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

};
#endif
