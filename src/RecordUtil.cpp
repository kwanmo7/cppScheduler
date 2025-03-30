#include "RecordUtil.h"
#include <iostream>

using namespace std;

Record RecordUtil::createRecord(const vector<string>& input){
  try{
    if(input.size() < 6){
      throw invalid_argument("Insufficient data for creating Record");
    }

    auto timePoint = chrono::system_clock::now();
    Record record(timePoint, stoi(input[1]), stoi(input[2]), stoi(input[3]),
                  stoi(input[4]), stoi(input[5]));
    return record;
  } catch(const exception& e){
    cerr << "Error creating Record from TXT: " << e.what() << endl;
    return Record();
  }
}

Record RecordUtil::createRecord(const vector<string>& input, time_t formatter){
  try{
    if(input.size() < 6){
      throw invalid_argument("Insufficient data for creating Record");
    }

    auto timePoint = chrono::system_clock::from_time_t(formatter);
    Record record(timePoint, stoi(input[1]), stoi(input[2]), stoi(input[3]),
                  stoi(input[4]), stoi(input[5]));

  }catch(const exception& e){
    cerr << "Error creating Record from CSV: " << e.what() << endl;
    return Record();
  }
}

bool RecordUtil::isValid(const Record& record){
  if(record.subscribers < 0 || record.dropouts < 0 ||
     record.paymentAmount < 0 || record.amountUsed < 0 || record.salesAmount < 0){
    return false;
  }
  if(record.time == chrono::system_clock::time_point()){
    return false;
  }

  return true;
}