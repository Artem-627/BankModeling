#pragma once

#include "../include/Primitives.h"
#include <queue>
#include <cstdint>

class ClientsQueue {
public:
    explicit ClientsQueue(std::uint16_t max_size);

    [[nodiscard]]
    std::uint16_t max_size() const;

    [[nodiscard]]
    std::uint16_t cur_size() const;

    void newClient(bank::Client* client);
    bank::Client* getClient();

private:
    std::queue<bank::Client*> queue_;
    std::uint16_t max_size_;
    std::uint16_t cur_size_;
};
