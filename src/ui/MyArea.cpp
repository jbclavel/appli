#include <QPainter>
#include "MyArea.h"


// constructor
MyArea::MyArea(QWidget *parent, QString path) : QGraphicsView(parent) {
    this->path = path;
	setRenderHints (QPainter::Antialiasing);

    this->scalingFactor = 1.2;
}

MyArea::MyArea(QString path) : QGraphicsView() {
    this->path = path;
    setRenderHints (QPainter::Antialiasing);

    this->scalingFactor = 1.2;
}


// get/set myPHPtr
PHPtr MyArea::getPHPtr() {
    return this->myPHPtr;
}
void MyArea::setPHPtr(PHPtr pPHPtr) {
     this->myPHPtr = pPHPtr;
}

// get/set scalingFactor
void MyArea::setScalingFactor(float scale){
    this->scalingFactor = scale;
}

float MyArea::getScalingFactor(){
    return this->scalingFactor;
}

// get/set path
QString MyArea::getPath() {
    return this->path;
}
void MyArea::setPath(QString Path) {
     this->path = path;
}

void MyArea::wheelEvent(QWheelEvent *event)
{
        // get the delta of the wheel event and check if control key is pushed
        if(event->delta()>=0 && event->modifiers() == Qt::ControlModifier)
        {
            // if the delta is positive, the action must follow the position of the pointer
            this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
            // scale positively
            this->scale(this->getScalingFactor(), this->getScalingFactor());
        }
        else if(event->delta()<0 && event->modifiers() == Qt::ControlModifier)
        {
            // if the delta is negative, the action must follow the center of the view
            this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
            // scale negatively
            this->scale(1 / this->getScalingFactor(), 1 / this->getScalingFactor());
        }
        else
        {
            QGraphicsView::wheelEvent(event);
        }

}

// method to zoom In
void MyArea::zoomIn()
{
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    this->scale(this->getScalingFactor(), this->getScalingFactor());
}

// method to zoom out
void MyArea::zoomOut()
{
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    this->scale(1 / this->getScalingFactor(), 1 / this->getScalingFactor());
}


#include "moc_MyArea.cpp"
