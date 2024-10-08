#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cmath>

#include "include/Banker.h"

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

    std::vector <bank::Banker> bankers = {
        bank::Banker(&global_time),
        bank::Banker(&global_time)
    };

    bankers[0].start();
    bankers[1].start();

    std::thread bankers_monitor([&]()
    {
        while (true)
        {
            std::fstream file;
            file.open("test.txt", std::_S_app);
            file << "[" << static_cast<std::uint32_t>(global_time.weekDay()) << " | " <<
                static_cast<std::uint32_t>(global_time.hours()) << ":" <<
                static_cast<std::uint32_t>(global_time.minutes()) << "]\t\t\t";
            file << (bankers[0].getClient() == nullptr ? "null" : std::to_string(bankers[0].getClient()->id())) << "\t\t|\t\t";
            file << (bankers[1].getClient() == nullptr ? "null" : std::to_string(bankers[1].getClient()->id())) << "\n";
            sf::sleep(sf::milliseconds(100));
            file.close();
        }
    });

    char a;
    std::cin >> a;
    while (true)
    {
        if (a == 'q')
        {
            bankers[0].stop();
            bankers[1].stop();
            break;
        }
        if (a == 'n')
        {
            std::size_t banker_index;
            std::uint64_t time;
            std::int64_t cost;

            std::cout << "Banker index [0/1]: ";
            std::cin >> banker_index;
            std::cout << "Time: ";
            std::cin >> time;
            std::cout << "Cost: ";
            std::cin >> cost;

            try
            {
                auto new_client = new bank::Client(new bank::Request(time, cost));
                bankers[banker_index].setClient(new_client);

                std::cout << "--- New client ---" << '\n';
                std::cout << "Id: " << new_client->id() << '\n';
                std::cout << "Time: " << new_client->request().time() << '\n';
                std::cout << "Cost: " << new_client->request().cost() << '\n';
                std::cout << "------------------" << '\n';
            }
            catch (std::logic_error& error)
            {
                std::cout << "[ERROR] " << error.what() << '\n';
            }
        }

        std::cin >> a;
    }


    return 0;
}
