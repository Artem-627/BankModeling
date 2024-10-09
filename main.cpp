#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/Bank.h"

int main()
{
    bank_time::Time global_time = {};
    std::thread timer([&]()
    {
        while (true)
        {
            ++global_time;
            sf::sleep(sf::milliseconds(100));
        }
    });


    bank::Bank bank(10, &global_time, 3);

    std::vector<bank::Request*> requests = {
        new bank::Request{12, 54},
        new bank::Request{34, 33},
        new bank::Request{44, 4},
        new bank::Request{37, 4},
        new bank::Request{27, 4},
        new bank::Request{57, 4},
        new bank::Request{7, 4},
        new bank::Request{18, 43}
    };

    for (auto& request : requests)
    {
        bank.newClient(new bank::Client(request));
    }

    bank.start();


    while (true)
    {
        std::cout.clear();
        std::cout << "[" << static_cast<uint64_t>(global_time.weekDay()) << " " <<
            (static_cast<uint64_t>(global_time.hours()) < 10 ? "0" : "") <<
            static_cast<uint64_t>(global_time.hours()) << ":" <<
            (static_cast<uint64_t>(global_time.minutes()) < 10 ? "0" : "") <<
            static_cast<uint64_t>(global_time.minutes()) << "]" << "\t";
        std::cout << "\t\t";
        std::cout << "\t|\t";
        for (auto banker : bank.getAllBankers())
        {
            if (banker->getClient())
            {
                std::cout << banker->getClient()->id() << "\t|\t";
            }
            else
            {
                std::cout << "null" << "\t|\t";
            }
        }
        std::cout << "Queue: ";
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
        sf::sleep(sf::milliseconds(50));
    }


    return 0;
}
