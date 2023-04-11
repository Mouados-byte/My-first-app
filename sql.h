#pragma once
/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class this_sql {
public :
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::ResultSet* res;
public:
	int data_sql(void) ;
};
