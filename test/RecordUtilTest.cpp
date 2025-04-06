#include <gtest/gtest.h>
#include "RecordUtil.h"
#include "Record.h"
#include <chrono>
#include <ctime>

using namespace std;

class RecordUtilTest : public ::testing::Test{
  protected:
    vector<string> validInput = {
      "2025-04-06 01:02:03", "100", "10", "2000", "1515" , "353535"
    };
    vector<string> invalidInput = {
      "invalid", "abc", "dfdf"
    };
};


// createRecord(vector<string>) - 정상 입력
TEST_F(RecordUtilTest, CreateRecordWithoutFormatter_ShouldCreateValidRecord) {
  Record record = RecordUtil::createRecord(validInput);

  EXPECT_EQ(record.subscribers, 100);
  EXPECT_EQ(record.dropouts, 10);
  EXPECT_EQ(record.paymentAmount, 2000);
  EXPECT_EQ(record.amountUsed, 1515);
  EXPECT_EQ(record.salesAmount, 353535);
  EXPECT_TRUE(record.time.time_since_epoch().count() > 0);
}

// createRecord(vector<string>) - 입력 부족/잘못된 입력
TEST_F(RecordUtilTest, CreateRecordWithoutFormatter_ShouldReturnEmptyRecordOnInvalidInput) {
  Record record = RecordUtil::createRecord(invalidInput);

  EXPECT_EQ(record.subscribers, 0);
  EXPECT_EQ(record.dropouts, 0);
  EXPECT_EQ(record.paymentAmount, 0);
  EXPECT_EQ(record.amountUsed, 0);
  EXPECT_EQ(record.salesAmount, 0);
  EXPECT_EQ(record.time, chrono::system_clock::time_point());
}

// createRecord(vector<string>, time_t) - 정상 입력 및 시간 지정
TEST_F(RecordUtilTest, CreateRecordWithFormatter_ShouldUseGivenTime) {
  time_t rawTime = time(nullptr);
  Record record = RecordUtil::createRecord(validInput, rawTime);

  auto expectedTime = chrono::system_clock::from_time_t(rawTime);
  EXPECT_EQ(record.time, expectedTime);
  EXPECT_EQ(record.subscribers, 100);
  EXPECT_EQ(record.dropouts, 10);
  EXPECT_EQ(record.paymentAmount, 2000);
  EXPECT_EQ(record.amountUsed, 1515);
  EXPECT_EQ(record.salesAmount, 353535);
}

// isValid - 정상 레코드
TEST_F(RecordUtilTest, IsValid_ShouldReturnTrueForValidRecord) {
  Record record = RecordUtil::createRecord(validInput);
  EXPECT_TRUE(RecordUtil::isValid(record));
}

// isValid - 음수값 포함
TEST_F(RecordUtilTest, IsValid_ShouldReturnFalseForNegativeValues) {
  auto now = chrono::system_clock::now();
  Record record(now, -1, 0, 0, 0, 0);
  EXPECT_FALSE(RecordUtil::isValid(record));
}

// isValid - 시간 값 없음
TEST_F(RecordUtilTest, IsValid_ShouldReturnFalseForDefaultTime) {
  Record record;
  record.subscribers = 100;
  record.dropouts = 10;
  record.paymentAmount = 2000;
  record.amountUsed = 1515;
  record.salesAmount = 353535;
  record.time = chrono::system_clock::time_point();  // 비어있는 시간

  EXPECT_FALSE(RecordUtil::isValid(record));
}