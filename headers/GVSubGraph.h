#pragma once
#include <graphviz/gvc.h>
#include <boost/shared_ptr.hpp>
#include <QFont>
#include <QMap>
#include <QPair>
#include <QString>
#include "GVCluster.h"
#include "GVNode.h"
#include "GVEdge.h"

/**
  * @file GVSubGraph.h
  * @brief header for the GVSubGraph class
  * @author PAPPL_2012
  *
  */

class GVSubGraph;
typedef boost::shared_ptr<GVSubGraph> GVSubGraphPtr;


/**
  * @class GVSubGraph
  * @brief the object containing a libraph subgraph and its associated nodes and edges
  *
  */
class GVSubGraph {

	public:
		
        /**
          * @brief the size in pixels of each node
          *
          */
		static const qreal nodeSize;

        /**
          * @brief the minimum margin around each node (in points for graphviz)
          *
          */
        static const qreal sepValue;
		
        /**
          * @brief GVSubGraph constructor
          * @param Agraph_t _graph a Graphviz graph
          */
		GVSubGraph(Agraph_t *_graph);

		virtual ~GVSubGraph();

        // subgraphs

        /**
          * @brief adds a subgraph
          *
          * @param QString the name of the SubGraph to be added
          *
          */
		void addSubGraph (const QString& name);

        /**
          * @brief removes a subgraph
          *
          * @param QString the name of the subgraph to be removed
          *
          */
		void removeSubGraph (const QString& name);

        /**
          * @brief retrieves a GVSubGraph by its name
          *
          * @param QString the name of the GVSubGraph to be retrieved
          * @return GVSubGraphPtr the pointer to the retrieved GVSubGraph
          *
          */
		GVSubGraphPtr getSubGraph (const QString& name);

        // nodes

        /**
          * @brief counts the number of nodes
          *
          * @return int the number of nodes
          *
          */
		int countNodes(void);

        /**
          * @brief adds a node, entering its name
          *
          * @param QString the name of the node to be added
          *
          */
		void addNode(const QString& name);

        /**
          * @brief adds a list of nodes, entering their names
          *
          * @param QStringList the list of the names of the nodes to be added
          */
		void addNodes(const QStringList& names);

        /**
          * @brief removes a node, entering its name
          *
          * @param QString the name of the node to be removed
          *
          */
		void removeNode(const QString& name);

        /**
          * @brief removes all the nodes
          *
          */
		void clearNodes();

        // edges

        /**
          * @brief adds an edge
          *
          * @brief QString the name of the edge's source
          * @brief QString the name of the edge's target
          *
          */
		void addEdge(const QString& source, const QString& target);

        /**
          * @brief removes an edge
          *
          * @brief QString the name of the egde's source
          * @brief QString the name of the edge's target
          *
          */
		void removeEdge(const QString& source, const QString& target);

        /**
          * @brief removes an edge, entering the pair (source, target)
          *
          * @brief QPair<QString, QString> the pair to be removed
          *
          */
		void removeEdge(const QPair<QString, QString>& key);
		
		//Setter

        /**
          * @brief sets the label
          *
          * @param QString the label
          *
          */
		void setLabel (const QString& name);
		
		//Layout results

        /**
          * @brief gets the list of nodes
          * @return the list of nodes
          *
          */
		QList<GVNode> nodes();

        /**
          * @brief gets the list of clusters
          * @return the list of clusters
          *
          */
		QList<GVCluster> clusters();

        /**
          * @brief gets the list of edges
          * @return the list of edges
          *
          */
		QList<GVEdge> edges();

        /**
          * @brief gets a graphviz edge by its source node name and target node name
          *
          * @param QString the name of the source node
          * @param QString the name of the target name
          * @return Agedge_t* a pointer to the retrieved edge
          */
        Agedge_t* getEdge(const QString& sourceName, const QString& targetName);

        /**
          * @brief gets a node by its name
          *
          * @param QString the name of the node
          * @return Agnode_t* a pointer to the retrieved node
          */
        Agnode_t* getNode (const QString& name);

        /**
          * @brief gets the graphviz graph struct of this GVSubGraph
          *
          * @return Agraph_t* a pointer to the graph
          */
        Agraph_t* graph();

        /**
          * @brief gets the DPI value
          *
          * @return qreal the DPI value
          *
          */
        qreal getDPI();


	protected:
		GVSubGraph();

        /**
          * @brief sets the Graph Attributes
          *
          */
		void setGraphAttributes(void);

        /**
         * @brief Agraph_t the related Graphviz graph
         */
        Agraph_t* _graph;

        /**
          * @brief checks if the node exists
          *
          * @param QString the name of the node which existence is to be checked
          * @return bool true if node exists, else fase
          *
          */
		bool hasNode (const QString& name);



		QMap<QString, Agnode_t*> _nodes;
		QMap<QString, GVSubGraphPtr> _subgraphs;
		QMap<QPair<QString, QString>, Agedge_t*> _edges;

};


// utils
/// opens a graph
static inline Agraph_t* _agopen(QString name, int kind) {
	return agopen(const_cast<char *>(qPrintable(name)), kind);
}

/// adds an alternative value parameter to the method for getting an object's attribute
static inline QString _agget(void *object, QString attr, QString alt=QString()) {
	QString str=agget(object, const_cast<char *>(qPrintable(attr)));
	if(str==QString())	return alt;
	else				return str;
}

/// directly uses agsafeset which always works, contrary to agset
static inline int _agset(void *object, QString attr, QString value) {
	return agsafeset(object, const_cast<char *>(qPrintable(attr)),
					 const_cast<char *>(qPrintable(value)),
					 const_cast<char *>(qPrintable(value)));
}

/// sets node attribute
static inline Agsym_t* _agnodeattr(Agraph_t* object, QString attr, QString value) {
	return agnodeattr(object, const_cast<char *>(qPrintable(attr)),
					 const_cast<char *>(qPrintable(value)));
}

/// sets edge attribute
static inline Agsym_t* _agedgeattr(Agraph_t* object, QString attr, QString value) {
	return agedgeattr(object, const_cast<char *>(qPrintable(attr)),
					 const_cast<char *>(qPrintable(value)));
}

// layout
static inline void _gvLayout(GVC_t* context, Agraph_t* graph, QString alg) {
	gvLayout(context, graph, const_cast<char *>(qPrintable(alg)));
}
