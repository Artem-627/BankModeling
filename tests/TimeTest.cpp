#include <gtest/gtest.h>
#include "../include/Time.h"


TEST(TimeTest, ConstructorAndGetters)
{
    const bank_time::Time t(bank_time::WeekDay::Monday, 10, 30);
    EXPECT_EQ(bank_time::WeekDay::Monday, t.weekDay());
    EXPECT_EQ(10, t.hours());
    EXPECT_EQ(30, t.minutes());

    const bank_time::Time t1(150); // 2 hours 30 minutes
    EXPECT_EQ(bank_time::WeekDay::Monday, t1.weekDay());
    EXPECT_EQ(2, t1.hours());
    EXPECT_EQ(30, t1.minutes());

    const bank_time::Time t2(1 * bank_time::MINUTES_IN_DAY + 1 * bank_time::MINUTES_IN_HOUR + 30);
    // 1 day 1 hour 30 minutes
    EXPECT_EQ(bank_time::WeekDay::Tuesday, t2.weekDay());
    EXPECT_EQ(1, t2.hours());
    EXPECT_EQ(30, t2.minutes());

    const bank_time::Time t3(
        1 * bank_time::MINUTES_IN_WEEK + 1 * bank_time::MINUTES_IN_DAY + 1 * bank_time::MINUTES_IN_HOUR
    );
    // 1 week 1 day 1 hour
    EXPECT_EQ(bank_time::WeekDay::Tuesday, t3.weekDay());
    EXPECT_EQ(1, t3.hours());
    EXPECT_EQ(0, t3.minutes());
}

TEST(TimeTest, ToMinutes)
{
    const bank_time::Time t1(150); // 2 hours 30 minutes
    EXPECT_EQ(150, t1.toMinutes());

    const bank_time::Time t2(1 * bank_time::MINUTES_IN_DAY + 1 * bank_time::MINUTES_IN_HOUR + 30);
    // 1 day 1 hour 30 minutes
    EXPECT_EQ(1 * bank_time::MINUTES_IN_DAY + 1 * bank_time::MINUTES_IN_HOUR + 30, t2.toMinutes());

    const bank_time::Time t3(
        1 * bank_time::MINUTES_IN_WEEK + 1 * bank_time::MINUTES_IN_DAY + 1 * bank_time::MINUTES_IN_HOUR
    );
    // 1 week 1 day 1 hour
    EXPECT_EQ(
        (1 * bank_time::MINUTES_IN_WEEK + 1 * bank_time::MINUTES_IN_DAY + 1 * bank_time::MINUTES_IN_HOUR) %
        bank_time::MINUTES_IN_WEEK,
        t3.toMinutes()
    );
}

TEST(TimeTest, AdditionOperator)
{
    bank_time::Time t(bank_time::WeekDay::Monday, 10, 30);
    t = t + 90; // 1 hour 30 minutes
    EXPECT_EQ(bank_time::WeekDay::Monday, t.weekDay());
    EXPECT_EQ(12, t.hours());
    EXPECT_EQ(0, t.minutes());

    t = t + (60 * 24 + 60); // 1 day 1 hour
    EXPECT_EQ(bank_time::WeekDay::Tuesday, t.weekDay());
    EXPECT_EQ(13, t.hours());
    EXPECT_EQ(0, t.minutes());
}

TEST(TimeTest, SubtractionOperator) {
    bank_time::Time t(bank_time::WeekDay::Monday, 10, 30);
    t = t - 90; // 1 hour 30 minutes
    EXPECT_EQ(bank_time::WeekDay::Monday, t.weekDay());
    EXPECT_EQ(9, t.hours());
    EXPECT_EQ(0, t.minutes());

    t = t - (1 * bank_time::MINUTES_IN_DAY + 15 * bank_time::MINUTES_IN_HOUR + 30); // 1 day 15 hour 30 minutes
    EXPECT_EQ(bank_time::WeekDay::Saturday, t.weekDay());
    EXPECT_EQ(17, t.hours());
    EXPECT_EQ(30, t.minutes());
}

TEST(TimeTest, IncrementOperator) {
    bank_time::Time t_inc(bank_time::WeekDay::Monday, 10, 30);
    bank_time::Time t_sum(bank_time::WeekDay::Monday, 10, 30);
    for (std::uint64_t i = 0; i < bank_time::MINUTES_IN_WEEK; ++i)
    {
        ++t_inc;
        t_sum = t_sum + 1;
        EXPECT_EQ(t_inc.weekDay(), t_inc.weekDay());
        EXPECT_EQ(t_inc.hours(), t_inc.hours());
        EXPECT_EQ(t_inc.minutes(), t_inc.minutes());
    }
}

TEST(TimeTest, DecrementOperator) {
    bank_time::Time t_inc(bank_time::WeekDay::Monday, 10, 30);
    bank_time::Time t_sum(bank_time::WeekDay::Monday, 10, 30);
    for (std::uint64_t i = 0; i < bank_time::MINUTES_IN_WEEK; ++i)
    {
        --t_inc;
        t_sum = t_sum - 1;
        EXPECT_EQ(t_inc.weekDay(), t_inc.weekDay());
        EXPECT_EQ(t_inc.hours(), t_inc.hours());
        EXPECT_EQ(t_inc.minutes(), t_inc.minutes());
    }
}

TEST(TimeTest, EqualityOperator) {
    const bank_time::Time t1(bank_time::WeekDay::Monday, 10, 30);
    const bank_time::Time t2(bank_time::WeekDay::Monday, 10, 30);
    EXPECT_TRUE(t1 == t2);

    const bank_time::Time t3(157);
    const bank_time::Time t4(157 + bank_time::MINUTES_IN_WEEK);
    EXPECT_TRUE(t3 == t4);
}

TEST(TimeTest, InequalityOperator) {
    const bank_time::Time t1(bank_time::WeekDay::Monday, 10, 30);
    const bank_time::Time t2(bank_time::WeekDay::Monday, 10, 31);
    EXPECT_TRUE(t1 != t2);
}
