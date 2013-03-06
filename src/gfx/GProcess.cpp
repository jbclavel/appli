#include <iostream>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QSizeF>
#include <QTextDocument>
#include <Qt>
#include "GProcess.h"
//#include "GVSubGraph.h"
#include <math.h>


const int GProcess::marginZone  = 10;
const int GProcess::sortName    = 11;


GProcess::GProcess(ProcessPtr p, GVNode n, qreal graphDPI) : process(p), node(n) {

    display = new QGraphicsItemGroup();

    // ellipse
    ellipse = new QGraphicsEllipseItem (node.centerPos.x() - node.width/2, node.centerPos.y() - node.height/2,
                                        node.width, node.height, display);
	ellipse->setPen(QPen(QColor(238,232,213)));
	ellipse->setBrush(QBrush(QColor(238,232,213)));

    int margin( (int) ceil(GVSubGraph::sepValue * graphDPI / GVGraph::DotDefaultDPI) );
    marginRect = new QGraphicsRectItem(
                node.centerPos.x() - node.width/2 - margin,
                node.centerPos.y() - node.height/2 - margin,
                node.width + 2*margin,
                node.height + 2*margin,
                display);
    //marginRect->setBrush(QBrush(QColor(255, 0, 0, 100)));
    marginRect->setBrush(Qt::NoBrush);
    marginRect->setPen(Qt::NoPen);
    marginRect->setData(marginZone, true);
    marginRect->setData(sortName, process->getSort()->getName().c_str());

    // text
    text = new QGraphicsTextItem (QString("%1").arg(process->getNumber()), ellipse);
	text->setDefaultTextColor(QColor(7,54,66));
	text->setPos(node.centerPos.x(), node.centerPos.y());
    // position the text
	QSizeF textSize = text->document()->size();
	text->setPos(text->x() - textSize.width()/2, text->y() - textSize.height()/2);
}


GProcess::~GProcess() {
    delete ellipse;
    delete text;
	delete display;
}


// getters

QGraphicsItem* GProcess::getDisplayItem (void) { return display; }

QGraphicsEllipseItem* GProcess::getEllipseItem(){ return ellipse; }

GVNode* GProcess::getNode() { return &(this->node); }

QGraphicsRectItem* GProcess::getMarginRect() { return this->marginRect; }


void GProcess::setNodeCoords(int dx, int dy) {
    node.centerPos.setX(node.centerPos.x() + dx);
    node.centerPos.setY(node.centerPos.y() + dy);
}

void GProcess::setNodeCoordsForImport(int x, int y) {
    node.centerPos.setX(x);
    node.centerPos.setY(y);
}


void GProcess::setNode(GVNode gvnode) {
    this->node = gvnode;
}


bool GProcess::checkCollisions() {

    QList<QGraphicsItem*> collidItems = marginRect->collidingItems();
    foreach (QGraphicsItem *item, collidItems) {
        // detect margins of GProcess items from other sorts
        if (item->data(marginZone).toBool()) {
            if (item->data(sortName).toString() != process->getSort()->getName().c_str()) {
                return true;
            }
        }
    }

    return false;
}

ProcessPtr* GProcess::getProcess() { return &(this->process); }
