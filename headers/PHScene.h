#pragma once
#include <boost/shared_ptr.hpp>
#include <QObject>
#include <QGraphicsScene>
#include <map>
#include <string>
#include "GAction.h"
#include "GProcess.h"
#include "GSort.h"
#include "GVGraph.h"


/**
  * @file PHScene.h
  * @brief header for the PHScene class
  * @author PAPPL_2012
  *
  */

using std::map;
using std::string;

// mutual inclusions
class PH;
class GProcess;
typedef boost::shared_ptr<GProcess> GProcessPtr;
class GSort;
typedef boost::shared_ptr<GSort> GSortPtr;
class GAction;
typedef boost::shared_ptr<GAction> GActionPtr;

class PHScene;
typedef boost::shared_ptr<PHScene> PHScenePtr;

typedef std::pair<string, GSortPtr> GSortEntry;


/**
  * @class PHScene
  * @brief the graphic object representing the process hitting
    extends QGraphicsScene
  *
  */
class PHScene: public QGraphicsScene {
	
	public:
        /**
          * @brief constructor
          *
          */
        PHScene(PH* _ph);

        /**
          * @brief forces the re-calculation of the layout of the scene
          *
          */
        void doRender(void);

        /**
          * @brief gets a GSort by its related Sort's name
          * @param string the name of the (G)Sort to get
          * @return GSortPtr pointer to the GSort to get
          *
          */
		GSortPtr getGSort (const string& s);

        /**
          * @brief getter for sorts
          *
          */
        map<string, GSortPtr> getGSorts();

        /**
          * @brief get the processes
          *
          */
        std::vector<GProcessPtr> getProcesses();

        /**
          * @brief get the actions
          *
          */
        std::vector<GActionPtr> getActions();

        /**
          * @brief hides all action arrows
          *
          */
        void hideActions();

        /**
          * @brief shows all the action arrows which are NOT related to hidden sorts
          *
          */
        void showActions();

        /**
          * @brief recalculates the graph, functions of customized GSort items positions
          *
          */
        void updateGraph();

        /**
          * @brief recalculates the graph, functions of customized GSort items positions
          *
          */
        void updateGraphForImport();




	protected:

        /**
          * @brief the related process hitting
          *
          */
		PH* ph;

        /**
          * @brief clears the scene and adds the elements composing the representation of the process hitting
          *
          */
		void draw(void);

        /**
          * @brief map of the Sorts drawn in the scene: the keys are the names of the Sorts
          *
          */
        map<string, GSortPtr> sorts;

        /**
          * @brief vector of the Processes drawn in the scene
          *
          */
		std::vector<GProcessPtr> processes;

        /**
          * @brief vector of the Actions drawn in the scene
          *
          */
        std::vector<GActionPtr> actions;

        /**
          * @brief creates GAction items from graphviz graph (GVEdge structs)
          *
          * @param GVGraphPtr a smart pointer to the graphviz graph to convert
          *
          */
        void createActions(GVGraphPtr graph);

};
