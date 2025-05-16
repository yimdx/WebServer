#ifndef _TIMER_MANAGER_H_
#define _TIMER_MANAGER_H_
#endif

#include <chrono>
#include <functional>
#include <queue>
#include "timer.hpp"
namespace webs{

class TimerManager{
    using TimerPtr = std::shared_ptr<Timer>;
    
public:
    TimerManager();
    ~TimerManager() = default;

    void add_timer(int id, uint64_t timeout_ms, std::function<void()> call_back);
    void update_timer(int id, uint64_t timeout_ms, std::function<void()> call_back);
    void tick();
    uint64_t get_next_timeout();

private:
    static uint64_t get_current_ms(){
        auto timestamp = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch()).count();
    };

    struct cmp{
        bool operator()(const TimerPtr& left, const TimerPtr& right){
            return left->get_expire() < right->get_expire();
        }
    };

    std::priority_queue<TimerPtr, std::vector<TimerPtr>, cmp> _timer_queue;
    std::unordered_map<int, TimerPtr> _id2timer;
    uint64_t _default_timeout;
};
}; // webs

