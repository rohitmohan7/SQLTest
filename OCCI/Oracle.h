#pragma once
#include <cstddef>
#include <occi.h>

using namespace oracle::occi;

typedef void(*ICONECT_ERRORPROC)(const char*);

class COracle {
private:
	Environment* env;
	Connection* conn;
	Statement* stmt;
	ResultSet* rset;
	const std::string user = "scott";
	const std::string passwd = "admin";
	const std::string db_connectionstr = "192.168.2.62:1521/XEPDB1";

public:
	/* Constructor. Opens a connection to the Oracle database (where the table ‘testing’ is
	located).*/
	COracle(ICONECT_ERRORPROC = NULL);

	/* Destructor. Frees handles, destroys any loaded data from a query including the
	   statement, resets all markers, and disconnects from Oracle.
	*/
	~COracle();

	/* Runs the parameter query szQuery and retrieves the resulting recordset. */
	bool Open(const char* szQuery);

	/* Returns the value of the field specified by nField. Note: This function allocates the
		memory for the value returned by this function.
	*/
	char* GetFieldValue(int nField);

	/* Returns the name of the field specified by nField.
	*/
	char* GetFieldName(int nField);

	/* Returns the number of fields in the active query */
	int GetFieldCount(void);

	/* Moves the current recordset forward one step. */
	bool MoveNext(void);

	/* Returns whether the current recordset has reached EOF. */
	bool IsEOF(void);
};