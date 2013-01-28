#pragma once
#include <boost/shared_ptr.hpp>
#include <string>
#include <list>
#include "Sort.h"

/**
  * \file Process.h
  * \brief header for the Process class
  * \author PAPPL_2012
  *
  */

using std::string;


// mutual inclusion
class Sort;
typedef boost::shared_ptr<Sort> SortPtr;

class Process;
typedef boost::shared_ptr<Process> ProcessPtr;

class GProcess;
typedef boost::shared_ptr<GProcess> GProcessPtr;

/**
  * @class Process
  * @brief represents a Process of the process hitting
  *
  */
class Process {

	public:

        /**
          * @brief constructor
          *
          * @param Sortptr pointer to the Sort the Process is related to
          * @param int number of the Process in the Sort it is related to
          *
          */
		Process (SortPtr s, const int& n);

        /**
          * @brief gets the number
          *
          */
		int getNumber(void);

        /**
          * @brief gets the Sort
          *
          */
		SortPtr getSort(void);

        /**
          * @brief builds name for DOT files
          * @return string adapted name
          */
		string getDotName (void);

        /**
          * @brief gives a text representation of the process hitting (in .dot format, used in Graphviz)
          * @return string the representation in DOT format
          *
          */
		string toDotString (void);

        /**
          * @brief sets the related GProcess
          * @param a pointer to the related GProcess object
          */
        void setGProcess(GProcessPtr gPPtr);

        /**
          * @brief gets the related GProcess
          * @return GProcessPtr a pointer to the related GProcess object
          *
          */
        GProcessPtr getGProcess();


	private:

        /**
          * @brief the Sort the Process is related to
          *
          */
		SortPtr sort;

        /**
          * @brief the number of the Process in the Sort it is related to
          *
          */
		int number;

        /**
          * @brief a pointer to the related GProcess
          *
          */
        GProcessPtr gProcess;

};
