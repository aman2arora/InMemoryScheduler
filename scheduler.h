#pragma once
#include <mutex>
#include <queue>
#include <thread>
#include <condition_variable>
#include "task.h"

namespace sched {

struct strcomp{
    bool operator() (const Task& a, const Task& b)
    {
        return a.getTime() > b.getTime();
    }
};


class Scheduler 
{
private:
    bool m_active;
    std::unique_ptr<std::thread> m_thread;

    std::mutex m;
    std::condition_variable cv;
    
    std::priority_queue<Task, std::vector<Task>, strcomp> m_taskq;

public:
    // Run mainloop in separate thread
    Scheduler() : m_active(true), m_thread(new std::thread([this]() { mainloop(); }))
    {
    }

    // Non copyable
    Scheduler(const Scheduler& rhs)=delete;
    Scheduler& operator=(const Scheduler& rhs)=delete;

    void stop() {
        m_active=false;
    }

    ~Scheduler(){
        stop();
        m_thread->join();
    }
    
    void mainloop() 
    {
        while (m_active)
        {
            Task task;
            {
                std::unique_lock<std::mutex> lk(m);
                // Using timeout is useful because in case when we found that
                // Next Task's Time still had some time, we will go into
                // waiting
                // To come out of waiting we need some timeout.
                // If some other task is pushed it would wake us to check, but
                // in case there is no activity on Q we need to check in
                // timeouts
                auto ret=cv.wait_for(lk, std::chrono::milliseconds(100), [&](){
                        return (!m_active || (!m_taskq.empty() && std::chrono::system_clock::now() >= m_taskq.top().getTime()));
                        });

                if (!ret) continue; // timeout, check again
                
                if (!m_active) break;

                task=m_taskq.top();
                m_taskq.pop();
            }   // lock goes out of scope
            task.execute(); // task executes without lock on Scheduler's taskQ
        }
    }

    void scheduleAt(const std::chrono::system_clock::time_point& p, std::function<void()>&& f)
    {
        std::function<void()> tfunc=[f](){
            std::thread tempThread(f);
            tempThread.detach();
        };
        {
            std::unique_lock<std::mutex> lk(m);
            m_taskq.emplace(std::move(tfunc), p);
        }
        cv.notify_one();
    }

    void scheduleEvery(const std::chrono::system_clock::duration& d, std::function<void()> f)
    {
        std::function<void()> tfunc=[this, f, d](){
            std::thread tempThread(f);
            tempThread.detach();

            scheduleEvery(d, f); // Recurring call
        };
        {
            std::unique_lock<std::mutex> lk(m);
            m_taskq.emplace(std::move(tfunc), std::chrono::system_clock::now()+d);
        }
        cv.notify_one();
    }

};

}
