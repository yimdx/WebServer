#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_
#endif

#include<thread>
#include<vector>
#include<queue>
#include<future>
#include<mutex>

namespace webs{

class ThreadPool{

public: 
    explicit ThreadPool(size_t max_thread_num = 1024)
        :_thread_pool(max_thread_num), _thread_num(max_thread_num)
    {
    };

    ~ThreadPool() = default;

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    // void init();
    void stop();

    template<typename F,typename... Args>
    auto submit(F&& f,Args&&... args)->std::future<decltype(f(args...))>{};
    


private:   
    std::vector<std::thread> _thread_pool;
    std::queue<std::function<void()>> _task_queue;

    std::mutex _task_mutex;
    std::condition_variable _task_cond;

    bool _stop;
    size_t _thread_num;



};

}; //webs
