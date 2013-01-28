#include <iostream>
#include <boost/lexical_cast.hpp>
#include "Action.h"


Action::Action (ProcessPtr source_, ProcessPtr target_, ProcessPtr result_, const bool& infiniteRate_, const double& r_, const int& sa_)
    : source(source_), target(target_), result(result_), infiniteRate(infiniteRate_), r(r_), sa(sa_) {}


// getters
ProcessPtr Action::getSource() { return source; }
ProcessPtr Action::getTarget() { return target; }
ProcessPtr Action::getResult() { return result; }


// output for DOT file
string Action::toDotString (void) {
	string res;

    res += 				source->getDotName()
			+ " -> " + 	target->getDotName()
			+ ";\n";
    res += 				target->getDotName()
			+ " -> " + 	result->getDotName()
			+ ";\n";

    return res;
}


// output for PH file
string Action::toString (void) {

	return 		source->getSort()->getName()
			+	" "
			+	boost::lexical_cast<string>(source->getNumber())
			+ 	" -> " 
			+ 	target->getSort()->getName()
			+	" "
			+	 boost::lexical_cast<string>(target->getNumber())
			+	" "
			+ 	 boost::lexical_cast<string>(result->getNumber())
			+	" @"
			+	(infiniteRate ? 
					"Inf" 
					:
					(r == (int) r) ? 
						boost::lexical_cast<string>(r) + "."
						:
						boost::lexical_cast<string>(r)
				)						
			+	"~"
			+	 boost::lexical_cast<string>(sa)
			+	"\n"
			;
}
