#pragma once
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QColor>
#include <list>
#include "PH.h"
#include "Sort.h"
#include "GVCluster.h"

/**
  * @file GSort.h
  * @brief header for the GSort class
  * @author PAPPL_2012
  *
  */

class GSort;
typedef boost::shared_ptr<GSort> GSortPtr;


/**
  * @class GSort
  * @brief contains style and layout info to draw a Sort
  *
  */
class GSort : public QGraphicsRectItem {

	public:

        /**
          * @brief constructor
          *
          * @param SortPtr the related Sort object
          * @param GVCluster the object that contains style and layout info
          */
		GSort(SortPtr p, GVCluster c);

		~GSort();

        /**
          * @brief get the rect item
          *
          */
        QGraphicsRectItem* getRect();

        /**
          * @brief the color used by the Actions that have this Sort as source
          *
          */
		QColor* color;

        /**
          * @brief Handles mouse press event (handles drag start)
          *
          * @param QGraphicsSceneMouseEvent the event to be handled
          */
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

        /**
          * @brief Handles mouse move event (handles drag)
          *
          * @param QGraphicsSceneMouseEvent the event to be handled
          */
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

        /**
          * @brief Handles mouse release event (handles drop)
          *
          * @param QGraphicsSceneMouseEvent the event to be handled
          */
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

        /**
          * @brief Handles context menu event (typically on right click)
          *
          * @param QGraphicsSceneContextMenuEvent the event to be handled
          */
        void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

        /**
          * @brief gets the related Sort object
          *
          * @return SortPtr a pointer to the related Sort object
          */
        SortPtr getSort();

        /**
          * @brief gets the related GVCluster which stores GSort absolute coordinates
          *
          * @return GVCluster the related GVCluster
          */
        GVCluster getCluster();

        /**
          * @brief gets the text of the sort
          *
          */
        QGraphicsTextItem* getText();

        /**
          * @brief updates the position of this GSort after drag&drop
          *
          */
        void updatePosition();

        /**
          * @brief hides this GSort setting opacity to 0
          */
        void hide();

        /**
          * @brief show the GSort setting full opacity
          */
        void show();

        /**
          * @brief indicates whether or not this GSort is made visible (test based on opacity, cf. hide() and show())
          */
        bool isVisible();

		
	protected:

        /**
          * @brief the graphical item representing the rectangle of the Sort
          *
          */
        QGraphicsRectItem* _rect;

        /**
          * @brief the graphical item representing the text of the Sort
          *
          */
		QGraphicsTextItem* text;

        /**
          * @brief the related Sort
          *
          */
		SortPtr sort;

        /**
          * @brief the related cluster
          *
          */
		GVCluster cluster;		
		
        /**
          * @brief the palette of colors that may be used as color member
          *
          */
        static std::vector<QColor> palette;

        /**
          * @brief palette management index
          *
          */
		static int paletteIndex;

        /**
          * @brief gets a new color in the palette
          *
          * @return QColor* the color retrieved in the palette
          */
		static QColor* makeColor(void);

        /**
          * @brief the point used to record this GSort's coordinates when user clicks it (ie. starts drag&drop)
          *
          */
        QPoint initPosPoint;

        /**
          * @brief the point used to record mouse press event position
          *
          */
        QPoint eventPressPoint;

        /**
          * @brief the space between this GSort's top side and the top GProcess
          *
          */
        qreal paddingTop;

};
