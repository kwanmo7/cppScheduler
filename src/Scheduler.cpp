#include "Scheduler.h"
#include "FileProcessor.h"
#include <iostream>

void Scheduler::run(){
  std::cout << "Running scheduled task ..." << std::endl;
  FileProcessor FileProcessor;
  FileProcessor.processFiles("input/");
}