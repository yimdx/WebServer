#ifndef _TIMER_H_
#define _TIMER_H_
#endif

#include<chrono>
#include <functional>

namespace webs{

class Timer{

public:
    Timer(int id, uint64_t expire, std::function<void()> call_back);
    ~Timer() = default;

    void reset_expire(uint64_t expire);
    void activate();
    uint64_t get_expire() const;
    int get_id() const;


private:
    int _id;
    uint64_t _expire;
    std::function<void()> _call_back;
};
}; // webs
