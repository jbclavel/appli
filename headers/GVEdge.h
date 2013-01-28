#pragma once
#include <QPoint>
#include <QString>
#include <QPainterPath>

/**
  * @file GVEdge.h
  * @brief header for the GVEdge class
  * @author PAPPL_2012
  *
  */


/**
  * @brief struct containing the information for a GVGraph's edge
  *
  */
struct GVEdge {

    /**
      * @brief the source node of the edge
      *
      */
    QString source;

    /**
      *  @brief the target node of the edge
      *
      */
    QString target;


    /**
      * @brief the path of the edge's line
      *
      */
    QPainterPath path;

};
