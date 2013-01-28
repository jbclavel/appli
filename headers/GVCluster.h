#pragma once
#include <QPoint>
#include <QString>

/**
  * @file GVCluster.h
  * @brief header for the GVCluster class
  * @author PAPPL_2012
  *
  */

/**
  * @brief struct containing the information for a GVGraph's node
  *
  */
struct GVCluster {
	
    /**
      * @brief the unique identifier of the cluster in the graph
      *
      */
    QString name;

    /**
      * @brief the position of the top-left corner
      *
      */
    QPoint topLeft;

    /**
      * @brief the size (height and width) of the cluster in pixels
      *
      */
    float height, width;
	
    /**
      * @brief the label position
      *
      */
	QPoint labelPos;
	
};
