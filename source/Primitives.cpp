#include "../include/Primitives.h"

namespace bank
{
    // Request
    inline std::uint64_t Request::getNextId()
    {
        static std::uint64_t last_request_id = 0;
        return last_request_id++;
    }

    Request::Request(const std::uint64_t &time)
        : id_(getNextId()), time_(time)
    {
    }

    std::uint64_t Request::id() const
    {
        return id_;
    }

    std::uint64_t Request::time() const
    {
        return time_;
    }


    // Client
    inline std::uint64_t Client::getNextId()
    {
        static std::uint64_t last_client_id = 0;
        return last_client_id++;
    }

    Client::Client()
        : id_(getNextId()), request_(nullptr)
    {
    }

    std::uint64_t Client::id() const
    {
        return id_;
    }

    Request Client::request() const
    {
        return *request_;
    }
}