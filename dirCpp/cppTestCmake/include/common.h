#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
// #include <cstdio>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

// Use (void) to silence unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))

#include <unistd.h>

#define _Assert_Exit_                                                                                          \
    if (getenv("OAI_GDBSTACKS"))                                                                               \
    {                                                                                                          \
        char tmp[1000];                                                                                        \
        sprintf(tmp, "gdb -ex='set confirm off' -ex 'thread apply all bt' -ex q -p %d < /dev/null", getpid()); \
        __attribute__((unused)) int dummy = system(tmp);                                                       \
    }                                                                                                          \
    fprintf(stderr, "\nExiting execution\n");                                                                  \
//    fflush(stdout);                                                                                            \
    fflush(stderr);                                                                                            \
    exit_function(__FILE__, __FUNCTION__, __LINE__, "_Assert_Exit_", OAI_EXIT_ASSERT);                         \
    abort(); // to avoid gcc warnings - never executed unless app-specific exit_function() does not exit() nor abort()

#define _Assert_(cOND, aCTION, fORMAT, aRGS...)                       \
    do                                                                \
    {                                                                 \
        if (!(cOND))                                                  \
        {                                                             \
            fprintf(stderr, "\nAssertion (%s) failed!\n"              \
                            "In %s() %s:%d\n" fORMAT,                 \
                    #cOND, __FUNCTION__, __FILE__, __LINE__, ##aRGS); \
            aCTION;                                                   \
        }                                                             \
    } while (0)

#define AssertFatal(cOND, fORMAT, aRGS...) _Assert_(cOND, _Assert_Exit_, fORMAT, ##aRGS)





#endif
/* End of this file. */