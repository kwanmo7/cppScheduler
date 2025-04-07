#ifndef SCHEDULER_SERVICE_H
#define SCHEDULER_SERVICE_H

#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include "Record.h"
#include "RecordUtil.h"
#include "RecordMapper.h"

class SchedulerService{
  public:

      explicit SchedulerService(RecordMapper& mapper);

      void insertRecord(const Record& Record);
      void readTxtFile(const std::filesystem::path& file);
      void readCsvFile(const std::filesystem::path& file);
  
  private:
      void processRecordForTxt(const std::vector<std::string>& input);
      void processRecordForCsv(const std::vector<std::string>& input);

      std::vector<std::string> split(const std::string& str, char delimiter);

      RecordMapper& recordMapper;

  #ifdef UNIT_TEST2
      friend class ::SchedulerServiceTest;
  #endif
};

#endif // SCHEDULER_SERVICE_H