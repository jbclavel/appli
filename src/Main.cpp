#include <QApplication>
#include <QtGui>
#include "MainWindow.h"

/*!
 * @file Main.cpp
 * @author Jean-Michel
 * @brief Principal Program
 * @details Defines the call
 */

#include <iostream>
#include "IO.h"
#include "GVGraph.h"
#include "PHIO.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();

}
