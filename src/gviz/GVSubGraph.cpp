#include <iostream>
#include <graphviz/gvc.h>
#include <boost/make_shared.hpp>
#include <QStringList>
#include "Exceptions.h"
#include "GVSubGraph.h"
#include "GVGraph.h"
#include "MainWindow.h"

// UTILS

// add subgraph
static inline Agraph_t* _agsubg(Agraph_t* object, QString name) {
	return agsubg(object, const_cast<char *>(qPrintable(name)));
}

// add node
static inline Agnode_t* _agnode(Agraph_t* object, QString name) {
	return agnode(object, const_cast<char *>(qPrintable(name)));
}


// CONSTRUCTORS

GVSubGraph::GVSubGraph() {} //This one is only called by GVGraph (protected)
GVSubGraph::GVSubGraph(Agraph_t* graph) : _graph(graph) {	
	setGraphAttributes();
}
GVSubGraph::~GVSubGraph() {    
    agclose(_graph);
}


//Set basic graph attributes for graphviz
const qreal GVSubGraph::nodeSize = 50;
const qreal GVSubGraph::sepValue = 12.0;
void GVSubGraph::setGraphAttributes(void) {

    QString mode;

    if(MainWindow::mwThis->getDisplayMode() == 0){

        mode = "false";
    }
    else if(MainWindow::mwThis->getDisplayMode() == 1){

        mode = "true";
    }

    // set graph attributes
    _agset(_graph, "overlap", "scale");
    _agset(_graph, "splines", mode);
    //_agset(_graph, "splines", "curved"); // with fdp, "curved" provokes edge overlap on nodes
	_agset(_graph, "dpi", "96,0");
    QString strSepValue = QString::number(sepValue).prepend("+");
    _agset(_graph, "sep", strSepValue);

    // divide the wanted width by the DPI to get the value in points
    QString nodePtsWidth = QString("%1").arg(GVSubGraph::nodeSize/_agget(_graph, "dpi", "96,0").replace(',', ".").toDouble());
	//GV uses , instead of . for the separator in floats
    _agnodeattr(_graph, "width", nodePtsWidth.replace('.', ","));

}

//Set name
void GVSubGraph::setLabel (const QString& name) {
	_agset(_graph, "label", name);
}

//Retrieve clusters for drawing (after layout has been done)
QList<GVCluster> GVSubGraph::clusters() {	
	QList<GVCluster> list;
	qreal dpi = this->getDPI();	
	for (QMap<QString, GVSubGraphPtr>::const_iterator it = _subgraphs.begin(); it != _subgraphs.end(); ++it) {
		Agraph_t* graph = it.value()->_graph;
		GVCluster object;
		object.name = graph->name; //Cluster name
		//Position
		qreal x = (dpi/GVGraph::DotDefaultDPI) *  graph->u.bb.LL.x;
		qreal y = (dpi/GVGraph::DotDefaultDPI) * -graph->u.bb.UR.y;
		object.topLeft = QPoint(x, y);
		//Size
		object.width 	= (graph->u.bb.UR.x - graph->u.bb.LL.x) * dpi/GVGraph::DotDefaultDPI;
        object.height	= (graph->u.bb.UR.y - graph->u.bb.LL.y) * dpi/GVGraph::DotDefaultDPI;
		//Label position
		qreal lx = (dpi/GVGraph::DotDefaultDPI) *  graph->u.label->pos.x;
		qreal ly = (dpi/GVGraph::DotDefaultDPI) * -graph->u.label->pos.y;
		object.labelPos = QPoint(lx, ly);
		list << object;
	}
	for (auto &s : _subgraphs)
		list += s->clusters();		
    return list;
}

//Retrieve nodes for drawing (after layout has been done)
QList<GVNode> GVSubGraph::nodes() {	
	QList<GVNode> list;
	qreal dpi = this->getDPI();
    for (QMap<QString, Agnode_t*>::const_iterator it = _nodes.begin(); it != _nodes.end(); ++it) {
        Agnode_t *node = it.value();
        GVNode object;
        object.name = node->name; //Node name
		//Position
        qreal x =  node->u.coord.x * (dpi/GVGraph::DotDefaultDPI);
        qreal y = -node->u.coord.y * (dpi/GVGraph::DotDefaultDPI);
        object.centerPos = QPoint(x, y);
		//Size
        object.height = node->u.height * dpi;
        object.width = node->u.width * dpi;
        list << object;
    }
	for (auto &s : _subgraphs)
		list += s->nodes();
    return list;
}

//Retrieve edges for drawing (after layout has been done)
QList<GVEdge> GVSubGraph::edges() { 
	QList<GVEdge> list;
	qreal dpi = this->getDPI();
    for(QMap<QPair<QString, QString>, Agedge_t*>::const_iterator it=_edges.begin(); it!=_edges.end();++it) {
        Agedge_t *edge=it.value();
        GVEdge object;		
        //Fill the source and target node names
        object.source=edge->tail->name;
        object.target=edge->head->name;		
        //Calculate the path from the spline
        if((edge->u.spl->list!=0) && (edge->u.spl->list->size%3 == 1)) {
            //If there is a starting point, draw a line from it to the first curve point
            if(edge->u.spl->list->sflag) {
                object.path.moveTo	(	edge->u.spl->list->sp.x*(dpi/GVGraph::DotDefaultDPI)
									,	(-edge->u.spl->list->sp.y)*(dpi/GVGraph::DotDefaultDPI)
									);
                object.path.lineTo	(	edge->u.spl->list->list[0].x*(dpi/GVGraph::DotDefaultDPI)
									,	(-edge->u.spl->list->list[0].y)*(dpi/GVGraph::DotDefaultDPI)
									);
            } else
                object.path.moveTo	(	edge->u.spl->list->list[0].x*(dpi/GVGraph::DotDefaultDPI)
									,	(-edge->u.spl->list->list[0].y)*(dpi/GVGraph::DotDefaultDPI)
									);
            //Loop over the curve points
            for(int i=1; i<edge->u.spl->list->size; i+=3)
                object.path.cubicTo	(	edge->u.spl->list->list[i].x   * (dpi/GVGraph::DotDefaultDPI)
									, 	(-edge->u.spl->list->list[i].y)   * (dpi/GVGraph::DotDefaultDPI)
									,	edge->u.spl->list->list[i+1].x * (dpi/GVGraph::DotDefaultDPI)
									,	(-edge->u.spl->list->list[i+1].y) * (dpi/GVGraph::DotDefaultDPI)
									,	edge->u.spl->list->list[i+2].x * (dpi/GVGraph::DotDefaultDPI)
									,	(-edge->u.spl->list->list[i+2].y) * (dpi/GVGraph::DotDefaultDPI)
									);
            //If there is an ending point, draw a line to it
            if(edge->u.spl->list->eflag)
                object.path.lineTo	(	edge->u.spl->list->ep.x*(dpi/GVGraph::DotDefaultDPI)
									,	(-edge->u.spl->list->ep.y)*(dpi/GVGraph::DotDefaultDPI)
									);
        }

        list << object;
    }

    return list;
}

//Subgraphs management
void GVSubGraph::addSubGraph(const QString& name) {
	if(_subgraphs.contains(name)) removeSubGraph(name);
	_subgraphs.insert(name, boost::make_shared<GVSubGraph>(_agsubg(_graph, name)));	
}
void GVSubGraph::removeSubGraph(const QString& name) {
	if(_subgraphs.contains(name)) {
        agdelete(_graph, _subgraphs[name]->_graph);
        _subgraphs.remove(name);
    }
}
GVSubGraphPtr GVSubGraph::getSubGraph(const QString& name) {
	if(_subgraphs.contains(name)) return _subgraphs.value(name);	
	else throw subgraph_not_found();
}

//Node management
int GVSubGraph::countNodes (void) { return _nodes.count(); }
void GVSubGraph::addNode(const QString& name) {
    if(_nodes.contains(name)) removeNode(name);	
    _nodes.insert(name, _agnode(_graph, name));
}
void GVSubGraph::addNodes(const QStringList& names) {
    for(int i=0; i<names.size(); ++i)
        addNode(names.at(i));
}
void GVSubGraph::removeNode(const QString& name) {
    if(_nodes.contains(name)) {
        agdelete(_graph, _nodes[name]);
        _nodes.remove(name);
        QList<QPair<QString, QString> >keys=_edges.keys();
        for(int i=0; i<keys.size(); ++i)
            if(keys.at(i).first==name || keys.at(i).second==name)
                removeEdge(keys.at(i));
    }
}
bool GVSubGraph::hasNode (const QString& name) {
	if(_nodes.contains(name)) return true;
	for (QMap<QString, GVSubGraphPtr>::const_iterator it = _subgraphs.begin(); it != _subgraphs.end(); ++it)
		if (it.value()->hasNode(name)) return true;
	return false;
}
Agnode_t* GVSubGraph::getNode (const QString& name) {
	if(_nodes.contains(name)) return _nodes[name];
	for (QMap<QString, GVSubGraphPtr>::const_iterator it = _subgraphs.begin(); it != _subgraphs.end(); ++it)
		if (it.value()->hasNode(name)) return it.value()->getNode(name);
	return NULL;
}
void GVSubGraph::clearNodes() {
    QList<QString> keys=_nodes.keys();
    for(int i=0; i<keys.size(); ++i)
        removeNode(keys.at(i));
}

//Edge management
void GVSubGraph::addEdge(const QString &source, const QString &target) {
    if (hasNode(source) && hasNode(target)) {
        QPair<QString, QString> key(source, target);
        if(!_edges.contains(key))
            _edges.insert(key, agedge(_graph, getNode(source), getNode(target)));
    }
}
void GVSubGraph::removeEdge(const QString &source, const QString &target) {
    removeEdge(QPair<QString, QString>(source, target));
}
void GVSubGraph::removeEdge(const QPair<QString, QString>& key) {
    if(_edges.contains(key)) {
        agdelete(_graph, _edges[key]);
        _edges.remove(key);
    }
}

//Getter for graph DPI
qreal GVSubGraph::getDPI() {
	return _agget(_graph, "dpi", "96,0").replace(',', ".").toDouble();
}

Agedge_t* GVSubGraph::getEdge(const QString &sourceName, const QString &targetName) {
    QPair<QString, QString> key(sourceName, targetName);
    if (!_edges.contains(key)) return NULL;
    return _edges.value(key);
}


Agraph_t* GVSubGraph::graph() { return this->_graph; }
