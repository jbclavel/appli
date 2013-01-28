#include <boost/filesystem.hpp>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "Exceptions.h"
#include "IO.h"


// read file content (path given as parameter) as string
string IO::readFile (string const& path) {

	using namespace boost::filesystem;
	IO::fileLocationCheck(path);
	
    // open text file in read only mode
	QFile file(QString::fromUtf8(path.c_str()));
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		throw io_error() << file_info(path);
	QTextStream in(&file);
	
	return in.readAll().toStdString();
	
}


// check that the file which path is given as parameter exists
void IO::fileLocationCheck (string const& path) {

	using namespace boost::filesystem;
	
    // sanity checks
	if (!exists(path)) 		
		throw file_not_exist() << file_info(path);	
	if (!is_regular_file(path))
		throw not_regular_file() << file_info(path);
		
}


// write string as file (which path is given as parameter)
void IO::writeFile (string const& path, string const& content) {

    // open text file in write only mode
	QFile file(QString::fromUtf8(path.c_str()));
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    // write string
    QTextStream out(&file);
    out << QString::fromUtf8(content.c_str());

    file.close();
	
}
