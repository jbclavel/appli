#ifndef HEADER_CONNECTIONSETTINGS
#define HEADER_CONNECTIONSETTINGS

#include <QtGui>

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

    private slots:
        void buildTable();
        void quit();

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
