#pragma once
#include <string>
#include "PH.h"
#include "MainWindow.h"
#include <QXmlStreamWriter>

/**
  * @file PHIO.h
  * @brief header for the PHIO class
  * @author PAPPL_2012
  *
  */

using std::string;

/**
  * @class PHIO
  * @brief manages the inputs and outputs of the PH files
  *
  */
class PHIO {

	public:
        /**
          * @brief checks if the file exists and is recognized by the parser
          * @param string the path of the file to parse
          * @return bool true if the file can be parsed
          *
          */
		static bool canParseFile(string const& path);

        /**
          * @brief parses the file if it is possible
          * @param string the path of the file to parse
          * @return PHPtr pointer to the PH object that results form parsing
          *
          */
		static PHPtr parseFile  (string const& path);

        /**
          * @brief saves the PH object as a PH file
          * @param string the path of the file
          * @param PHPtr pointer to the object that will be saved
          *
          */
        static void writeToFile (string const& path, PHPtr ph);

        /**
          * @brief saves as a PNG the representation of the PH file as it is displayed in the GUI
          * @param PHPtr pointer to the PH object of the active window
          * @param QString the name of the file saved
          *
          */
        static void exportToPNG (PHPtr ph, QString name);

        /**
          * @brief saves as an XML file the layout and style information of the graph displayed in GUI
          *
          * @param MainWindow active MainWindow
          * @param QFile the file to be written
          */
        static void exportXMLMetadata(MainWindow *window, QFile &output);

	
	private:
		PHIO(){}

        /**
          * @brief parses the data dumped by phc utility
          * @param string the dump to parse
          * @return PHPtr pointer to the PH object that results form parsing
          *
          */
        static PHPtr parse (string const& input);

};
