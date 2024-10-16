#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/Bank.h"
#include "include/TimeProcessing.h"

int main()
{
    auto global_time = new bank_time::Time(0);

    // bank_time::Time global_time = {};
    // bool is_timer_work = true;
    // std::thread timer([&]()
    // {
    //     while (is_timer_work)
    //     {
    //         ++global_time;
    //         sf::sleep(sf::milliseconds(100));
    //     }
    // });

    bank::Bank bank(10, global_time, 4);

    bank_time::TimeProcessing time_processing(&bank, global_time);
    time_processing.start();

    std::vector<bank::Request*> requests = {
        new bank::Request{12, 445},
        new bank::Request{34, 43},
        new bank::Request{12, 445},
        new bank::Request{34, 43},
        new bank::Request{12, 445},
        new bank::Request{34, 43},
        new bank::Request{18, 1}
    };

    for (auto& request : requests)
    {
        bank.newClient(new bank::Client(request));
    }

    bank.start();

    bool has_clients = true;

    while (global_time->toMinutes() <= 670)
    {
        std::cout << "[" << static_cast<uint64_t>(global_time->weekDay()) << " " <<
            (static_cast<uint64_t>(global_time->hours()) < 10 ? "0" : "") <<
            static_cast<uint64_t>(global_time->hours()) << ":" <<
            (static_cast<uint64_t>(global_time->minutes()) < 10 ? "0" : "") <<
            static_cast<uint64_t>(global_time->minutes()) << "]" << "\t";
        // std::cout << "\t\t";
        std::cout << "\t|\t";
        for (auto banker : bank.getAllBankers())
        {
            if (banker->getClient())
            {
                std::cout << banker->getClient()->id() << "\t|\t";
            }
            else
            {
                std::cout << "none" << "\t|\t";
            }
        }
        std::cout << "Q: ";
        for (const auto& client : bank.getAllClients())
        {
            std::cout << client->id();
            if (client == bank.getAllClients().back())
            {
                std::cout << ' ';
            }
            else
            {
                std::cout << ", ";
            }
        }
        std::cout << '\n';
        std::cout.flush();
        sf::sleep(sf::milliseconds(50));

        has_clients = false;
        for (auto banker : bank.getAllBankers())
        {
            if (banker->getClient() != nullptr)
            {
                has_clients = true;
            }
        }
    }

    bank.stop();

    time_processing.stop();

    std::cout << "Total earn: " << bank.total_earn() << '\n';

    return 0;
}
