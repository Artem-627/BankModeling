#pragma once

#include <cstdint>
#include <random>
#include <optional>

#include "Bank.h"
#include "Time.h"

namespace bank_time
{
    constexpr float kNormalDistrubutionMean = 6;
    constexpr float kNormalDistrubutionStddev = 1.5;

    constexpr std::uint64_t kModellingSpeed = 70; // One minute in moddeling equals to kModellingSpeed milliseconds

    constexpr std::uint64_t kMinRequestTime = 2;
    constexpr std::uint64_t kMaxRequestTime = 50;

    constexpr std::int64_t kMinRequestCost = 300;
    constexpr std::int64_t kMaxRequestCost = 5000;

    class TimeProcessing
    {
    public:
        TimeProcessing() = delete;

        TimeProcessing(bank::Bank* bank, Time* const &global_time);

        ~TimeProcessing();

        void start();

        void stop();

    private:
        Time* global_time_ = nullptr;
        bank::Bank* bank_;
        std::thread* time_processing_thread_ = nullptr;
        bool is_time_processing_work_ = false;
        std::random_device rd{};
        std::mt19937 gen{rd()};
        std::uniform_real_distribution<float> random_probability_{0.0, 1.0};
        std::normal_distribution<float>* time_interval_distribution_;
        std::uniform_int_distribution<std::uint64_t>* request_time_distribution_;
        std::uniform_int_distribution<std::int64_t>* request_cost_distribution_;
        std::optional<std::uint64_t> time_to_next_client = std::nullopt;

        std::optional<std::uint64_t> getTimeInterval();
    };
}