
#include "../include/Primitives.h"
#include "../include/Time.h"
#include "../include/ClientsQueue.h"
#include "../include/Bank.h"
#include <stdexcept>
#include <queue>
#include <cstdint>

Bank::Bank(std::uint16_t max_size, bank_time::Time* time, std::uint16_t bankers_number)
: queue_(*new ClientsQueue(max_size)), time_(time), bankers_number_(bankers_number), total_earn_(0), new_client_probability_(1.0)
{
}

std::uint16_t Bank::bankers_number() const
{
    return bankers_number_;
}

std::int64_t Bank::total_earn() const
{
    return total_earn_;
}

double Bank::new_client_probability() const
{
    return new_client_probability_;
}

void Bank::newClient(bank::Client *client)
{
    try {
        queue_.newClient(client);
    } catch (const char* error_message) {
        throw std::runtime_error(error_message);
    }
}

void Bank::ChangeNewClientProbability(double coefficient)
{
    new_client_probability_ *= coefficient;
}

void Bank::ChangeTotalEarn(std::int64_t change)
{
    total_earn_ += change;
}

