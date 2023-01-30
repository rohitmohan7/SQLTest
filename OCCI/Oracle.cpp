
#include "Oracle.h"

COracle::COracle(ICONECT_ERRORPROC) {
    try {
        env = Environment::createEnvironment(Environment::DEFAULT);
        conn = env->createConnection(user, passwd, db_connectionstr);
    }
    catch (SQLException ex) {
        ICONECT_ERRORPROC(ex.getMessage().c_str());
    }
}

bool COracle::Open(const char* szQuery) {
    stmt = conn->createStatement(szQuery);
    rset = stmt->executeQuery();
    return rset->next();
}

bool COracle::MoveNext() {
    return rset->next();
}

int COracle::GetFieldCount() {
    return rset->getNumArrayRows();
}

char* COracle::GetFieldName(int nField) {
    std::vector<MetaData> rsmd = rset->getColumnListMetaData();
    return (char *)rsmd[nField].getString(MetaData::ATTR_NAME).c_str();
}

char* COracle::GetFieldValue(int nField) {
    std::vector<MetaData> rsmd = rset->getColumnListMetaData();
    switch (rsmd[nField].getInt(MetaData::ATTR_DATA_TYPE))
    {
        case OCCI_SQLT_NUM:
            return (char*) rset->getNumber(nField).toText(env, "%d").c_str();
        default:
            return (char*)rset->getString(nField).c_str();
    }
}

bool COracle::IsEOF() {
    return rset->status() == ResultSet::END_OF_FETCH;
}

COracle::~COracle()
{
    stmt->closeResultSet(rset);
    conn->terminateStatement(stmt);
    env->terminateConnection(conn);
    Environment::terminateEnvironment(env);
}