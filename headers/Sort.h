#pragma once
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Process.h"

/**
  * @file Sort.h
  * @brief header for the Sort class
  * @author PAPPL_2012
  *
  */

using std::string;
using std::list;
using std::vector;
using boost::make_shared;


// mutual inclusion
class Process;
typedef boost::shared_ptr<Process> ProcessPtr;

class Sort;
typedef boost::shared_ptr<Sort> SortPtr;

class GSort;


/**
  * @class Sort
  * @brief represents a sort of the process hitting
  *
  */
class Sort {

public:
	
        /**
          * @brief creates a pointer to the Sort which name is given as parameter
          * @param string name of the Sort to created
          * @param int number of processes in the Sort
          * @return SortPtr the pointer to the created Sort
          *
          */
		static SortPtr make(const string&, const int&);
		

        /**
          * @brief gets a Process by its index
          * @param uint the index of the Process in processes vector
          *
          */
		ProcessPtr getProcess (const uint&);

        /**
          * @brief gets processes vector
          *
          */
        vector<ProcessPtr> getProcesses (void);

        /**
          * @brief gets the active process
          *
          */
		ProcessPtr getActiveProcess (void);

        /**
          * @brief sets the active process
          *
          */
		void setActiveProcess (const int&);

        /**
          * @brief counts the number of processes
          * @return int the number of processes
          */
		int countProcesses (void);

        /**
          * @brief gets the name of the Sort
          *
          */
		string getName (void);

        /**
          * @brief gives a text representation of the process hitting (as it would be in a .ph file)
          * @return string the text representation of the process hitting in PH format
          */
		string toString(void);

        /**
          * @brief gives a text representation of the process hitting (in .dot format, used in Graphviz)
          * @return string the text representation of the process hitting in DOT format
          */
		string toDotString(void);

	protected:

        /**
          * @brief constructor
          *
          */
        Sort (const string&);

        /**
          * @brief adds a Process
          * @param ProcessPtr pointer to the Process to add
          */
		void addProcess(ProcessPtr p);

        /**
          * @brief name of the Sort
          *
          */
		string name;

        /**
          * @brief Processes of the Sort
          *
          */
		vector<ProcessPtr> processes;

        /**
          * @brief active Process in the Sort
          *
          */
		ProcessPtr activeProcess;
};
