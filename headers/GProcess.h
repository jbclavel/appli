#pragma once
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <list>
#include "PH.h"
#include "Process.h"
#include "GVNode.h"

/**
  * @file GProcess.h
  * @brief header for the GProcess class
  * @author PAPPL_2012
  *
  */

class GProcess;
typedef boost::shared_ptr<GProcess> GProcessPtr;
class Process;
typedef boost::shared_ptr<Process> ProcessPtr;


/**
  * @class GProcess
  * @brief contains style and layout info to draw a process
  *
  */
class GProcess {

	public:

        /**
          * @brief constructor
          *
          * @param ProcessPtr the related Process object
          * @param GVNode the object that contains style and layout info
          * @param qreal graph DPI value (graphviz)
          */
        GProcess(ProcessPtr p, GVNode n, qreal graphDPI);

		~GProcess();

        /**
          * @brief gets the display
          *
          * @return QGraphicsItem the graphical item representing the Process
          */
		QGraphicsItem* getDisplayItem (void);

        /**
          * @brief gets the ellipse
          *
          */
        QGraphicsEllipseItem* getEllipseItem();

        /**
          * @brief gets the related GVNode
          *
          * @return the related GVNode
          */
        GVNode* getNode();

        /**
          * @brief gets the rect item that represents the margin of this GProcess
          *
          */
        QGraphicsRectItem* getMarginRect();

        /**
          * @brief updates the related GVNode's coordinates with a vector
          *
          * @param int dx the horizontal component of the translation
          * @param int dy the vertical component of the translation
          *
          */
        void setNodeCoords(int dx, int dy);

        /**
          * @brief updates the related GVNode's coordinates with a point
          *
          * @param int x the horizontal coordinate of the node
          * @param int y the vertical coordinate of the node
          *
          */
        void setNodeCoordsForImport(int x, int y);

        /**
          * @brief sets the related GVNode structure
          *
          * @param GVNode the GVNode to copy geometry from
          *
          */
        void setNode(GVNode gvnode);

        /**
          * @brief checks collisions with margins of other GProcess items (see graph attribute "sep" in GVSubGraph)
          *
          * @return bool true if this GProcess' margin collides with another one's margin (of a different sort), else false
          */
        bool checkCollisions();


        /**
          * @brief gets the related Process
          *
          */

        ProcessPtr* getProcess();


	
	protected:

        /**
          * @brief the graphical item representing the Process
          *
          */
		QGraphicsItem* display;

        /**
          * @brief the graphical item representing the ellipse of the Process
          *
          */
		QGraphicsEllipseItem* ellipse;

        /**
          * @brief the graphical item representing the text of the Process
          *
          */
        QGraphicsTextItem* text;

        /**
          * @brief the related Process
          *
          */
		ProcessPtr process;

        /**
          * @brief the related node
          *
          */
		GVNode node;

        /**
          * @brief the margin around this process, must exclude any other process' margin (cf. graphviz attribute "pos" in GVSubGraph)
          *
          */
        QGraphicsRectItem* marginRect;

        /**
          * @brief arbitrarily-chosen key for "margin item" data
          *
          */
        static const int marginZone;

        /**
          * @brief arbitrarily-chosen key for sort name data
          *
          */
        static const int sortName;

};
