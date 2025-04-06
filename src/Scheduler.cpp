#include "Scheduler.h"
#include "FileProcessor.h"
#include "SchedulerService.h"
#include "RecordMapper.h"
#include <iostream>

void Scheduler::run(){
  std::cout << "Running scheduled task ..." << std::endl;

  Recordmapper mapper;
  SchedulerService service(mapper);

  FileProcessor FileProcessor;
  FileProcessor.processFiles("input/");
}