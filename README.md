C++ In Memory Scheduler :

Handles two kind of calls:
- Direct Event : scheduleAt( std::chrono::time_point, std::function<void()> )
- Recurring Event : scheduleEvery( std::chrono::duration, std::function<void()> )

Task is implemented using function wrapper of void, one can simply encapsulate
code and use.

main.cpp contains an example with 4 task schedulings :
F1 : start once after 5 seconds & run for 10 seconds  
F2 : Start every 3 seconds and each time run for 1 sec 
F3 : Start every 10 seconds and run for 1 second
F4 : Start once after 10 seconds & run for 1 sec

They should display the result for 20 seconds, sample result :
Scheduler started Fri Dec  4 18:29:54 2020

F2.1 Fri Dec  4 18:29:57 2020

F2.2 Fri Dec  4 18:29:58 2020

F1.1 Fri Dec  4 18:29:59 2020

F2.1 Fri Dec  4 18:30:00 2020

F2.2 Fri Dec  4 18:30:01 2020

F2.1 Fri Dec  4 18:30:03 2020

F3.1 Fri Dec  4 18:30:04 2020

F4.1 Fri Dec  4 18:30:04 2020

F2.2 Fri Dec  4 18:30:04 2020

F3.2 Fri Dec  4 18:30:05 2020

F4.2 Fri Dec  4 18:30:05 2020

F2.1 Fri Dec  4 18:30:06 2020

F2.2 Fri Dec  4 18:30:07 2020

F1.2 Fri Dec  4 18:30:09 2020

F2.1 Fri Dec  4 18:30:09 2020

F2.2 Fri Dec  4 18:30:10 2020

F2.1 Fri Dec  4 18:30:12 2020

F2.2 Fri Dec  4 18:30:13 2020


Credits :
The implementation is a result of following : 

https://codereview.stackexchange.com/questions/21336/c-task-scheduler

Compilation command: 

g++ -std=c++17 main.cpp
Using g++: g++ -v
Using built-in specs.
COLLECT_GCC=g++-6.3.0
COLLECT_LTO_WRAPPER=/usr/local/gcc-6.3.0/libexec/gcc/x86_64-apple-darwin19.6.0/6.3.0/lto-wrapper
Target: x86_64-apple-darwin19.6.0
Configured with: ../configure --prefix=/usr/local/gcc-6.3.0 --enable-checking=release --with-gmp=/usr/local/gcc-6.3.0 --with-mpfr=/usr/local/gcc-6.3.0 --with-mpc=/usr/local/gcc-6.3.0 --enable-languages=c,c++,fortran --with-isl=/usr/local/gcc-6.3.0 --program-suffix=-6.3.0 --with-native-system-header-dir=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include : (reconfigured) ../configure --build=x86_64-apple-darwin19.6.0 --prefix=/usr/local/gcc-6.3.0 --enable-checking=release --disable-nls --with-gmp=/usr/local/gcc-6.3.0 --with-mpfr=/usr/local/gcc-6.3.0 --with-mpc=/usr/local/gcc-6.3.0 --enable-languages=c,c++,fortran --with-isl=/usr/local/gcc-6.3.0 --with-system-zlib --disable-multilib --program-suffix=-6.3.0 --with-native-system-header-dir=/usr/include --with-sysroot=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk SED=/usr/bin/sed
Thread model: posix
gcc version 6.3.0 (GCC) 

