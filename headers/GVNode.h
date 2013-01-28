#pragma once
#include <QPoint>
#include <QString>

/**
  * @file GVNode.h
  * @brief header for the GVNode class
  * @author PAPPL_2012
  *
  */


/**
  * @brief struct containing the information for a GVGraph's node
  *
  */
struct GVNode {

    /**
      * @brief the unique identifier of the node in the graph
      *
      */
    QString name;

    /**
      * @brief position of the center point of the node from the top-left corner
      *
      */
    QPoint centerPos;

    /**
      * @brief the size (height and width) of the node in pixels
      *
      */
    float height, width;
	
};
