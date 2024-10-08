#include "../include/Banker.h"

#include <stdexcept>
#include <SFML/Graphics.hpp>

#include <iostream>

namespace bank
{
    Banker::Banker(Bank* bank, bank_time::Time* global_time)
        : id_(getNextId()),
          global_time_(global_time),
          bank_(bank)
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
          start_work_time_(other.start_work_time_),
          bank_(other.bank_)
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
                        }

                        if (
                            (*global_time_ - *start_work_time_).toMinutes() >= curr_client_.load()->request().time()
                        )
                        {
                            salary_ += curr_client_.load()->request().cost();

                            delete start_work_time_;
                            start_work_time_ = nullptr;

                            curr_client_ = nullptr;
                        }
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

        bank_->ChangeTotalEarn(salary_);
        salary_ = 0;

        is_working_ = false;

        delete start_work_time_;
        start_work_time_ = nullptr;

        work_thread_->join();
        delete work_thread_;
        work_thread_ = nullptr;
    }

    std::int64_t Banker::getSalary() const
    {
        return salary_;
    }

    void Banker::setClient(Client* client)
    {
        if (curr_client_ != nullptr)
        {
            throw std::logic_error("The banker is already busy");
        }
        curr_client_.store(client);
    }

    Client* Banker::getClient() const
    {
        return curr_client_.load();
    }
}
