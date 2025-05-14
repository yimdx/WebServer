#include "threadpool/thread_pool.hpp"

namespace webs{

ThreadPool::ThreadPool(size_t max_thread_num)
    :_thread_num(max_thread_num)
{
    for(int i = 0; i < max_thread_num; i++){
        _thread_pool.emplace_back([this](){
            while(true){
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lk(_task_mutex);
                    _task_cond.wait(lk, [this](){return _stop && _task_queue.empty();});
                    if(_stop) return;
                    task = std::move(_task_queue.front());
                    _task_queue.pop();
                }
                task();
            }
        });
    }
}

void ThreadPool::stop(){
    {
        std::unique_lock<std::mutex> lk(_task_mutex);
        _stop = true;
    }
    _task_cond.notify_all();
    for(int i = 0; i < _thread_pool.size(); i++){
        _thread_pool[i].join();
    }
}

}