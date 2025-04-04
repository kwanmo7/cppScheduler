#include "RecordMapper.h"
#include "Record.h"
#include "MockSQL.h"
#include "SQLWrapper.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

using namespace std;
using ::testing::Return;
using ::testing::ByMove;
using ::testing::NiceMock;

class RecordMapperMockTest : public ::testing::Test {
protected:
    std::unique_ptr<RecordMapper> mapper;
    std::unique_ptr<NiceMock<sql::MockConnection>> mockConn;
    std::unique_ptr<NiceMock<sql::MockPreparedStatement>> mockStmt;
    std::unique_ptr<NiceMock<sql::MockResultSet>> mockResult;

    void SetUp() override {
        // mock 객체들을 생성
        mockConn = std::make_unique<NiceMock<sql::MockConnection>>();
        mockStmt = std::make_unique<NiceMock<sql::MockPreparedStatement>>();
        mockResult = std::make_unique<NiceMock<sql::MockResultSet>>();

        // Statement가 준비되었을 때 mockStmt 반환
        EXPECT_CALL(*mockConn, prepareStatement(::testing::_))
            .WillRepeatedly(Return(ByMove(std::move(mockStmt))));

        // query 실행 시 mockResult 반환
        EXPECT_CALL(*mockStmt, executeQuery())
            .WillRepeatedly(Return(ByMove(std::move(mockResult))));

        // insert용 executeUpdate도 허용
        EXPECT_CALL(*mockStmt, executeUpdate())
            .WillRepeatedly(Return(1));

        // RecordMapper 생성자에서 사용할 수 있도록 MockSQL을 생성
        class TestSQL : public SQLWrapper {
        public:
            explicit TestSQL(std::unique_ptr<sql::Connection> conn)
                : conn_(std::move(conn)) {}

            std::unique_ptr<sql::Connection> createConnection() override {
                return std::move(conn_);
            }

        private:
            std::unique_ptr<sql::Connection> conn_;
        };

        mapper = std::make_unique<RecordMapper>(std::make_unique<TestSQL>(std::move(mockConn)));
        mapper->loadQueries("test_queries.dat");  // 테스트용 dummy 쿼리 파일
    }

    void TearDown() override {
        mapper.reset();
    }
};

TEST_F(RecordMapperMockTest, InsertRecordCallsExecuteUpdate) {
    Record rec;
    rec.init();
    rec.subscribers = 100;
    EXPECT_NO_THROW(mapper->insertRecord(rec));
}

TEST_F(RecordMapperMockTest, SelectRecordReturnsMockedResult) {
    // select용 next() -> true 1번, false 1번
    EXPECT_CALL(*mockResult, next()).WillOnce(Return(true)).WillOnce(Return(false));
    EXPECT_CALL(*mockResult, getString("time")).WillOnce(Return("2024-04-05 12:34:56"));
    EXPECT_CALL(*mockResult, getInt("subscribers")).WillOnce(Return(111));
    EXPECT_CALL(*mockResult, getInt("dropouts")).WillOnce(Return(0));
    EXPECT_CALL(*mockResult, getInt("payment_amount")).WillOnce(Return(200));
    EXPECT_CALL(*mockResult, getInt("amount_used")).WillOnce(Return(150));
    EXPECT_CALL(*mockResult, getInt("sales_amount")).WillOnce(Return(300));

    auto results = mapper->selectRecord("2024-04-05 12:34:56");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].subscribers, 111);
}
