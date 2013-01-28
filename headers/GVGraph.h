#pragma once
#include <graphviz/gvc.h>
#include <boost/shared_ptr.hpp>
#include <QFont>
#include <QList>
#include <QMap>
#include <QPair>
#include <QRectF>
#include <QString>
#include "GVSubGraph.h"

/**
  * @file GVGraph.h
  * @brief header for the GVGraph class
  * @author PAPPL_2012
  *
  */

class GVGraph;
typedef boost::shared_ptr<GVGraph> GVGraphPtr;

// An object containing a libgraph graph and its associated nodes and edges

/**
  * @class GVGraph
  * @brief object containing a libgraph graph and its associated nodes and edges
  *
  */
class GVGraph: public GVSubGraph {

	public:

        /**
          * @brief Default DPI value used by dot (which uses points instead of pixels for coordinates)
          *
          */
		static const qreal DotDefaultDPI;

        /**
          * @brief Construct a Graphviz graph object
          *
          * @param name The name of the graph, must be unique in the application
          * @param font The font to use for the graph
          * @param node_size The size in pixels of each node
          *
          */
		GVGraph(QString name, QFont font=QFont());
		~GVGraph();

		// Layout and rendering
        /**
          * @brief builds the layout
          *
          */
		void applyLayout (void);

        /**
          * @brief renders the file
          *
          * @param Qstring name of the file you want to render
          *
          */
		void renderToFile (QString name);
		
        /**
          * @brief the rectangle result
          *
          * @return a QRectF representing the rectangle built
          *
          */
        QRectF boundingRect();

        /**
          * @brief sets the font that will be used in all the labels
          *
          * @param QFont chosen to be used
          *
          */
		void setFont(QFont font);

	private:

		QFont _font;
		GVC_t *_context;
};
