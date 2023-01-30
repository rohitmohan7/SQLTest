#include <Oracle.h>

void ErrorProc(const char* error) {
    printf(error);
}

int main(void)
{
    COracle* cOracle = new COracle(ErrorProc);

    std::string sqlStmt = "SELECT * FROM testing \
    WHERE AUTHOR = 'iconnect\london' \
    AND OBJECT_ID >= 5";

    std::vector<std::string> buffer;

    if (cOracle->Open(sqlStmt.c_str())) {
        int fieldCount = cOracle->GetFieldCount();
        std::string val;

        for (int i = 0; i < fieldCount; ++i) {
            val += (val.length() > 0 ? "," : "");
            val += cOracle->GetFieldName(i);
        }

        buffer.push_back(val);

        while (!cOracle->IsEOF()) {
            val.clear();
            for (int i = 0; i < fieldCount; ++i) {
                val += (val.length() > 0 ? "," : "");
                val += cOracle->GetFieldValue(i);
            }
            buffer.push_back(val);
            if (!cOracle->MoveNext()) {
                break;
            }
        }
    }
}
