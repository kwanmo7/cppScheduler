#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include <string>

class FileProcessor{
  public:
    explicit FileProcessor(SchedulerService* service);
    void processFiles(const std::string& directory);

  private:
    SchedulerService* schedulerService;
};

#endif // FILE_PROCESSOR_H