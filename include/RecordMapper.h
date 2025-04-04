#ifndef RECORD_MAPPER_H
#define RECORD_MAPPER_H

#include "Record.h"
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include "dotenv.h"
#include <unordered_map>

class RecordMapper{
  public:
      RecordMapper();
      ~RecordMapper();

      void insertRecord(const Record& record);
      std::vector<Record> selectRecord(const std::string& dateTime);

  private:
      std::unique_ptr<sql::Connection> connection;  // MySQL Connection
      std::unordered_map<std::string, std::string> queries; // 쿼리를 저장할 맵
      dotenv env;

      void connect(); // DB 연결
      void loadQueries(const std::string& filepath);  // .dat 파일에서 SQL 쿼리 가져오기
      std::string getEnvVar(const std::string& varName);  // 환경변수 가져오기

  #ifdef UNIT_TEST
      friend class RecordMapperMockTest;
  #endif
};

#endif // RECORD_MAPPER_H
