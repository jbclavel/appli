#pragma once
#include <string>

/**
  * @file IO.h
  * @brief header for the IO class
  * @author PAPPL_2012
  *
  */

using std::string;


/**
  * @class IO
  * @brief manages the inputs and outputs at the lowest level
  *
  */
class IO {

	public:
        IO() {}

        /**
          * @brief reads file content
          * @param string the path of the file to read
          * @return string file content
          *
          */
        static string readFile (string const& path);

        /**
          * @brief checks that the file exists
          *
          * @param string the path of the file to check
          *
          */
        static void fileLocationCheck (string const& path);

        /**
          * @brief Writes the content in the file
          * @param string the path of the file to write in
          * @param string the text content to write
          */
        static void writeFile (string const& path, string const& content);

};
