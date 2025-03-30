cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름 및 버전 설정
project(SchedulerProject VERSION 1.0 LANGUAGES CXX)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 소스 및 헤더 파일 경로 지정
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(CONFIG_DIR "${CMAKE_SOURCE_DIR}/config")
set(SCRIPTS_DIR "${CMAKE_SOURCE_DIR}/scripts")

# 실행 파일 이름
set(EXECUTABLE_NAME Scheduler)

# include 디렉토리 추가
include_directories(${INCLUDE_DIR})

# 소스 파일 모음
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")

# 실행 파일 생성
add_executable(${EXECUTABLE_NAME} ${SRC_FILES})

# 환경변수 파일(.env) 경로 추가
configure_file(${CONFIG_DIR}/.env ${CMAKE_BINARY_DIR}/.env COPYONLY)

# 컴파일 옵션 추가 (필요에 따라 변경)
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -pedantic)

# MySQL 라이브러리 연결 (필요한 경우 설정)
find_package(MySQL REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} MySQL::Client)

# dotenv 라이브러리 연결 (필요한 경우 설정)
find_library(DOTENV_LIB dotenv REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} ${DOTENV_LIB})