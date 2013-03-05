#ifndef HEADER_CONNECTIONSETTINGS
#define HEADER_CONNECTIONSETTINGS

#include <QtGui>
#include "ArgumentFrame.h"
#include "FuncFrame.h"
#include "ChoixLigne.h"





class ConnectionSettings : public QDialog
{
    Q_OBJECT


    public:
        ConnectionSettings();
        ~ConnectionSettings();

        std::vector<QLabel*> tabArgNumber;
        std::vector<QComboBox*> tabArgType;

        std::vector<QString> tabArgTypeMem;

        std::vector<QWidget*> tabArgSuf;
        std::vector<QCheckBox*> tabArgfacul;
        std::vector<QLineEdit*> tabArgOutline;


        std::vector<QLineEdit*> tabTampon;
        std::vector<QLineEdit*> tabTamponParam;

        std::vector<QLineEdit*> tabChoixNom;
        std::vector<QLineEdit*> tabChoixParam;

        int nbArgPrcdt;
        int rowMax;
        std::vector<QString> tabChoixPrcdt;

        static std::vector<FuncFrame*> tabFunction;
        static std::vector< std::vector<ArgumentFrame*>* > tabArgument;
        static std::vector< std::vector< std::vector<ChoixLigne*>*>*> tabChoix;
        static void importXMLSettings();
        static QStringList argTypeList;

    private slots:
        void buildTable();
        void quit();
        void exportXMLSettings();  
        void validationConnectionSettings();
        void testFunctionName();
        void testProgram();
        void testOutline();
        void testChoix();
        void choixCrea(QString param);
        void buildChoix();
        void setEnability(QString param);


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
        QLabel *enTeteArgOutline;
            //Argument types list

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
