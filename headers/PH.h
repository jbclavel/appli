#pragma once
#include <list>
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Action.h"
#include "GVGraph.h"
#include "PHScene.h"
#include "Process.h"
#include "Sort.h"

/**
  * @file PH.h
  * @brief header for the PH class
  * @author PAPPL_2012
  *
  */

using std::list;
using std::map;
using std::string;
using boost::make_shared;

// mutual inclusion
class Action;
typedef boost::shared_ptr<Action> ActionPtr;

class PH;
typedef boost::shared_ptr<PH> PHPtr;
typedef std::pair<string, SortPtr> SortEntry;


/**
  * @brief builds cluster name for graphviz, from Sort name
  * @param String the Sort's name to be adapted for graphviz cluster
  */
static inline QString makeClusterName (string s) {
	return QString::fromStdString("cluster_" + s);
}

/**
  * @brief builds node name for graphviz, from Process name
  * @param ProcessPtr pointer to the Process which name is to be adapted for graphviz node
  */
static inline QString makeProcessName (ProcessPtr p) {
	return QString::fromStdString(p->getSort()->getName()) + QString("_%1").arg(p->getNumber());
}


/**
  * @class PH
  * @brief represents an entire process hitting as defined in a PH file
  *
  */
class PH {

	public:

        /**
          * @brief constructor
          *
          */
		PH();

        /**
          * @brief adds a sort to the PH
          * @param SortPtr the sort to add
          */
		void addSort(SortPtr s);

        /**
          * @brief adds an action to the PH
          * @param ActionPtr the action to add
          */
		void addAction(ActionPtr a);

        /**
          * @brief getter for a sort
          *
          */
		SortPtr getSort(string const&);

        /**
          * @brief getter for the actions of the PH
          *
          */
        list<ActionPtr> getActions(void);

        /**
          * @brief getter for the sorts of the PH
          *
          */
        list<SortPtr> getSorts(void);

        /**
          * @brief getter for the processes of the PH
          *
          */
		list<ProcessPtr> getProcesses(void);		

        /**
          * @brief gives a text representation of the process hitting (as it would be in a .ph file)
          * @return string the text representation of the process hitting in PH format
          */
        string toString (void);

        /**
          * @brief gives a text representation of the process hitting (in .dot format, used in Graphviz)
          * @return string the text representation of the process hitting in DOT format
          */
        string toDotString (void);

        /**
          * @brief calls for the process hitting in its scene
          * @details time-expensive method, calls the toGVGraph method
          *
          */
		void render (void);

        /**
          * @brief makes a representation of the process hitting as a graph
          * @details calls graphviz to calculate the optimized graph
          * @return GVGraphPtr pointer to the Graph built
          *
          */
		GVGraphPtr toGVGraph(void);

        /**
          * @brief updates the representation of the process hitting as a graph after user's customizations
          * @details calls graphviz to calculate the graph
          * @return
          *
          */
        GVGraphPtr updateGVGraph(PHScene *scene);

        /**
          * @brief outputs for display
          * @return PHScenePtr pointer to the Scene built
          */
        PHScenePtr getGraphicsScene (void);

        /**
          * @brief getter for the stochasticity absorption
          *
          */
		int 	getStochasticityAbsorption ();

        /**
          * @brief setter for the stochasticity absorption
          *
          */
		void 	setStochasticityAbsorption (int sa);

        /**
          * @brief getter for the default rate;
          *
          */
		double 	getDefaultRate ();

        /**
          * @brief setter for the default rate
          *
          */
		void	setDefaultRate (double r);

        /**
          * @brief getter for the Infinite Default Rate
          *
          */
		bool 	getInfiniteDefaultRate ();

        /**
          * @brief setter for the Infinitite Default Rate
          *
          */
		void 	setInfiniteDefaultRate (bool b);

        QStringList* positionHit;

	protected:

		//Headers

        /**
          * @brief default value for stochasticity absorption
          *
          */
		int stochasticity_absorption;

        /**
          * @brief boolean to know if the default rate is or is not infinite
          * @details if true then the value of default rate makes no sense
          *
          */
        bool infinite_default_rate;

        /**
          * @brief default value for rate
          *
          */
		double default_rate;

		//Content

        /**
          * @brief map of the sorts, linked with their names
          *
          */
		map<string, SortPtr> sorts;

        /**
          * @brief list of the actions
          *
          */
		list<ActionPtr> actions;
		
		//Display

        /**
          * @brief graphical object representing the process hitting
          *
          */
		PHScenePtr scene;		

};
