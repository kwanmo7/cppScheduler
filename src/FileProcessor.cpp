#include "FileProcessor.h"
#include "ConstVO.h"
#include "SchedulerService.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void FileProcessor::processFiles(const std::string& directory){
  RecordMapper RecordMapper;
  SchedulerService schedulerService(RecordMapper);

  for(const auto& entry : fs::directory_iterator(directory)){
    try{
      if(entry.path().extension() == std::string(".") + ConstVO::suffixForTxt){
        std::cout << "Processing TXT file: " << entry.path() << std::endl;

        schedulerService.readTxtFile(entry.path().string());
      }else if(entry.path().extension() == std::string(".") + ConstVO::suffixForCsv){
        std::cout << "Processing CSV file: " << entry.path() << std::endl;

        schedulerService.readCsvFile(entry.path().string());
      }else{
        std::cerr << "Unsupported file type: " << entry.path() << std::endl;
      }
    }catch(const std::exception& e){
      std::cerr << "Error processing file: " << entry.path() << ": " << e.what() << std::endl;
    }
  }
}