#include "timer/timer.hpp"

namespace webs{

Timer::Timer(int id, uint64_t expire, std::function<void()> call_back)
    :_id(id), _expire(expire), _call_back(call_back)
{
}

void Timer::reset_expire(uint64_t expire){
    _expire = expire;
}

void Timer::activate(){
    _call_back();
}

uint64_t Timer::get_expire() const{
    return _expire;
}

int Timer::get_id() const{
    return _id;
};

}