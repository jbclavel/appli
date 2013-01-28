#include <QtTest/QtTest>
#include "PHIOTest.h"

/**
 * @file TestRunner.cpp
 * @brief this file contains the main program for test mode
 */

int main (int argc, char ** argv) {
	PHIOTest test1;
	QTest::qExec(&test1);
	return 0;
}
