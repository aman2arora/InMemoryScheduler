#include "scheduler.h"

using namespace sched;

void TaskNsec(int N)
{
  std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
  while (std::chrono::system_clock::now()<(p+std::chrono::seconds(N))){}
}

int main() {
  Scheduler s;
  std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
  std::time_t t = std::chrono::system_clock::to_time_t(p);
  std::cout << "Scheduler started " << std::ctime(&t) << std::endl;

  // Simple case: start once after 5 seconds & run for 10 seconds
  s.scheduleAt(std::chrono::system_clock::now() + std::chrono::seconds(5), [] {
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(p);
    std::cout << "F1.1 " << std::ctime(&t) << std::endl;

    TaskNsec(10);

    std::chrono::system_clock::time_point p2 = std::chrono::system_clock::now();
    std::time_t t2 = std::chrono::system_clock::to_time_t(p2);
    std::cout << "F1.2 " << std::ctime(&t2) << std::endl;
  });
  
  // Start every 3 seconds and each time run for 1 sec
  s.scheduleEvery(std::chrono::seconds(3), [] {
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(p);
    std::cout << "F2.1 " << std::ctime(&t) << std::endl;

    TaskNsec(1);

    std::chrono::system_clock::time_point p2 = std::chrono::system_clock::now();
    std::time_t t2 = std::chrono::system_clock::to_time_t(p2);
    std::cout << "F2.2 " << std::ctime(&t2) << std::endl;
  });
  
  // Start every 10 seconds and run for 1 second
  s.scheduleEvery(std::chrono::seconds(10), [] {
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(p);
    std::cout << "F3.1 " << std::ctime(&t) << std::endl;

    TaskNsec(1);

    std::chrono::system_clock::time_point p2 = std::chrono::system_clock::now();
    std::time_t t2 = std::chrono::system_clock::to_time_t(p2);
    std::cout << "F3.2 " << std::ctime(&t2) << std::endl;
  });
  
  // Start once after 10 seconds & run for 1 sec
  s.scheduleAt(std::chrono::system_clock::now() + std::chrono::seconds(10), [] {
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(p);
    std::cout << "F4.1 " << std::ctime(&t) << std::endl;

    TaskNsec(1);

    std::chrono::system_clock::time_point p2 = std::chrono::system_clock::now();
    std::time_t t2 = std::chrono::system_clock::to_time_t(p2);
    std::cout << "F4.2 " << std::ctime(&t2) << std::endl;
  });

  // wait 20 seconds for result, then end
  TaskNsec(20);
  s.stop();
}
