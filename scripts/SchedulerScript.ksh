#!/bin/ksh

# 프로그램 실행 경로
PROGRAM_PATH=""

# 로그 파일 경로
LOG_FILE="./logs/scheduler.log"

# 현재 시간 기록
echo "$(date): Executing Scheduler ... " >> $LOG_FILE

# 프로그램 실행 및 로그 기록
$PROGRAM_PATH >> $LOG_FILE 2>&1

if [ -f $PROGRAM_PATH ]; then
  # C++ 실행 파일 실행 및 결과 로그 저장
  echo "$(date): Executing the program at $PROGRAM_PATH" >> $LOG_FILE
  $PROGRAM_PATH >> $LOG_FILE 2>&1
  echo "$(date): Scheduler execution completed successfully." >> $LOG_FILE
else
  # 실행 파일이 없을 경우 오류 로그 저장
  echo "$(date): ERROR - Program not found at $PROGRAM_PATH" >> $LOG_FILE
fi
