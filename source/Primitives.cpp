#include "../include/Primitives.h"

namespace bank
{
    // Request
    inline std::uint64_t Request::getNextId()
    {
        static std::uint64_t last_request_id = 0;
        return last_request_id++;
    }

    Request::Request(const std::uint64_t& time, const std::int64_t& cost)
        : id_(getNextId()), time_(time), cost_(cost)
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

    std::int64_t Request::cost() const
    {
        return cost_;
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

    Client::Client(Request* request, bank_time::Time arrival_time_)
        : id_(getNextId()), request_(request), arrival_time_(arrival_time_)
    {
    }

    Client::~Client()
    {
        delete request_;
        request_ = nullptr;
    }

    std::uint64_t Client::id() const
    {
        return id_;
    }

    Request Client::request() const
    {
        return *request_;
    }

    bank_time::Time Client::arrival_time() const
    {
        return arrival_time_;
    }
}
