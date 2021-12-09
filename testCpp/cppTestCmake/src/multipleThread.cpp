#include "multipleThread.h"
#include <iostream>
#include <thread>
#include <chrono>
//#include <string>
#include <numeric>

//#include <stdio.h>
//#include <unistd.h>
void detachTask(void) {
    int ulCounter = 0;
    while (true) {
        //std::string s(1, ucCounter);
        //std::cout << s << std::endl;
        std::cout << "This is a deamon thread for testing(" << ulCounter << ")." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (3 <= ulCounter++) {
            return;
        }
    }
}

void justATask(void) {
    std::cout << "This is a sub-task for testing." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "I am done!" << std::endl;
}

int testMultiThread(void) {
    /* Multiple threads test. */
    std::thread subTask1(justATask);
    //subTask = std::thread(justATask);
    std::cout << "This thread is joinable? " << subTask1.joinable() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    subTask1.join();

    std::thread subTask2(detachTask);
    std::cout << "This thread is joinable? " << subTask2.joinable() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    subTask2.join();

    return 0;
}

#if 0
// a simple function that wastes CPU cycles "forever"
static void cpu_waster(void) {
    printf("CPU Waster Process ID: %d\n", getpid());
    printf("CPU Waster Thread ID %d\n", std::this_thread::get_id());
    while(true) continue;
}

int testCPUTester(void) {
    printf("Main Process ID: %d\n", getpid());
    printf("Main Thread ID: %d\n", std::this_thread::get_id());
    std::thread thread1(cpu_waster);
    std::thread thread2(cpu_waster); 

    while(true) { // keep the main thread alive "forever"
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
#endif

/* End of this file. */