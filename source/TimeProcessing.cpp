#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include <iostream>

#include "../include/TimeProcessing.h"

namespace bank_time
{
    TimeProcessing::TimeProcessing(bank::Bank* bank, Time* const & global_time)
        : global_time_(global_time),
          bank_(bank),
          time_interval_distribution_(new std::normal_distribution{kNormalDistrubutionMean, kNormalDistrubutionStddev}),
          request_time_distribution_(
              new std::uniform_int_distribution<std::uint64_t>(kMinRequestTime, kMaxRequestTime)
          ),
          request_cost_distribution_(
              new std::uniform_int_distribution<std::int64_t>(kMinRequestCost, kMaxRequestCost)
          )
    {
    }

    TimeProcessing::~TimeProcessing()
    {
        delete time_interval_distribution_;
        delete time_processing_thread_;
    }

    void TimeProcessing::start()
    {
        if (is_time_processing_work_)
        {
            throw std::logic_error("Time processing is already started");
        }


        is_time_processing_work_ = true;
        time_processing_thread_ = new std::thread([=]()
        {
            while (is_time_processing_work_)
            {
                ++(*global_time_);

                if (!time_to_next_client.has_value())
                {
                    time_to_next_client = getTimeInterval();
                    // std::cout << "[Interval\t\t" << time_to_next_client.value() << "]\t\t\t";
                }
                if (time_to_next_client > 0)
                {
                    --time_to_next_client.value();
                }
                else
                {
                    std::uint64_t request_time = request_time_distribution_->operator()(gen);
                    std::int64_t request_cost = request_cost_distribution_->operator()(gen);

                    const auto new_request = new bank::Request(request_time, request_cost);
                    const auto new_client = new bank::Client(new_request);

                    try
                    {
                        bank_->newClient(new_client);

                        time_to_next_client = std::nullopt;
                    }
                    catch (const std::logic_error &e)
                    {
                        std::cout << "[Клиент не поместился в банк блять]" << '\n';
                    }
                }

                sf::sleep(sf::milliseconds(kModellingSpeed));
            }
        });
    }

    void TimeProcessing::stop()
    {
        if (!is_time_processing_work_)
        {
            throw std::logic_error("Time processing is not started yet");
        }

        is_time_processing_work_ = false;
        time_processing_thread_->join();
        delete time_processing_thread_;
        time_processing_thread_ = nullptr;
    }

    std::optional<std::uint64_t> TimeProcessing::getTimeInterval()
    {
        if (random_probability_(gen) >= bank_->new_client_probability())
        {
            return std::nullopt;
        }

        return time_interval_distribution_->operator()(gen);
    }
}
