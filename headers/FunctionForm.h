#ifndef FUNCTIONFORM_H
#define FUNCTIONFORM_H
#include <QtGui>

class FunctionForm : public QDialog
{
    Q_OBJECT

    public:
    //the entry argument fileName let us have the current path tab
    //see QString pathTab
        FunctionForm(QString fileName);
        ~FunctionForm();


    signals :

    private slots:
        //open the dynamic window according to the XML file
        void openConnectionForm();

        //quit the first window which allows user to choose a function
        void quit();

        //let to go from the dynamic window (connection form) to the first window
        void fctBack();

        //launch the MainWindow function named Compute
        void launchCompute();

        //manage the enable/disable functionnality according to the field "Taken into account"
        //the entry argument state is useless
        void enableForm(int state);

        //function which let us have the .ph File Name selected in a QFileDialog window
        void getNamePH();

        //function which let us have the File Name selected in a QFileDialog window
        void getName();

        //function which let us have the Directory Name selected in a QFileDialog window
        void getDirectoryName();

        //function which let us have the directory name selected in a QFileDialog window for the case File not existing
        void getDirectoryNameFileNotExisting();

        void testEmpty();

    private:
        //variable containing the path of the current file .ph open
        QString pathTab;


        //variable allow us to manage the .ph files
        int indexFilePH;

        //variable allow us to manage the files
        int indexFile;

        //variable allow us to manage the directories
        int indexDirec;

        //variable allow us to manage the File not existing
        int indexFileNotExisting;

        //widget to choose the function
        QComboBox *choix;

        //2 buttons
        QPushButton *Yes;
        QPushButton *Cancel;

        //wiget for the display of the buttons
        QHBoxLayout *buttonLayout;

        //global layout
        QVBoxLayout *totalLayout;

        //scroll
        QWidget *widget;
        QScrollArea *area;
        QVBoxLayout *layoutTotal;

        //Name and index of the function chosen
        QString functionChosen;
        int indexFctChosen;

        //tabs of dynamics widgets of the main window (the form)
        std::vector<QGroupBox*> tabGroupBox;
        std::vector<QFormLayout*> tabQFormLayout;
        std::vector<QHBoxLayout*> tabQHBox;
        std::vector<QCheckBox*> tabQcheckBox;
        std::vector<QWidget*> tabLineEdit;

        std::vector<QPushButton*> tabButtonFile;
        std::vector<QPushButton*> tabButtonFilePH;
        std::vector<QPushButton*> tabButtonDirec;
        std::vector<QPushButton*> tabButtonFileNotExisting;

        //2 buttons
        QPushButton *Ok;
        QPushButton *back;

        //wiget for the display of the buttons of the main window (the form)
        QHBoxLayout *buttonLayout2;
};
#endif // FUNCTIONFORM_H
