#pragma once

#include <iostream>
#include <functional>
#include <chrono>

namespace sched{

class Task {
private:
    std::function<void()> func;
    std::chrono::system_clock::time_point time;
public:
    Task() {}
    Task(std::function<void()>&& f, const std::chrono::system_clock::time_point& t): func(f), time(t) {}
    void execute() {
        func();
    }
    std::chrono::system_clock::time_point getTime() const {
        return time;
    }
};

}
