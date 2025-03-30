#ifndef RECORD_UTIL_H
#define RECORD_UTIL_H

#include "Record.h"
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

class RecordUtil{
  public:
    // txt에서 레코드 생성
    static Record createRecord(const std::vector<std::string>& input);

    // csv에서 레코드 생성
    static Record createRecord(const std::vector<std::string>& input, std::time_t formatter);
    
    // Record 유효성 검사
    static bool isValid(const Record& record);

};


#endif // RECORD_UTIL_H