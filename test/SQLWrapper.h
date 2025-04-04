#ifndef SQLWRAPPER_H
#define SQLWRAPPER_H

#include <memory>
#include <cppconn/connection.h>

class SQLWrapper {
public:
    virtual ~SQLWrapper() = default;
    virtual std::unique_ptr<sql::Connection> createConnection() = 0;
};

#endif // SQLWRAPPER_H
