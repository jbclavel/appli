#include <iostream>
#include <QMatrix>
#include <QPointF>
#include <QVector>
#include <QColor>
#include <Qt>
#include "GAction.h"


GAction::GAction(ActionPtr a, GVEdge e, GVEdge f, PHScene* sc) : scene(sc), action(a) {

    edges = std::make_pair (e, f);
    display = new QGraphicsItemGroup();

    // Gsort where this action starts
    GSortPtr owner = scene->getGSort(action->getSource()->getSort()->getName());
    QColor color = *(owner->color);

    // arrow tails
    arrowTails.first 	= new QGraphicsPathItem(edges.first.path, display);
    arrowTails.first->setPen(QPen(color));
    arrowTails.second 	= new QGraphicsPathItem(edges.second.path, display);
    arrowTails.second->setPen(QPen(color, 0, Qt::DashLine));

    // arrow heads
    arrowHeads.first 	= makeArrowHead(edges.first, color);
    arrowHeads.second 	= makeArrowHead(edges.second, color);
}


GAction::~GAction() {
    delete display;
    //delete scene; <-- do not delete this pointer, it's owned by a shared pointer in PH.h
}


// draw an arrowhead
QGraphicsPolygonItem* GAction::makeArrowHead(const GVEdge& e, const QColor& color) {

    // arrow pointing to the right
    QPointF p = e.path.pointAtPercent(1);
    QPointF* q = new QPointF(p.x() - 8, p.y() - 5);
    QPointF* r = new QPointF(p.x() - 8, p.y() + 5);
    QPointF* s = new QPointF(p.x() - 1, p.y());
    QPointF* t = new QPointF(p.x() - 7.5, p.y() + 4);
    QPointF* u = new QPointF(p.x() - 7.5, p.y() - 4);
    QPolygonF polygon;
    polygon.push_back(p);
    polygon.push_back(*q);
    polygon.push_back(*u);
    polygon.push_back(*s);
    polygon.push_back(*t);
    polygon.push_back(*r);

    // rotate arrow
    QMatrix matrix;
    matrix.translate(p.x(), p.y());
    matrix.rotate(-e.path.angleAtPercent(1));
    matrix.translate(-p.x(), -p.y());
    polygon = matrix.map(polygon);

    // turn into QGraphicsPolygonItem
    QGraphicsPolygonItem* res = new QGraphicsPolygonItem (polygon, display);
    res->setPen(QPen(color));
    res->setBrush(QBrush(color));
    return res;
}


// getters

QGraphicsItem* GAction::getDisplayItem (void) {
    return display;
}

ActionPtr GAction::getAction() {
    return action;
}

GSortPtr GAction::getSourceSort() {
    return scene->getGSort(action->getSource()->getSort()->getName());
    //return action->getSource()->getGProcess();
}

GSortPtr GAction::getTargetSort() {
    return scene->getGSort(action->getTarget()->getSort()->getName());
    //return action->getTarget()->getGProcess();
}

GSortPtr GAction::getResultSort() {
    return scene->getGSort(action->getResult()->getSort()->getName());
    //return action->getResult()->getGProcess();
}
