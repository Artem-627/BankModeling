#pragma once

#include "../include/Analyzer.h"

#include <stdexcept>
#include <SFML/Graphics.hpp>

#include <iostream>

namespace bank
{
    Analyzer::Analyzer(bank_time::Time* global_time, bank::Bank* bank)
    : global_time_(global_time), bank_(bank)
    {
    }

    void Analyzer::start()
    {
        if (is_statistics_collecting_) {
            throw std::logic_error("Analyzer is already working");
        }

        is_statistics_collecting_ = true;
        collecting_statistics_thread_ = new std::thread([=, this]()
                {
                    while (is_statistics_collecting_)
                    {
                        queue_lengths_.push_back(bank_->getCurrentQueueLength());
                        sf::sleep(sf::milliseconds(10));
                    }
                });
    }

    void Analyzer::stop()
    {
        if (!is_statistics_collecting_) {
            throw std::logic_error("Statistics collecting is not started");
        }

        is_statistics_collecting_ = false;

        collecting_statistics_thread_->join();
        delete collecting_statistics_thread_;
        collecting_statistics_thread_ = nullptr;
    }

    bank::statistics Analyzer::getStatistics()
    {
        bank::statistics result{};
        for (auto banker : bank_->getAllBankers()) {
            result.clients_served_number_ += banker->getClientsNumber();
        }
        if (result.clients_served_number_ == 0) {
            throw std::logic_error("No data available");
        }

        result.lost_clients_number_ = bank_->lost_clients_number();
        result.lost_clients_percentage_ = static_cast<double>(result.lost_clients_number_) / (result.lost_clients_number_ + result.clients_served_number_);

        for (auto length : queue_lengths_) {
            result.average_queue_length_ += length;
        }
        if (queue_lengths_.empty()) {
            throw std::logic_error("No data available");
        } else {
            result.average_queue_length_ /= static_cast<double>(queue_lengths_.size());
        }

        for (auto banker : bank_->getAllBankers()) {
            result.average_queue_length_ += banker->getClientsWaitingTime();
        }
        result.average_waiting_time_ /= result.clients_served_number_;

        std::uint32_t summary_work_minutes = 0;
        std::uint32_t summary_downtime_minutes = 0;
        for (auto banker : bank_->getAllBankers()) {
            summary_work_minutes += banker->getWorkMinutes();
            summary_downtime_minutes += banker->getDowntimeMinutes();
        }
        if (summary_work_minutes == 0 && summary_downtime_minutes == 0) {
            throw std::logic_error("No data available");
        }
        result.average_banker_employment_ = static_cast<double>(summary_work_minutes) / (summary_work_minutes + summary_downtime_minutes);

        result.total_earn_ = bank_->total_earn();

        return result;
    }
}