#include "../include/ClientsQueue.h"
#include <stdexcept>

namespace bank
{
    ClientsQueue::ClientsQueue(std::uint16_t max_size)
        : max_size_(max_size), cur_size_(0)
    {
    }

    std::uint16_t ClientsQueue::max_size() const
    {
        return max_size_;
    }

    std::uint16_t ClientsQueue::cur_size() const
    {
        return cur_size_;
    }

    void ClientsQueue::newClient(bank::Client* client)
    {
        if (cur_size_ >= max_size_)
        {
            throw std::logic_error("queue is full");
        }

        cur_size_++;
        queue_.push(client);
    }

    bank::Client* ClientsQueue::getClient()
    {
        if (cur_size_ == 0)
        {
            throw std::logic_error("queue is empty");
        }

        cur_size_--;
        bank::Client* cur_client = queue_.front();
        queue_.pop();
        return cur_client;
    }

    std::vector<const bank::Client*> ClientsQueue::getAllClients() const
    {
        std::vector<const bank::Client*> clients;
        auto buffer_queue = queue_;
        while (!buffer_queue.empty())
        {
            clients.push_back(buffer_queue.front());
            buffer_queue.pop();
        }
        return clients;
    }
}
