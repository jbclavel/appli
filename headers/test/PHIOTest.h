#include <QtTest/QtTest>

/**
  * @file PHIOTest.h
  * @brief header for the PHIOTest class
  * @author PAPPL_2012
  */

/**
  * @class PHIOTest
  * @brief checks that PH files are parsed successfully
  */
 class PHIOTest: public QObject {
    Q_OBJECT
	private slots:
		void parse_data();
		void parse();
 };
