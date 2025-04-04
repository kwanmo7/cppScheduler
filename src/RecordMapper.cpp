#include "RecordMapper.h"
#include <iostream>
#include <cppconn/exception.h>
#include <fstream>
#include <sstream>

using namespace std;

RecordMapper::RecordMapper() : env(){
  loadQueries(env.get("CONFIG_PATH") + "/queries.dat");
  connect();
}

RecordMapper::~RecordMapper(){
  if(connection){
    connection->close();
  }
}

void RecordMapper::connect(){
  try{
    sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();

    // 환경변수 가져오기
    string dbUrl = getEnvVar("DB_URL");
    string user = getEnvVar("DB_USER");
    string password = getEnvVar("DB_PASSWORD");

    // MySQL 연결 초기화

    connection.reset(driver->connect(dbUrl, user, password));
    

  }catch(sql::SQLException& e){
    cerr << "Error connecting to database: " << e.what() << endl;
  }
}

// 환경 변수 가져옴
string RecordMapper::getEnvVar(const string& varName){
  // dotenv 객체 생성 및 초기화(.env 파일 자동 로드)
  return env.get(varName);
}

void RecordMapper::loadQueries(const string& filePath){
  ifstream file(filePath);
  if(!file.is_open()){
    throw runtime_error("Failed to open queries file");
  }

  string line;
  while(getline(file, line)){
    istringstream iss(line);
    string key, value;
    if(getline(iss, key, '=') && getline(iss, value)){
      queries[key] = value;
    }
  }
}

void RecordMapper::insertRecord(const Record& record){
  try{
    const string& query = queries.at("insertRecord");
    unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));

    auto timeT = chrono::system_clock::to_time_t(record.time);
    char buffer[20] = {0};
    tm timeStruct;

    #if defined(_WIN32) || defined(_WIN64)
      localtime_s(&timeStruct, &timeT);
    #else
      timeStruct = *localtime(&timeT);
    #endif

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeStruct);
    string formmattedTime(buffer);

    // PreparedStatement에 값 설정
    pstmt->setString(1, formmattedTime);
    pstmt->setInt(2, record.subscribers);
    pstmt->setInt(3, record.dropouts);
    pstmt->setInt(4, record.paymentAmount);
    pstmt->setInt(5, record.amountUsed);
    pstmt->setInt(6, record.salesAmount);

    pstmt->executeUpdate();
    cout << "Record insert successfully: "<< record.toString() << endl;

  }catch(const sql::SQLException& e){
    cerr << "Error insert Record: " << e.what() << endl;
  }
}

vector<Record> RecordMapper::selectRecord(const string& dateTime){
  vector<Record> records;

  try{
    const string& query = queries.at("selectRecords");
    unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));
    pstmt->setString(1, dateTime);

    unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
    Record record;
    while(res->next()){
      record.init();

      string timeStr = res->getString("time");
      tm tm= {};
      istringstream ss(timeStr);
      ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
      if(!ss.fail()){
        time_t timeT = mktime(&tm);
        record.time = chrono::system_clock::from_time_t(timeT);
      }else{
        record.time = chrono::system_clock::time_point{};
      }
      
      record.subscribers = res->getInt("subscribers");
      record.dropouts = res->getInt("dropouts");
      record.paymentAmount = res->getInt("payment_amount");
      record.amountUsed = res->getInt("amount_used");
      record.salesAmount = res->getInt("sales_amount");
      records.push_back(move(record));
    }

  }catch(const sql::SQLException& e){
    cerr << "Error select records: " << e.what() << endl;
  }

  return records;
}