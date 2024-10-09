#include <cstdint>

struct statistics {
public:
    std::uint32_t clients_served_number_;
    std::uint32_t lost_clients_number_;
    double lost_clients_percentage_;
    double average_queue_length_;
    double average_waiting_time_;
    double average_banker_employment_;
    std::int64_t total_earn_;
};