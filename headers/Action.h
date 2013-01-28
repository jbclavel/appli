#pragma once
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include "PH.h"
#include "Sort.h"
#include "GAction.h"

/**
  * @file Action.h
  * @brief header for the Action class
  * @author PAPPL_2012
  *
  */


class Action;
typedef boost::shared_ptr<Action> ActionPtr;

class GAction;
typedef boost::shared_ptr<GAction> GActionPtr;


/**
  * @class Action
  * @brief Represents an Action of the process hitting
  *
  */
class Action {

	public:
    /**
      * @brief constructor
      *
      * @param ProcessPtr the source Process of the hit
      * @param ProcessPtr the target Process of the hit
      * @param ProcessPtr the result of the hit
      * @param bool determines whether the rate of the hit is infinite or not
      * @param double the rate of the hit
      * @param int the stochasticity absorption of the hit
      */
		Action 	(	ProcessPtr source_, ProcessPtr target_, ProcessPtr result_
				, 	const bool& infiniteRate_
				, 	const double& r_
				,	const int& sa_
				);

        /**
          * @brief gets the source Process
          *
          * @return ProcessPtr pointer to the source Process
          */
        ProcessPtr getSource();

        /**
          * @brief gets the target Process
          *
          * @return ProcessPtr pointer to the target Process
          */
		ProcessPtr getTarget();

        /**
          * @brief gets the result Process
          *
          * @return ProcessPtr pointer to the result Process
          */
		ProcessPtr getResult();

        /**
          * @brief gives a text representation of the Process (as it would be in a .ph file)
          *
          * @return string the text representation of the Process
          */
		string toString (void);

        /**
          * @brief gives a text representation of the Process (in .dot format, used in Graphviz)
          *
          * @return string the text representation of the Process
          */
		string toDotString (void);

	protected:

       /**
         * @brief the source Process
         *
         */
        ProcessPtr source;

        /**
          * @brief the target Process
          *
          */
		ProcessPtr target;

        /**
          * @brief the result Process
          *
          */
        ProcessPtr result;

        /**
          * @brief Boolean that determines whether the rate of the hit is infinite or not
          *
          */
        bool infiniteRate;

        /**
          * @brief the rate of the hit
          *
          */
        float r;

        /**
          * @brief the stochasticity absorption
          *
          */
        int sa;
		
};
