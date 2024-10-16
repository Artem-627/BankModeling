#pragma once

#include "Banker.h"
#include "ClientsQueue.h"
#include "Primitives.h"
#include "Time.h"

#include <thread>
#include <cstdint>
#include <vector>

namespace bank
{
    class Bank
    {
    public:
        explicit Bank(std::uint16_t max_size, bank_time::Time* time, std::uint16_t bankers_number);

        [[nodiscard]]
        std::uint16_t bankers_number() const;

        [[nodiscard]]
        std::uint32_t lost_clients_number() const;

        [[nodiscard]]
        std::int64_t total_earn() const;

        [[nodiscard]]
        double new_client_probability() const;

        [[nodiscard]]
        std::uint16_t getCurrentQueueLength() const;

        void newClient(bank::Client* client);

        void ChangeNewClientProbability(double coefficient);

        [[nodiscard]]
        std::vector <const Client*> getAllClients() const;

        [[nodiscard]]
        std::vector <Banker*> getAllBankers();

        void start();

        void stop();

        void ChangeTotalEarn(std::int64_t change);

    private:
        ClientsQueue queue_;
        bank_time::Time* time_;
        std::uint16_t bankers_number_;
        std::vector<bank::Banker*> bankers_;
        std::int64_t total_earn_;
        double new_client_probability_;
        std::thread* queue_processing_thread_ = nullptr;
        bool is_queue_processing_ = false;
        std::uint32_t lost_clients_number_ = 0;

        void startQueueProcessing();

        void stopQueueProcessing();
    };
}
