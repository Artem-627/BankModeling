#pragma once

#include "../include/Primitives.h"
#include "../include/Time.h"
#include "../include/ClientsQueue.h"
#include <queue>
#include <cstdint>

class Bank {
public:
    explicit Bank(std::uint16_t max_size, bank_time::Time* time, std::uint16_t bankers_number);

    [[nodiscard]]
    std::uint16_t bankers_number() const;

    [[nodiscard]]
    std::int64_t total_earn() const;

    [[nodiscard]]
    double new_client_probability() const;

    void newClient(bank::Client* client);
    void ChangeNewClientProbability(double coefficient);
    void ChangeTotalEarn(std::int64_t change);

private:
    ClientsQueue queue_;
    bank_time::Time* time_;
    std::uint16_t bankers_number_;
    // vector of Bankers
    std::int64_t total_earn_;
    double new_client_probability_;
};
