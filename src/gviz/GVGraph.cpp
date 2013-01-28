#include <iostream>
#include <graphviz/gvc.h>
#include <boost/make_shared.hpp>
#include <QStringList>
#include <QRectF>
#include "Exceptions.h"
#include "GVGraph.h"


/*! Dot uses a 72 DPI value for converting it's position coordinates from points to pixels
    while we display at 96 DPI on most operating systems. */
const qreal GVGraph::DotDefaultDPI=72.0;


GVGraph::GVGraph(QString name, QFont font) : GVSubGraph() {	
	_context = gvContext();
    _graph = _agopen(name, AGDIGRAPHSTRICT); // strict directed graph, see libgraph doc
	setGraphAttributes();
    setFont(font);
}


// layout elements
void GVGraph::applyLayout() {	
    gvFreeLayout(_context, _graph);
    _gvLayout(_context, _graph, "fdp");
}


// get bounding rect (after layout has been done)
QRectF GVGraph::boundingRect() {
    qreal dpi = this->getDPI();
    return QRectF(_graph->u.bb.LL.x*(dpi/DotDefaultDPI), _graph->u.bb.LL.y*(dpi/DotDefaultDPI),
                  _graph->u.bb.UR.x*(dpi/DotDefaultDPI), _graph->u.bb.UR.y*(dpi/DotDefaultDPI));
}


// destruct
GVGraph::~GVGraph() {
    gvFreeLayout(_context, _graph);
    agclose(_graph);
    gvFreeContext(_context);
}


// font management
void GVGraph::setFont(QFont font) {
    _font=font;

    _agset(_graph, "fontname", font.family());
    _agset(_graph, "fontsize", QString("%1").arg(font.pointSizeF()));

    _agnodeattr(_graph, "fontname", font.family());
    _agnodeattr(_graph, "fontsize", QString("%1").arg(font.pointSizeF()));

    _agedgeattr(_graph, "fontname", font.family());
    _agedgeattr(_graph, "fontsize", QString("%1").arg(font.pointSizeF()));
}
