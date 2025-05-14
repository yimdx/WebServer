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
    explicit ThreadPool(size_t max_thread_num = 1024);

    ~ThreadPool() = default;

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    // void init();
    void stop();

    template<typename F,typename... Args>
    auto submit(F&& f,Args&&... args)->std::future<decltype(f(args...))>{
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lk(_task_mutex);
            if (_stop) throw std::runtime_error("enqueue on stopped ThreadPool");
            _task_queue.emplace([task]() { (*task)(); });
        }
        _task_cond.notify_one();
        return res;
    };
    


private:   
    std::vector<std::thread> _thread_pool;
    std::queue<std::function<void()>> _task_queue;

    std::mutex _task_mutex;
    std::condition_variable _task_cond;

    bool _stop;
    size_t _thread_num;



};

}; //webs
