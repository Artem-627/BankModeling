#pragma once

#include <cstdint>

namespace bank_time
{
    constexpr std::uint64_t MINUTES_IN_HOUR = 60;
    constexpr std::uint64_t MINUTES_IN_DAY = (60 * 24);
    constexpr std::uint64_t MINUTES_IN_WEEK = (60 * 24 * 7);

    enum class WeekDay
    {
        Monday = 0,
        Tuesday = 1,
        Wednesday = 2,
        Thursday = 3,
        Friday = 4,
        Saturday = 5,
        Sunday = 6
    };

    inline WeekDay toWeekDay(std::uint64_t day);

    // WeekDay operators
    WeekDay operator+(WeekDay week_day, std::uint64_t days);
    WeekDay operator-(WeekDay week_day, std::uint64_t days);
    WeekDay& operator+=(WeekDay& week_day, std::uint64_t days);
    WeekDay& operator-=(WeekDay& week_day, std::uint64_t days);
    WeekDay operator++(WeekDay& week_day);
    WeekDay operator++(WeekDay& week_day, int);
    WeekDay operator--(WeekDay& week_day);
    WeekDay operator--(WeekDay& week_day, int);


    class Time
    {
    public:
        Time() = default;
        explicit Time(std::uint64_t minutes);
        Time(WeekDay week_day, std::uint8_t hours, std::uint8_t minutes);
        ~Time() = default;


        // Getters
        [[nodiscard]]
        WeekDay weekDay() const;

        [[nodiscard]]
        std::uint8_t hours() const;

        [[nodiscard]]
        std::uint8_t minutes() const;

        [[nodiscard]]
        std::uint64_t toMinutes() const;

        // Friend functions
        friend Time operator+(const Time& time, std::uint64_t minutes);
        friend Time operator-(const Time& time, std::uint64_t minutes);
        friend Time operator++(Time& time);
        friend Time operator++(Time& time, int);
        friend Time operator--(Time& time);
        friend Time operator--(Time& time, int);
        friend bool operator==(const Time& time1, const Time& time2);
        friend bool operator!=(const Time& time1, const Time& time2);

    private:
        WeekDay week_day_;
        std::uint8_t hours_;
        std::uint8_t minutes_;
    };

    // Time operators
    Time operator+(const Time& time, std::uint64_t minutes);
    Time operator-(const Time& time, std::uint64_t minutes);
    Time operator++(Time& time);
    Time operator++(Time& time, int);
    Time operator--(Time& time);
    Time operator--(Time& time, int);
    bool operator==(const Time& time1, const Time& time2);
    bool operator!=(const Time& time1, const Time& time2);
}
