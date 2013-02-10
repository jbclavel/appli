#ifndef HEADER_CONNECTIONSETTINGS
#define HEADER_CONNECTIONSETTINGS

#include <QtGui>

class ConnectionSettings : public QWidget
{
    Q_OBJECT


    public:
        ConnectionSettings();
        std::vector<QLabel*> tabArgNumber;
        std::vector<QComboBox*> tabArgType ;
        std::vector<QLineEdit*> tabArgSuf;
        std::vector<QCheckBox*> tabArgfacul;
        int nbArgPrcdt;

    private slots:
        void buildDynamicPage();
        //void genererCode();

    private:
        QLineEdit *name;
        QLineEdit *program;
        QSpinBox *nbArg;

        //QValidator *validator;

        QStringList argTypeList;
        QComboBox *argType ;


        QGridLayout *gridTable;
        QCheckBox *facultatif;
        QGroupBox *groupDefinition;

        QPushButton *Save;
        QPushButton *Cancel;

        QVBoxLayout *tableLayout;
        QGroupBox *groupTable;
        QFormLayout *definitionLayout;
        QHBoxLayout *boutonsLayout;
        QVBoxLayout *globalLayout;


};

#endif
