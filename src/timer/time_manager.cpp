#include "timer/time_manager.hpp"

namespace webs{

TimerManager::TimerManager(){
    _default_timeout = 2000;
}   

void TimerManager::add_timer(int id, uint64_t timeout, std::function<void()> call_back){
    auto new_timer = std::make_shared<Timer>(id, get_current_ms()+timeout, call_back);
    _timer_queue.push(new_timer);
    _id2timer[id] = new_timer;
}

void TimerManager::update_timer(int id, uint64_t timeout, std::function<void()> call_back = nullptr){
    add_timer(id, timeout, call_back);
}

uint64_t TimerManager::get_next_timeout(){
    uint64_t result = _default_timeout;
    auto curr_time = get_current_ms();
    while(!_timer_queue.empty()){
        // skip all old Timer;
        auto curr_timer = _timer_queue.top();
        if(_id2timer.at(curr_timer->get_id()) == curr_timer){
            result = curr_timer->get_expire() - get_current_ms();
            break;
        };
        _timer_queue.pop();
    }
    return result;
}

void TimerManager::tick(){
    auto curr_time = get_current_ms();
    while(!_timer_queue.empty()){
        auto curr_timer = _timer_queue.top();

        // if curr timer is not expired, stop loop;
        if(curr_timer->get_expire() > curr_time) break;
        
        // if curr timer is newest, execute call back;
        if(_id2timer.at(curr_timer->get_id()) == curr_timer) curr_timer->activate();
        _timer_queue.pop();
        _id2timer.erase(curr_timer->get_id());
    }
};


}