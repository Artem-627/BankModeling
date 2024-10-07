#pragma once

#include <cstdint>

namespace bank
{
    class Request
    {
    public:
        explicit Request(const std::uint64_t& time);

        [[nodiscard]]
        std::uint64_t id() const;

        [[nodiscard]]
        std::uint64_t time() const;

    private:
        std::uint64_t id_;
        std::uint64_t time_;

        static inline std::uint64_t getNextId();
    };


    class Client
    {
    public:
        Client();

        [[nodiscard]]
        std::uint64_t id() const;

        [[nodiscard]]
        Request request() const;

    private:
        std::uint64_t id_;
        Request* request_;

        static inline std::uint64_t getNextId();
    };
}
