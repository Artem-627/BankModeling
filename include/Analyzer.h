#pragma once

#include <cstdint>
#include <vector>
#include <thread>
#include <atomic>

#include "Primitives.h"
#include "Time.h"
#include "Statistics.h"
#include "Bank.h"

namespace bank
{
    class Analyzer
    {
    public:
        Analyzer(bank_time::Time* global_time, bank::Bank* bank);

        void start();

        void stop();

        bank::Statistics getStatistics();
    private:
        std::vector<std::uint16_t> queue_lengths_;
        bank_time::Time* global_time_;
        bank::Bank* bank_;
        std::thread* collecting_statistics_thread_ = nullptr;
        bool is_statistics_collecting_ = false;
    };
}