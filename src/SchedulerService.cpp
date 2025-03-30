#include "SchedulerService.h"
#include "ConstVO.h"
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;
using namespace std;

SchedulerService::SchedulerService(RecordMapper& mapper) : recordMapper(mapper) {}

void SchedulerService::insertRecord(const Record& record){
  try{
    recordMapper.insertRecord(record);
  }catch(const exception& e){
    cerr << "Error insert record: " << e.what() << endl;
  }
}

void SchedulerService::readTxtFile(const filesystem::path& filePath){
  try{
    ifstream file(filePath);
    if(!file.is_open()){
      throw runtime_error("Failed to open txt file: " + filePath.string());
    }

    string line;
    line.clear();
    while(getline(file, line)){
      vector<string> tokens = split(line, ConstVO::textFileDelimiter);
    }

  }catch(const exception& e){
    cerr << "Error read txt file: " << e.what() << endl;
  }

}

void SchedulerService::readCsvFile(const filesystem::path& filePath){
  try{
    ifstream file(filePath);
    if(!file.is_open()){
      throw runtime_error("Failed to open csv file: " + filePath.string());
    }

    string line;
    line.clear();
    while(getline(file, line)){
      vector<string> tokens = split(line, ConstVO::csvFileDelimiter);
    }

  }catch(const exception& e){
    cerr << "Error read csv file: " << e.what() << endl;
  }
}

void SchedulerService::processRecordForTxt(const vector<string>& input){
  try{
    Record record = RecordUtil::createRecord(input);
    if(RecordUtil::isValid(record)){
      insertRecord(record);
    }
  }catch(const exception& e){
    cerr << "Error processing txt record: " << e.what() << endl;
  }
}

void SchedulerService::processRecordForCsv(const vector<string>& input){
  try{
    Record record = RecordUtil::createRecord(input);
    if(RecordUtil::isValid(record)){
      insertRecord(record);
    }
  }catch(const exception& e){
    cerr << "Error processing csv record: " << e.what() << endl;
  }
}

vector<string> SchedulerService::split(const string& str, char delimiter){
  vector<string> tokens;
  istringstream stream(str);
  string token;

  tokens.clear();
  stream.clear();
  token.clear();

  while(getline(stream, token, delimiter)){
    tokens.push_back(token);
  }

  return tokens;
}