#pragma once

#include <QWidget>
#include <QApplication>
#include <QtGui>
#include "PH.h"

/**
  * @file MyArea.h
  * @brief header for the MyArea class
  * @author PAPPL_2012
  *
  */


/**
  * @class MyArea
  * @brief Graph Widget
    extends QGraphicsView
  *
  */
class MyArea : public QGraphicsView {
    Q_OBJECT

    public:

        /**
          * @brief constructor
          * @param QString path of the area
          *
          */
        MyArea(QString path);

        /**
          * @brief constructor
          * @param QWidget parent of the MyArea, which is the Area
          * @param QString path of the area
          *
          */
        MyArea(QWidget *parent, QString path);

        // getter + setter for myPHPtr
        /**
          * @brief gets myPHPtr
          *
          */
        PHPtr getPHPtr();

        /**
          * @brief sets myPHPtr
          *
          */
        void setPHPtr(PHPtr);

        // getter + setter for path

        /**
          * @brief gets path
          *
          */
        QString getPath();

        /**
          * @brief sets path
          *
          */
        void setPath(QString);

        /**
          * @brief zooms the view in
          *
          */
        void zoomIn();

        /**
          * @brief zooms the view out
          *
          */
        void zoomOut();

        /**
          * @brief zooms the view in and out while scrolling
          *
          */
        void wheelEvent(QWheelEvent *event);

        /**
          * @brief gets the scaling factor
          *
          */
        float getScalingFactor();

        /**
          * @brief sets the scaling factor
          *
          */
        void setScalingFactor(float);



    protected:
        /**
          * @brief pointer to a PH object
          *
          */
        PHPtr myPHPtr;

        /**
          * @brief the path to the file
          *
          */
        QString path;        

        /**
          * @brief the scaling factor
          *
          */
        float scalingFactor;

    signals:

    public slots:

};
