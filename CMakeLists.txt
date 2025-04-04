cmake_minimum_required(VERSION 3.10)

project(SchedulerProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 경로 변수 설정
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(CONFIG_DIR "${CMAKE_SOURCE_DIR}/config")
set(SCRIPTS_DIR "${CMAKE_SOURCE_DIR}/scripts")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/test")
set(EXECUTABLE_NAME Scheduler)

# MySQL Connector C++ 9.2 경로
set(MYSQL_CONNECTOR_DIR "C:/Program Files/MySQL/MySQL Connector C++ 9.2")
set(MYSQL_INCLUDE_DIR "${MYSQL_CONNECTOR_DIR}/include/jdbc")
set(MYSQL_LIB_DIR "${MYSQL_CONNECTOR_DIR}/lib64/vs14")

# 실행 파일 소스 설정
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")
add_executable(${EXECUTABLE_NAME} ${SRC_FILES})

# include 디렉토리 설정
target_include_directories(${EXECUTABLE_NAME} PRIVATE
  ${INCLUDE_DIR}
  "${MYSQL_INCLUDE_DIR}"
)

# MySQL 연결
target_link_directories(${EXECUTABLE_NAME} PRIVATE "${MYSQL_LIB_DIR}")
target_link_libraries(${EXECUTABLE_NAME} mysqlcppconn)

# 실행 시 필요한 DLL 복사
file(COPY "${MYSQL_CONNECTOR_DIR}/lib64/mysqlcppconn-10-vs14.dll" DESTINATION ${CMAKE_BINARY_DIR})

# 환경변수 파일(.env) 복사
configure_file(${CMAKE_SOURCE_DIR}/.env ${CMAKE_BINARY_DIR}/.env COPYONLY)

# 컴파일 옵션 분기 (MSVC 대응)
if (MSVC)
  target_compile_options(${EXECUTABLE_NAME} PRIVATE /W4 /utf-8)
else()
  target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

# ----------------------------
# Google Test 설정
# ----------------------------
add_subdirectory(googletest)

file(GLOB TEST_SOURCES "${TEST_DIR}/*.cpp")
add_executable(test_main ${TEST_SOURCES})

target_include_directories(test_main PRIVATE
  ${INCLUDE_DIR}
  "${MYSQL_INCLUDE_DIR}"
  ${CMAKE_SOURCE_DIR}/googletest/googletest/include
  ${CMAKE_SOURCE_DIR}/googletest/googlemock/include
)

target_link_directories(test_main PRIVATE "${MYSQL_LIB_DIR}")
target_link_libraries(test_main
  gtest
  gtest_main
  gmock
  mysqlcppconn
)

target_compile_definitions(test_main PRIVATE UNIT_TEST)

if (MSVC)
  target_compile_options(test_main PRIVATE /W4 /utf-8)
else()
  target_compile_options(test_main PRIVATE -Wall -Wextra -pedantic)
endif()
