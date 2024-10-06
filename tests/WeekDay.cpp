#include <gtest/gtest.h>
#include "../include/Time.h"


TEST(WeekDayTest, AdditionOperator)
{
    EXPECT_EQ(bank_time::WeekDay::Tuesday, bank_time::WeekDay::Monday + 1);
    EXPECT_EQ(bank_time::WeekDay::Monday, bank_time::WeekDay::Sunday + 1);
}

TEST(WeekDayTest, SubtractionOperator)
{
    EXPECT_EQ(bank_time::WeekDay::Saturday, bank_time::WeekDay::Sunday - 1);
    EXPECT_EQ(bank_time::WeekDay::Friday, bank_time::WeekDay::Saturday - 1);
    EXPECT_EQ(bank_time::WeekDay::Monday, bank_time::WeekDay::Tuesday - 1);
    EXPECT_EQ(bank_time::WeekDay::Sunday, bank_time::WeekDay::Monday - 1);
}

TEST(WeekDayTest, IncrementOperator)
{
    bank_time::WeekDay day = bank_time::WeekDay::Monday;
    EXPECT_EQ(bank_time::WeekDay::Monday, day);
    EXPECT_EQ(bank_time::WeekDay::Tuesday, ++day);
    EXPECT_EQ(bank_time::WeekDay::Tuesday, day++);
    EXPECT_EQ(bank_time::WeekDay::Wednesday, day);
}

TEST(WeekDayTest, DecrementOperator)
{
    bank_time::WeekDay day = bank_time::WeekDay::Monday;
    EXPECT_EQ(bank_time::WeekDay::Sunday, --day);
    EXPECT_EQ(bank_time::WeekDay::Sunday, day--);
    EXPECT_EQ(bank_time::WeekDay::Saturday, day);
}

TEST(WeekDayTest, AdditionAssignmentOperator)
{
    bank_time::WeekDay day = bank_time::WeekDay::Monday;
    day += 2;
    EXPECT_EQ(bank_time::WeekDay::Wednesday, day);
}

TEST(WeekDayTest, SubtractionAssignmentOperator)
{
    bank_time::WeekDay day = bank_time::WeekDay::Monday;
    day -= 2;
    EXPECT_EQ(bank_time::WeekDay::Saturday, day);
}
