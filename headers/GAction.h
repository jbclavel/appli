#pragma once
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <list>
#include <utility>
#include "GVEdge.h"
#include "PH.h"
#include "PHScene.h"
#include "Action.h"
#include "GSort.h"


/**
  * @file GAction.h
  * @brief header for the GAction class
  * @author PAPPL_2012
  *
  */

class GAction;
typedef boost::shared_ptr<GAction> GActionPtr;
class Action;
typedef boost::shared_ptr<Action> ActionPtr;
class PHScene;

using std::pair;


/**
  * @class GAction
  * @brief contains style and layout info to draw an action
  *
  */
class GAction {

	public:

    /**
      * @brief constructor
      *
      * @param ActionPtr the related Action object
      * @param GVEdge the object that contains style and layout info for hit arrow
      * @param GVEdge the object that contains style and layout info for bounce (result) arrow
      * @param PHScene the related scene
      */
		GAction(ActionPtr a, GVEdge e, GVEdge f, PHScene* sc);

        ~GAction();

     /**
       * @brief gets the display
       *
       * @return QGraphicsItem the graphical item representing the Action
       */
		QGraphicsItem* getDisplayItem (void);

        /**
          * @brief gets the action
          *
          */
        ActionPtr getAction();

        /**
          * @brief gets the source GProcess item
          *
          * @param GProcessPtr a pointer to the source GProcess item
          */
        GSortPtr getSourceSort();

        /**
          * @brief gets the target GProcess item
          *
          * @param GProcessPtr a pointer to the target GProcess item
          */
        GSortPtr getTargetSort();

        /**
          * @brief gets the result GProcess item
          *
          * @param GProcessPtr a pointer to the result GProcess item
          */
        GSortPtr getResultSort();

	
	protected:
	
        /**
          * @brief the PHScene related to the Action
          *
          */
		PHScene* scene;

        /**
          * @brief the graphical item representing the Action
          *
          */
		QGraphicsItem* display;

        /**
          * @brief the related Action
          *
          */
        ActionPtr action;

        /**
          * @brief the pair of graphical items representing the tails of the arrows of the Action
          *
          */
		pair<QGraphicsPathItem*, QGraphicsPathItem*> 		arrowTails;

        /**
          * @brief the pair of graphical items representing the heads of the arrows of the Action
          *
          */
        pair<QGraphicsPolygonItem* , QGraphicsPolygonItem*>	arrowHeads;

        /**
          * @brief the edges related to the arrows
          *
          */
		pair<GVEdge, GVEdge> edges;

        /**
          * @brief draws the head of the arrow
          *
          * @param GVEdge the edge related to the arrow
          * @param Qcolor the color of the arrow
          *
          * @return QGraphicsPolygonItem* the graphical item representing the head of the arrow
          *
          */
		QGraphicsPolygonItem* makeArrowHead(const GVEdge& e, const QColor& color);		
	
};
