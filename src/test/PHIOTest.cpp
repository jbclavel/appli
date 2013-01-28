#include <string>
#include "PHIOTest.h"
#include "PHIO.h"

using std::string;


// test parser on various operations
void PHIOTest::parse_data()  {
	QTest::addColumn<QString>("source");
	QTest::newRow("declarations") 	<< "tests/1_declarations.ph";
	QTest::newRow("cooperativity") 	<< "tests/2_cooperativity.ph";
	QTest::newRow("actions") 		<< "tests/3_actions.ph";
	QTest::newRow("knockdown") 		<< "tests/4_knockdown.ph";
	QTest::newRow("rm") 			<< "tests/5_rm.ph";
	QTest::newRow("headers") 		<< "tests/6_headers.ph";
	QTest::newRow("footer") 		<< "tests/7_footer.ph";
	QTest::newRow("grn") 			<< "tests/8_grn.ph";
	QTest::newRow("comments") 		<< "tests/9_comments.ph";
	QTest::newRow("metazoan") 		<< "tests/metazoan.ph";
	QTest::newRow("ERBB_G1") 		<< "tests/ERBB_G1-S.ph";
	QTest::newRow("tcrsig40") 		<< "tests/tcrsig40.ph";
 }


 void PHIOTest::parse()  {
	QFETCH(QString, source);
	QVERIFY(PHIO::canParseFile(source.toStdString()));
 }
