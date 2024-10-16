#include "../include/Banker.h"

#include <stdexcept>
#include <SFML/Graphics.hpp>

#include <iostream>

namespace bank
{
    Banker::Banker(bank_time::Time* global_time)
        : id_(getNextId()),
          global_time_(global_time)
    {
    }

    Banker::Banker(const Banker& other)
        : id_(other.id_),
          curr_client_(other.curr_client_.load()),
          global_time_(other.global_time_),
          work_thread_(other.work_thread_),
          is_working_(other.is_working_),
          salary_(other.salary_),
          last_synced_time_(other.last_synced_time_.load()),
          start_work_time_(other.start_work_time_)
    {
    }

    std::uint64_t Banker::getNextId()
    {
        static std::uint64_t last_banker_id = 0;

        return last_banker_id++;
    }

    void Banker::start()
    {
        if (salary_ != 0)
        {
            throw std::logic_error("The banker's salary is not zero at the time of starting work");
        }

        if (work_thread_ != nullptr)
        {
            throw std::logic_error("Banker is already working");
        }

        is_working_ = true;
        work_thread_ = new std::thread([=]()
        {
            last_synced_time_ = *global_time_;
            while (is_working_)
            {
                if (*global_time_ == last_synced_time_)
                {
                    sf::sleep(sf::milliseconds(10));

                    if (getClient())
                    {
                        if (start_work_time_ == nullptr)
                        {
                            start_work_time_ = new bank_time::Time(*global_time_);
                        } else
                        {
                            work_minutes_++;
                        }

                        if (
                            (*global_time_ - *start_work_time_).toMinutes() >= curr_client_.load()->request().time()
                        )
                        {
                            clients_served_number_++;
                            salary_ += curr_client_.load()->request().cost();

                            delete start_work_time_;
                            start_work_time_ = nullptr;

                            delete curr_client_;
                            curr_client_ = nullptr;
                        }
                    } else
                    {
                        downtime_minutes_++;
                    }
                    last_synced_time_ = last_synced_time_ + 1;
                }
            }
        });
    }

    void Banker::stop()
    {
        if (work_thread_ == nullptr)
        {
            throw std::logic_error("Banker is not working");
        }

        is_working_ = false;

        delete start_work_time_;
        start_work_time_ = nullptr;

        work_thread_->join();
        delete work_thread_;
        work_thread_ = nullptr;
    }

    std::int64_t Banker::getSalary()
    {
        const std::int64_t result_salary = salary_;

        salary_ = 0;

        return result_salary;
    }

    std::int32_t Banker::getClientsNumber()
    {
        const std::int32_t result_clients_number = clients_served_number_;

        clients_served_number_ = 0;

        return result_clients_number;
    }

    std::int32_t Banker::getWorkMinutes()
    {
        const std::int32_t result_work_minutes = work_minutes_;

        work_minutes_ = 0;

        return result_work_minutes;
    }

    std::int32_t Banker::getDowntimeMinutes()
    {
        const std::int32_t result_downtime_minutes = downtime_minutes_;

        downtime_minutes_ = 0;

        return result_downtime_minutes;
    }

    std::int32_t Banker::getClientsWaitingTime()
    {
        const std::int32_t result_clients_waiting_time = clients_waiting_time_;

        clients_waiting_time_ = 0;

        return result_clients_waiting_time;
    }

    void Banker::setClient(Client* client)
    {
        if (curr_client_ != nullptr)
        {
            throw std::logic_error("The banker is already busy");
        }
        clients_waiting_time_ += (*global_time_ - client->arrival_time()).toMinutes();
        curr_client_.store(client);
    }

    Client* Banker::getClient() const
    {
        return curr_client_.load();
    }
}
