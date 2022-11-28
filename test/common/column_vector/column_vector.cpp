//
// Created by JinHai on 2022/11/28.
//

#include <gtest/gtest.h>
#include "base_test.h"
#include "common/column_vector/column_vector.h"
#include "common/types/value.h"
#include "main/logger.h"
#include "main/stats/global_resource_usage.h"

class ColumnVectorTest : public BaseTest {
    void
    SetUp() override {
        infinity::Logger::Initialize();
        infinity::GlobalResourceUsage::Init();
    }

    void
    TearDown() override {
        infinity::Logger::Shutdown();
        EXPECT_EQ(infinity::GlobalResourceUsage::GetObjectCount(), 0);
        EXPECT_EQ(infinity::GlobalResourceUsage::GetRawMemoryCount(), 0);
        infinity::GlobalResourceUsage::UnInit();
    }
};

TEST_F(ColumnVectorTest, flat_tinyint) {
    using namespace infinity;

    DataType data_type(LogicalType::kTinyInt);
    ColumnVector col_tinyint(data_type, ColumnVectorType::kFlat);
    col_tinyint.Initialize();

    EXPECT_THROW(col_tinyint.SetDataType(DataType(LogicalType::kTinyInt)), std::logic_error);
    EXPECT_THROW(col_tinyint.SetVectorType(ColumnVectorType::kFlat), std::logic_error);

    EXPECT_EQ(col_tinyint.capacity(), DEFAULT_VECTOR_SIZE);
    EXPECT_EQ(col_tinyint.Size(), 0);
    EXPECT_THROW(col_tinyint.ToString(), std::logic_error);
    EXPECT_THROW(col_tinyint.GetValue(0), std::logic_error);
    EXPECT_EQ(col_tinyint.tail_index_, 0);
    EXPECT_EQ(col_tinyint.data_type_size_, 1);
    EXPECT_NE(col_tinyint.data_ptr_, nullptr);
    EXPECT_EQ(col_tinyint.vector_type(), ColumnVectorType::kFlat);
    EXPECT_EQ(col_tinyint.data_type(), data_type);

    EXPECT_NE(col_tinyint.buffer_, nullptr);
    EXPECT_EQ(col_tinyint.nulls_ptr_, nullptr);
    EXPECT_TRUE(col_tinyint.initialized);
    col_tinyint.Reserve(DEFAULT_VECTOR_SIZE - 1);
    auto tmp_ptr = col_tinyint.data_ptr_;
    EXPECT_EQ(col_tinyint.capacity(), DEFAULT_VECTOR_SIZE);
    EXPECT_EQ(tmp_ptr, col_tinyint.data_ptr_);

    for(i64 i = 0; i < DEFAULT_VECTOR_SIZE; ++ i) {
        Value v = Value::MakeTinyInt(static_cast<TinyIntT>(i));
        col_tinyint.AppendValue(v);
        Value vx = col_tinyint.GetValue(i);
        EXPECT_EQ(vx.type().type(), LogicalType::kTinyInt);
        EXPECT_EQ(vx.value_.tiny_int, static_cast<TinyIntT>(i));
        EXPECT_THROW(col_tinyint.GetValue(i + 1), std::logic_error);
    }

    col_tinyint.Reserve(DEFAULT_VECTOR_SIZE* 2);

    for(i64 i = 0; i < DEFAULT_VECTOR_SIZE; ++ i) {
        Value vx = col_tinyint.GetValue(i);
        EXPECT_EQ(vx.type().type(), LogicalType::kTinyInt);
        EXPECT_EQ(vx.value_.tiny_int, static_cast<TinyIntT>(i));
    }
    EXPECT_EQ(col_tinyint.tail_index_, DEFAULT_VECTOR_SIZE);
    EXPECT_EQ(col_tinyint.capacity(), 2* DEFAULT_VECTOR_SIZE);

    for(i64 i = DEFAULT_VECTOR_SIZE; i < 2 * DEFAULT_VECTOR_SIZE; ++ i) {
        Value v = Value::MakeTinyInt(static_cast<TinyIntT>(i));
        col_tinyint.AppendValue(v);
        Value vx = col_tinyint.GetValue(i);
        EXPECT_EQ(vx.type().type(), LogicalType::kTinyInt);
        EXPECT_EQ(vx.value_.tiny_int, static_cast<TinyIntT>(i));
        EXPECT_THROW(col_tinyint.GetValue(i + 1), std::logic_error);
    }

    col_tinyint.Reset();
    EXPECT_EQ(col_tinyint.capacity(), 0);
    EXPECT_EQ(col_tinyint.tail_index_, 0);
    EXPECT_EQ(col_tinyint.data_type_size_, 0);
    EXPECT_EQ(col_tinyint.buffer_, nullptr);
    EXPECT_EQ(col_tinyint.data_ptr_, nullptr);
    EXPECT_EQ(col_tinyint.initialized, false);
    EXPECT_EQ(col_tinyint.data_type(), DataType(LogicalType::kInvalid));
    EXPECT_EQ(col_tinyint.vector_type(), ColumnVectorType::kInvalid);

    // ====
    EXPECT_THROW(col_tinyint.Initialize(), std::logic_error);
    col_tinyint.SetDataType(DataType(LogicalType::kTinyInt));
    EXPECT_THROW(col_tinyint.Initialize(), std::logic_error);
    col_tinyint.SetVectorType(ColumnVectorType::kFlat);
    col_tinyint.Initialize();
    EXPECT_THROW(col_tinyint.SetDataType(DataType(LogicalType::kTinyInt)), std::logic_error);
    EXPECT_THROW(col_tinyint.SetVectorType(ColumnVectorType::kFlat), std::logic_error);

    EXPECT_EQ(col_tinyint.capacity(), DEFAULT_VECTOR_SIZE);
    EXPECT_EQ(col_tinyint.Size(), 0);
    EXPECT_THROW(col_tinyint.ToString(), std::logic_error);
    EXPECT_THROW(col_tinyint.GetValue(0), std::logic_error);
    EXPECT_EQ(col_tinyint.tail_index_, 0);
    EXPECT_EQ(col_tinyint.data_type_size_, 1);
    EXPECT_NE(col_tinyint.data_ptr_, nullptr);
    EXPECT_EQ(col_tinyint.vector_type(), ColumnVectorType::kFlat);
    EXPECT_EQ(col_tinyint.data_type(), data_type);

    EXPECT_NE(col_tinyint.buffer_, nullptr);
    EXPECT_EQ(col_tinyint.nulls_ptr_, nullptr);
    EXPECT_TRUE(col_tinyint.initialized);
    col_tinyint.Reserve(DEFAULT_VECTOR_SIZE - 1);
    tmp_ptr = col_tinyint.data_ptr_;
    EXPECT_EQ(col_tinyint.capacity(), DEFAULT_VECTOR_SIZE);
    EXPECT_EQ(tmp_ptr, col_tinyint.data_ptr_);

    for(i64 i = 0; i < DEFAULT_VECTOR_SIZE; ++ i) {
        Value v = Value::MakeTinyInt(static_cast<TinyIntT>(i));
        col_tinyint.AppendValue(v);
        Value vx = col_tinyint.GetValue(i);
        EXPECT_EQ(vx.type().type(), LogicalType::kTinyInt);
        EXPECT_EQ(vx.value_.tiny_int, static_cast<TinyIntT>(i));
        EXPECT_THROW(col_tinyint.GetValue(i + 1), std::logic_error);
    }
}

TEST_F(ColumnVectorTest, flat_smallint) {
    using namespace infinity;

    DataType data_type(LogicalType::kSmallInt);
    ColumnVector col_smallint(data_type, ColumnVectorType::kFlat);
    col_smallint.Initialize();

    EXPECT_THROW(col_smallint.SetDataType(DataType(LogicalType::kSmallInt)), std::logic_error);
    EXPECT_THROW(col_smallint.SetVectorType(ColumnVectorType::kFlat), std::logic_error);

    EXPECT_EQ(col_smallint.capacity(), DEFAULT_VECTOR_SIZE);
    EXPECT_EQ(col_smallint.Size(), 0);
    EXPECT_THROW(col_smallint.ToString(), std::logic_error);
    EXPECT_THROW(col_smallint.GetValue(0), std::logic_error);
    EXPECT_EQ(col_smallint.tail_index_, 0);
    EXPECT_EQ(col_smallint.data_type_size_, 2);
    EXPECT_NE(col_smallint.data_ptr_, nullptr);
    EXPECT_EQ(col_smallint.vector_type(), ColumnVectorType::kFlat);
    EXPECT_EQ(col_smallint.data_type(), data_type);

    EXPECT_NE(col_smallint.buffer_, nullptr);
    EXPECT_EQ(col_smallint.nulls_ptr_, nullptr);
    EXPECT_TRUE(col_smallint.initialized);
    col_smallint.Reserve(DEFAULT_VECTOR_SIZE - 1);
    auto tmp_ptr = col_smallint.data_ptr_;
    EXPECT_EQ(col_smallint.capacity(), DEFAULT_VECTOR_SIZE);
    EXPECT_EQ(tmp_ptr, col_smallint.data_ptr_);

    for(i64 i = 0; i < DEFAULT_VECTOR_SIZE; ++ i) {
        Value v = Value::MakeSmallInt(static_cast<SmallIntT>(i));
        col_smallint.AppendValue(v);
        Value vx = col_smallint.GetValue(i);
        EXPECT_EQ(vx.type().type(), LogicalType::kSmallInt);
        EXPECT_EQ(vx.value_.small_int, static_cast<SmallIntT>(i));
        EXPECT_THROW(col_smallint.GetValue(i + 1), std::logic_error);
    }

    col_smallint.Reserve(DEFAULT_VECTOR_SIZE* 2);

    for(i64 i = 0; i < DEFAULT_VECTOR_SIZE; ++ i) {
        Value vx = col_smallint.GetValue(i);
        EXPECT_EQ(vx.type().type(), LogicalType::kSmallInt);
        EXPECT_EQ(vx.value_.small_int, static_cast<SmallIntT>(i));
    }
    EXPECT_EQ(col_smallint.tail_index_, DEFAULT_VECTOR_SIZE);
    EXPECT_EQ(col_smallint.capacity(), 2* DEFAULT_VECTOR_SIZE);

    for(i64 i = DEFAULT_VECTOR_SIZE; i < 2 * DEFAULT_VECTOR_SIZE; ++ i) {
        Value v = Value::MakeSmallInt(static_cast<SmallIntT>(i));
        col_smallint.AppendValue(v);
        Value vx = col_smallint.GetValue(i);
        EXPECT_EQ(vx.type().type(), LogicalType::kSmallInt);
        EXPECT_EQ(vx.value_.small_int, static_cast<SmallIntT>(i));
        EXPECT_THROW(col_smallint.GetValue(i + 1), std::logic_error);
    }

    col_smallint.Reset();
    EXPECT_EQ(col_smallint.capacity(), 0);
    EXPECT_EQ(col_smallint.tail_index_, 0);
    EXPECT_EQ(col_smallint.data_type_size_, 0);
    EXPECT_EQ(col_smallint.buffer_, nullptr);
    EXPECT_EQ(col_smallint.data_ptr_, nullptr);
    EXPECT_EQ(col_smallint.initialized, false);
    EXPECT_EQ(col_smallint.data_type(), DataType(LogicalType::kInvalid));
    EXPECT_EQ(col_smallint.vector_type(), ColumnVectorType::kInvalid);

    // ====
    EXPECT_THROW(col_smallint.Initialize(), std::logic_error);
    col_smallint.SetDataType(DataType(LogicalType::kSmallInt));
    EXPECT_THROW(col_smallint.Initialize(), std::logic_error);
    col_smallint.SetVectorType(ColumnVectorType::kFlat);
    col_smallint.Initialize();
    EXPECT_THROW(col_smallint.SetDataType(DataType(LogicalType::kSmallInt)), std::logic_error);
    EXPECT_THROW(col_smallint.SetVectorType(ColumnVectorType::kFlat), std::logic_error);

    EXPECT_EQ(col_smallint.capacity(), DEFAULT_VECTOR_SIZE);
    EXPECT_EQ(col_smallint.Size(), 0);
    EXPECT_THROW(col_smallint.ToString(), std::logic_error);
    EXPECT_THROW(col_smallint.GetValue(0), std::logic_error);
    EXPECT_EQ(col_smallint.tail_index_, 0);
    EXPECT_EQ(col_smallint.data_type_size_, 2);
    EXPECT_NE(col_smallint.data_ptr_, nullptr);
    EXPECT_EQ(col_smallint.vector_type(), ColumnVectorType::kFlat);
    EXPECT_EQ(col_smallint.data_type(), data_type);

    EXPECT_NE(col_smallint.buffer_, nullptr);
    EXPECT_EQ(col_smallint.nulls_ptr_, nullptr);
    EXPECT_TRUE(col_smallint.initialized);
    col_smallint.Reserve(DEFAULT_VECTOR_SIZE - 1);
    tmp_ptr = col_smallint.data_ptr_;
    EXPECT_EQ(col_smallint.capacity(), DEFAULT_VECTOR_SIZE);
    EXPECT_EQ(tmp_ptr, col_smallint.data_ptr_);

    for(i64 i = 0; i < DEFAULT_VECTOR_SIZE; ++ i) {
        Value v = Value::MakeSmallInt(static_cast<SmallIntT>(i));
        col_smallint.AppendValue(v);
        Value vx = col_smallint.GetValue(i);
        EXPECT_EQ(vx.type().type(), LogicalType::kSmallInt);
        EXPECT_EQ(vx.value_.small_int, static_cast<SmallIntT>(i));
        EXPECT_THROW(col_smallint.GetValue(i + 1), std::logic_error);
    }
}