#include <cstdint>

namespace bank
{
    struct statistics
    {
    public:
        std::uint32_t clients_served_number_ = 0;
        std::uint32_t lost_clients_number_ = 0;
        double lost_clients_percentage_ = 0;
        double average_queue_length_ = 0 ;
        double average_waiting_time_ = 0;
        double average_banker_employment_ = 0;
        std::int64_t total_earn_ = 0;
    };
}