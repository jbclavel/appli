#include <iostream>
#include <string>
#include <boost/exception/all.hpp>

/**
  * @file Exceptions.h
  * @brief header for the Exceptions class
  * @author PAPPL_2012
  *
  */

using std::string;
using boost::error_info;

/**
  * @class exception_base
  * @brief struct defining the base of the exception
  *
  */
struct exception_base: virtual std::exception, virtual boost::exception { };

//IO errors
typedef error_info<struct file_path, string> file_info;

/**
  * @class io_error
  * @brief struct defining the base of the IO errors
  *
  */
struct io_error: virtual exception_base { };

/**
  * @class file_not_exist
  * @brief struct defining the exception called when the file does not exist
    extends io_error
  *
  */
struct file_not_exist: virtual io_error { };

/**
  * @class not_regular_file
  * @brief struct defining the exception called when the format of the file is not the one expected
    extends io_error
  *
  */
struct not_regular_file: virtual io_error { };

/**
  * @class not_regular_file
  * @brief struct defining the exception called when the import file does not refer to the current ph file
    extends io_error
  *
  */
struct wrong_import_file: virtual io_error { };


//Parse errors
typedef error_info<struct parse_detail, string> parse_info;

/**
  * @class ph_parse_error
  * @brief struct defining the exception called when the PH file cannot be parsed
    extends exception_base
  *
  */
struct ph_parse_error: virtual exception_base { };

/**
  * @class pint_phc_crash
  * @brief struct defining the exception called when Pint cannot be called
    extends ph_parse_error
  *
  */
struct pint_phc_crash: virtual ph_parse_error { };

/**
  * @class textAreaEmpty_exception
  * @brief struct defining the exception called when the user update from an empty textArea
    extends ph_parse_error
  *
  */
struct textAreaEmpty_exception: virtual ph_parse_error { };

//Pint errors

/**
  * @class pint_program_not_found
  * @brief struct defining the exception called when Pint is not found$
    extends exception_base
  */
struct pint_program_not_found: virtual exception_base { };

//PH errors
typedef error_info<struct process_id, int> process_info;
typedef error_info<struct sort_name, string> sort_info;

/**
  * @class ph_error
  * @brief struct defining the exception called when there is an error in the PH file
    extends exception_base
  *
  */
struct ph_error: virtual exception_base { };

/**
  * @class process_required
  * @brief struct defining the exception called when the process is not specified
    extends ph_error
  *
  */
struct process_required : virtual ph_error { };

/**
  * @class process_not_found
  * @brief struct defining the exception called when the process called is not found
    extends ph_error
  *
  */
struct process_not_found : virtual ph_error { };

/**
  * @class sort_not_found
  * @brief struct defining the exception called when the sort called are not found
    extends ph_error
  *
  */
struct sort_not_found : virtual ph_error { };

//Graphviz error

/**
  * @class gv_error
  * @brief struct defining the exception called when an error occurs in GraphViz
    extends exception_base
  *
  */
struct gv_error: virtual exception_base { };

/**
  * @class subgraph_not_found
  * @brief struct defining the exception called when the subgraph is not found
    extends gv_error
  *
  */
struct subgraph_not_found : virtual gv_error { };
