#include "../include/Time.h"

#include <stdexcept>

namespace bank_time
{
    // WeekDay
    WeekDay operator+(WeekDay week_day, const std::uint64_t days)
    {
        return static_cast<WeekDay>((static_cast<std::uint64_t>(week_day) + days) % 7);
    }

    WeekDay operator-(WeekDay week_day, const std::uint64_t days)
    {
        return static_cast<WeekDay>((static_cast<std::uint64_t>(week_day) + 7 - days % 7) % 7);
    }

    WeekDay operator++(WeekDay& week_day)
    {
        week_day += 1;

        return week_day;
    }

    WeekDay operator++(WeekDay& week_day, const int)
    {
        const WeekDay temp = week_day;

        week_day += 1;

        return temp;
    }

    WeekDay operator--(WeekDay& week_day)
    {
        week_day -= 1;

        return week_day;
    }

    WeekDay operator--(WeekDay& week_day, const int)
    {
        const WeekDay temp = week_day;

        week_day -= 1;

        return temp;
    }

    WeekDay& operator+=(WeekDay& week_day, const std::uint64_t days)
    {
        week_day = week_day + days;

        return week_day;
    }

    WeekDay& operator-=(WeekDay& week_day, const std::uint64_t days)
    {
        week_day = week_day - days;

        return week_day;
    }

    WeekDay toWeekDay(const std::uint64_t day)
    {
        return static_cast<WeekDay>(day % 7);
    }

    // Time
    Time::Time(const WeekDay week_day, const std::uint8_t hours, const std::uint8_t minutes)
        : week_day_(week_day),
          hours_(hours),
          minutes_(minutes)
    {
    }

    Time::Time(const std::uint64_t minutes)
        : week_day_(toWeekDay(minutes / kMinutesInDay)),
          hours_((minutes % kMinutesInDay) / kMinutesInHour),
          minutes_(minutes % kMinutesInHour)
    {
    }


    WeekDay Time::weekDay() const
    {
        return week_day_;
    }

    std::uint8_t Time::hours() const
    {
        return hours_;
    }

    std::uint8_t Time::minutes() const
    {
        return minutes_;
    }

    std::uint64_t Time::toMinutes() const
    {
        return (static_cast<std::uint64_t>(week_day_) * kMinutesInDay) + (hours_ * kMinutesInHour) + minutes_;
    }


    // Time operators
    Time operator+(const Time& time, const std::uint64_t minutes)
    {
        const Time result(time.toMinutes() + minutes);

        return result;
    }

    Time operator-(const Time& time, const std::uint64_t minutes)
    {
        const Time result(
            ((time.toMinutes() + kMinutesInWeek) - (minutes % kMinutesInWeek)) % kMinutesInWeek
        );

        return result;
    }

    Time operator+(const Time& time1, const Time& time2)
    {
        const Time result(time1.toMinutes() + time2.toMinutes());

        return result;
    }

    Time operator-(const Time& time1, const Time& time2)
    {
        if (time1.toMinutes() < time2.toMinutes())
        {
            throw std::logic_error("Time1 is less than Time2");
        }

        const Time result(time1.toMinutes() + kMinutesInWeek - time2.toMinutes());

        return result;
    }

    Time operator++(Time& time)
    {
        time = time + 1;

        return time;
    }

    Time operator++(Time& time, const int)
    {
        Time temp(time);

        time = time + 1;

        return temp;
    }

    Time operator--(Time& time)
    {
        time = time - 1;

        return time;
    }

    Time operator--(Time& time, const int)
    {
        Time temp(time);

        time = time - 1;

        return temp;
    }

    bool operator==(const Time& time1, const Time& time2)
    {
        return time1.toMinutes() == time2.toMinutes();
    }

    bool operator!=(const Time& time1, const Time& time2)
    {
        return time1.toMinutes() != time2.toMinutes();
    }
}
