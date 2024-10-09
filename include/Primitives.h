#pragma once

#include "Time.h"
#include <cstdint>

namespace bank
{
    class Request
    {
    public:
        explicit Request(const std::uint64_t& time, const std::int64_t& cost);

        [[nodiscard]]
        std::uint64_t id() const;

        [[nodiscard]]
        std::uint64_t time() const;

        [[nodiscard]]
        std::int64_t cost() const;

    private:
        std::uint64_t id_;
        std::uint64_t time_;
        std::int64_t cost_;

        static inline std::uint64_t getNextId();
    };


    class Client
    {
    public:
        Client();

        explicit Client(Request* request, bank_time::Time arrival_time);

        ~Client();

        [[nodiscard]]
        std::uint64_t id() const;

        [[nodiscard]]
        Request request() const;

        [[nodiscard]]
        bank_time::Time arrival_time() const;

    private:
        std::uint64_t id_;
        Request* request_;
        bank_time::Time arrival_time_{};

        static inline std::uint64_t getNextId();
    };
}
