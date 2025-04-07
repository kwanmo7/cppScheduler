#define UNIT_TEST2

#include "SchedulerService.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Record.h"
#include <memory>

using namespace std;
using namespace testing;

class MockRecordMapper : public RecordMapper {
public:
  MOCK_METHOD(void, insertRecord, (const Record&), ());
};

class SchedulerServiceTest : public ::testing::Test {
protected:
  MockRecordMapper mockMapper;
  SchedulerService service{mockMapper};
};

TEST_F(SchedulerServiceTest, SplitStringByDelimiter) {
  string input = "100|10|2000|1500|3000";
  vector<string> expected = {"100", "10", "2000", "1500", "3000"};

  auto result = service.split(input, '|');
  EXPECT_EQ(result, expected);
}

TEST_F(SchedulerServiceTest, ProcessValidTxtRecord_ShouldCallInsert) {
  vector<string> input = {"2025-04-06 01:02:03", "100", "10", "2000", "1500", "3000"};

  EXPECT_CALL(mockMapper, insertRecord(_)).Times(1);
  service.processRecordForTxt(input);
}

TEST_F(SchedulerServiceTest, ProcessInvalidTxtRecord_ShouldNotCallInsert) {
  vector<string> input = {"invalid", "abc", "def"};

  EXPECT_CALL(mockMapper, insertRecord(_)).Times(0);
  service.processRecordForTxt(input);
}

TEST_F(SchedulerServiceTest, ProcessValidCsvRecord_ShouldCallInsert) {
  vector<string> input = {"2025-04-06 01:02:03", "100", "10", "2000", "1500", "3000"};

  EXPECT_CALL(mockMapper, insertRecord(_)).Times(1);
  service.processRecordForCsv(input);
}

TEST_F(SchedulerServiceTest, ProcessInvalidCsvRecord_ShouldNotCallInsert) {
  vector<string> input = {"wrong", "bad", "data"};

  EXPECT_CALL(mockMapper, insertRecord(_)).Times(0);
  service.processRecordForCsv(input);
}
