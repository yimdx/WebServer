#ifndef _EPOLLER_H_
#define _EPOLLER_H_
#endif

#include <sys/epoll.h>
#include <vector>

namespace webs{

class Epoller{

public:
    explicit Epoller(int max_link = 1024)
        :_events(max_link)
    {
    };
    ~Epoller() = default;

    bool add_fd(int fd, uint32_t event);
    bool del_fd(int fd, uint32_t event);
    bool mod_fd(int fd, uint32_t event);

    // ms
    int wait(int timeout = -1);
    int get_fd(size_t idx) const;
    uint32_t get_event_fd(size_t idx) const;
private:
    size_t _epoll_fd;
    std::vector<struct epoll_event> _events;
};

}//webs