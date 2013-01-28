#include <boost/lexical_cast.hpp>
#include "Process.h"


Process::Process (SortPtr s, const int& n) : sort(s), number(n) {}


// output for DOT file
string Process::toDotString () {
	string n = boost::lexical_cast<string>(number);
	return getDotName() + " [label=\"" + n + "\"];\n";
}


// build name for DOT file
string Process::getDotName () {
	string n = boost::lexical_cast<string>(number);
	return sort->getName() + "_p" + n;
}


// setter
void Process::setGProcess(GProcessPtr gPPtr) {
    gProcess = gPPtr;
}


// getters
int Process::getNumber () { return number; }
SortPtr Process::getSort () { return sort; }
GProcessPtr Process::getGProcess() { return gProcess; }
