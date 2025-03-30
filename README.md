# cppScheduler

## 개요
SchedulerProject는 파일 데이터 처리를 자동화하고 데이터베이스에 저장하는 프로그램입니다.  
TXT 및 CSV 파일을 읽고 데이터를 처리하여 MySQL 데이터베이스에 기록하며, 매일 자정 0시에 자동 실행됩니다.

---

## 개발환경
```
C++17
MySQL
dotenv 라이브러리
Visual Studio Code(VS Code)
```

## 프로젝트 구조

```
cppScheduler/
├── src/                 # 소스 코드 (.cpp 파일)  
│   ├── FileProcessor.cpp  
│   ├── RecordMapper.cpp  
│   ├── RecordUtil.cpp  
│   ├── Scheduler.cpp  
│   ├── SchedulerService.cpp  
├── include/             # 헤더 파일 (.h 파일)  
│   ├── ConstVO.h  
│   ├── FileProcessor.h  
│   ├── RecordMapper.h  
│   ├── RecordUtil.h  
│   ├── Scheduler.h  
│   ├── SchedulerService.h  
├── config/              # 환경 설정 파일  
│   ├── .env  
│   ├── queries.dat  
├── scripts/             # 실행 스크립트  
│   ├── SchedulerScript.ksh  
├── logs/                # 로그 파일 저장소 (실행 중 생성됨)  
```

---

## 설치 방법

### 1. 소스 코드 클론
```bash
git clone https://github.com/kwanmo7/cppScheduler.git
cd cppScheduler
```

### 2. MySQL 및 dotenv 라이브러리 설치
MySQL 클라이언트를 설치하고, dotenv 라이브러리를 설치합니다.

### 3. CMake 빌드
```bash
mkdir build
cd build
cmake ..
make
```

---

## 실행 방법

### 1. 환경 변수 설정
`config/.env` 파일에서 데이터베이스 연결에 필요한 환경 변수를 설정합니다.

```bash
DB_URL=database-url
DB_USER=database-user
DB_PASSWORD=database-password
```

### 2. 쿼리 파일 설정
`config/queries.dat` 파일에 SQL 쿼리를 정의합니다.

### 3. 스케줄러 스크립트 실행
```bash
chmod +x scripts/SchedulerScript.ksh
./scripts/SchedulerScript.ksh
```

---

## 크론 작업 자동화

### 1. `crontab -e` 를 실행하여 크론 작업을 편집합니다.
### 2. 아래 줄을 추가하여 매일 자정 실행을 설정합니다.
```bash
0 0 * * * /path/to/scripts/SchedulerScript.ksh
```
### 3. 로그 파일은 `logs/scheduler.log` 에 기록됩니다.

---

## 로그 확인
실행 로그는 `logs/scheduler.log` 파일에 저장됩니다. 로그를 실시간으로 확인하려면 아래 명령어를 실행하세요.

```bash
tail -f logs/scheduler.log
```

