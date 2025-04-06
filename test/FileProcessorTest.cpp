#define UNIT_TEST
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <filesystem>
#include <fstream>
#include "FileProcessor.h"
#include "SchedulerService.h"
#include "ConstVO.h"

using namespace std;
using namespace testing;
namespace fs = std::filesystem;

// Mock SchedulerService
class MockSchedulerService : public SchedulerService{
  public:
    MockSchedulerService() : SchedulerService(*static_cast<RecordMapper*>(nullptr)){}

    MOCK_METHOD(void, readTxtFile, (const std::string&), ());
    MOCK_METHOD(void, readCsvFile, (const std::string&), ());
};

// Test Fixture
class FileProcessorTest : public ::testing::Test{
  protected:
    fs::path testDir;

    void SetUp() override {
      testDir = fs::temp_directory_path() / "test_input_dir";
      fs::create_directory(testDir);

      // 테스트용 파일 생성
      ofstream(testDir / ("sample." + string(ConstVO::suffixForTxt))) << "dummy txt";
      ofstream(testDir / ("sample." + string(ConstVO::suffixForCsv))) << "dummy csv";
      ofstream(testDir / ("sample.md")) << "unsupported file";

    }

    void TearDown() override {
      fs::remove_all(testDir);
    }
};

// Test Case
TEST_F(FileProcessorTest, ShouldCallReadTxtAndCsvFile){
  MockSchedulerService mockService;
  FileProcessor processor(&mockService);

  EXPECT_CALL(mockService, readTxtFile(::testing::HasSubstr("sample.txt"))).Times(1);
  EXPECT_CALL(mockService, readCsvFile(::testing::HasSubstr("sample.csv"))).Times(1);

  processor.processFiles(testDir.string());
}