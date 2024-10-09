#include "../include/ClientsQueue.h"
#include "../include/Bank.h"

#include <stdexcept>
#include <queue>
#include <cstdint>
#include <SFML/Graphics.hpp>

namespace bank
{
    Bank::Bank(std::uint16_t max_size, bank_time::Time *time, std::uint16_t bankers_number)
        : queue_(ClientsQueue(max_size)), time_(time), bankers_number_(bankers_number), total_earn_(0),
            new_client_probability_(1.0)
    {
        bankers_.resize(bankers_number);
        for (int i = 0; i < bankers_number; i++)
        {
            bankers_[i] = new Banker(time_);
        }
    }

    std::uint16_t Bank::bankers_number() const
    {
        return bankers_number_;
    }

    std::uint32_t Bank::lost_clients_number() const
    {
        return lost_clients_number_;
    }

    std::int64_t Bank::total_earn() const
    {
        return total_earn_;
    }

    double Bank::new_client_probability() const
    {
        return new_client_probability_;
    }

    std::uint16_t Bank::getCurrentQueueLength() const
    {
        return queue_.cur_size();
    }

    void Bank::newClient(bank::Client *client)
    {
        try {
            queue_.newClient(client);
        } catch (const char *error_message) {
            lost_clients_number_++;
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

    std::vector <const bank::Client *> Bank::getAllClients() const
    {
        return queue_.getAllClients();
    }

    std::vector <bank::Banker *> Bank::getAllBankers()
    {
        std::vector <bank::Banker *> result;
        for (const auto& banker : bankers_)
        {
            result.push_back(banker);
        }
        return result;
    }

    void Bank::start()
    {
        for (auto &banker : bankers_)
        {
            banker->start();
        }

        startQueueProcessing();
    }

    void Bank::stop()
    {
        for (const auto &banker : bankers_)
        {
            total_earn_ += banker->getSalary();
            banker->stop();
        }

        stopQueueProcessing();
    }

    void Bank::startQueueProcessing()
    {
        if (is_queue_processing_)
        {
            throw std::logic_error("Queue processing is already started");
        }

        is_queue_processing_ = true;
        queue_processing_thread_ = new std::thread([=]()
        {
            while (is_queue_processing_)
            {
                if (queue_.cur_size() > 0)
                {
                    for (auto &banker : bankers_)
                    {
                        if (banker->getClient() == nullptr)
                        {
                            banker->setClient(queue_.getClient());
                        }
                    }
                }
                sf::sleep(sf::milliseconds(10));
            }
        });
    }

    void Bank::stopQueueProcessing()
    {
        if (!is_queue_processing_)
        {
            throw std::logic_error("Queue processing is not started");
        }

        is_queue_processing_ = false;

        queue_processing_thread_->join();
        delete queue_processing_thread_;
        queue_processing_thread_ = nullptr;
    }
}
