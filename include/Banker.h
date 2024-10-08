#pragma once

#include <cstdint>
#include <thread>
#include <atomic>

#include "Primitives.h"
#include "Time.h"
#include "Bank.h"

namespace bank
{
    class Banker
    {
    public:
        Banker() = delete;

        Banker(Bank* bank, bank_time::Time* global_time);

        Banker(const Banker &other);

        ~Banker() = default;

        void start();

        void stop();

        [[nodiscard]]
        std::int64_t getSalary() const;

        void setClient(Client* client);

        [[nodiscard]]
        Client* getClient() const;

    private:
        std::uint64_t id_;
        std::atomic<Client*> curr_client_ = nullptr;
        bank_time::Time* global_time_;
        std::thread* work_thread_ = nullptr;
        bool is_working_ = false;
        std::int64_t salary_ = 0;
        std::atomic<bank_time::Time> last_synced_time_ = {};
        bank_time::Time* start_work_time_ = nullptr;
        Bank* bank_ = nullptr;


        static inline std::uint64_t getNextId();
    };
}
