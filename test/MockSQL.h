#ifndef MOCK_SQL_H
#define MOCK_SQL_H

#include <string>
#include <gmock/gmock.h>
#include <memory>

namespace sql {

class ResultSet {
public:
    virtual ~ResultSet() = default;
    virtual bool next() = 0;
    virtual int getInt(const std::string& columnLabel) = 0;
    virtual std::string getString(const std::string& columnLabel) = 0;
};

class PreparedStatement {
public:
    virtual ~PreparedStatement() = default;
    virtual void setInt(unsigned int parameterIndex, int value) = 0;
    virtual void setString(unsigned int parameterIndex, const std::string& value) = 0;
    virtual std::unique_ptr<ResultSet> executeQuery() = 0;
    virtual int executeUpdate() = 0;
};

class Connection {
public:
    virtual ~Connection() = default;
    virtual std::unique_ptr<PreparedStatement> prepareStatement(const std::string& query) = 0;
    virtual void close() = 0;
};

class MockResultSet : public ResultSet {
public:
    MOCK_METHOD(bool, next, (), (override));
    MOCK_METHOD(int, getInt, (const std::string& columnLabel), (override));
    MOCK_METHOD(std::string, getString, (const std::string& columnLabel), (override));
};

class MockPreparedStatement : public PreparedStatement {
public:
    MOCK_METHOD(void, setInt, (unsigned int parameterIndex, int value), (override));
    MOCK_METHOD(void, setString, (unsigned int parameterIndex, const std::string& value), (override));
    MOCK_METHOD(std::unique_ptr<ResultSet>, executeQuery, (), (override));
    MOCK_METHOD(int, executeUpdate, (), (override));
};

class MockConnection : public Connection {
public:
    MOCK_METHOD(std::unique_ptr<PreparedStatement>, prepareStatement, (const std::string& query), (override));
    MOCK_METHOD(void, close, (), (override));
};

} // namespace sql

#endif // MOCK_SQL_H
