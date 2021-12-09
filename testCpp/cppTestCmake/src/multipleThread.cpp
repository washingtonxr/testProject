#include "multipleThread.h"
#include <iostream>
#include <thread>
#include <chrono>
//#include <string>
#include <numeric>
#include <mutex>
#include <atomic>

#include <stdio.h>
//#include <stdio.h>
//#include <unistd.h>
std::mutex mutexLock;
std::atomic<unsigned int> atomicCounter(0);
std::recursive_mutex recrusiveMutexLock;
unsigned int ulCommonValue = 0;

static void tryLockCallback(void) {
    int ulCounter = 0;
    while (1) {
        if (mutexLock.try_lock()) {
            printf("ulCommonValue = %d.\n", ulCommonValue);
            //recrusiveMutexLock.lock();
            ulCommonValue++;
            mutexLock.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (5 <= ulCounter++) {
                return;
            }
        }
    }
    return;
}

static void recursiveMutexCallback(void) {
    int ulCounter = 0;
    while (true) {
        printf("ulCommonValue = %d.\n", ulCommonValue);
        recrusiveMutexLock.lock();
        ulCommonValue++;
        recrusiveMutexLock.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (5 <= ulCounter++) {
            return;
        }
    }
    return;
}

static void atomicCallback(void) {
    int ulCounter = 0;
    while (true) {
        atomicCounter++;
        printf("atomicCounter = %d.\n", atomicCounter.load());
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (5 <= ulCounter++) {
            return;
        }
    }
    return;
}

static void lockTask(void) {
    int ulCounter = 0;
    while (true) {
        std::cout << "This is a lock thread for testing(" << ulCounter << ")." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        mutexLock.lock();
        ulCounter++;
        mutexLock.unlock();
        if (5 <= ulCounter) {
            return;
        }
    }
    return;
}

static void detachTask(void) {
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

static void justATask(void) {
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

    std::thread subTask3(lockTask);
    std::thread subTask4(lockTask);
    std::thread subTask5(lockTask);
    std::thread subTask6(lockTask);

    subTask3.join();
    subTask4.join();
    subTask5.join();
    subTask6.join();

    std::thread atomicTask1(atomicCallback);
    std::thread atomicTask2(atomicCallback);
    std::thread atomicTask3(atomicCallback);
    std::thread atomicTask4(atomicCallback);
    atomicTask1.join();
    atomicTask2.join();
    atomicTask3.join();
    atomicTask4.join();

    std::thread recrusiveMutexTask1(recursiveMutexCallback);
    std::thread recrusiveMutexTask2(recursiveMutexCallback);
    std::thread recrusiveMutexTask3(recursiveMutexCallback);
    std::thread recrusiveMutexTask4(recursiveMutexCallback);
    recrusiveMutexTask1.join();
    recrusiveMutexTask2.join();
    recrusiveMutexTask3.join();
    recrusiveMutexTask4.join();

    std::thread tryLockTask1(tryLockCallback);
    std::thread tryLockTask2(tryLockCallback);
    std::thread tryLockTask3(tryLockCallback);
    std::thread tryLockTask4(tryLockCallback);
    tryLockTask1.join();
    tryLockTask2.join();
    tryLockTask3.join();
    tryLockTask4.join();

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
