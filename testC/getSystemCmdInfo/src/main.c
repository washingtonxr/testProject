#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <string.h>

#define STRING_LENGTH 1024
#define DEFAULT_IF "ens160"

/* The exit status. Only to be accessed if WIFEXITED(x) is true.  */
#ifndef WEXITSTATUS
#define WEXITSTATUS(x) (((x) >> 8) & 0xff)
#endif

int system_call(const char *fmt, ...)
{
    int status;
    char cStrBuffer[STRING_LENGTH] = {0};

    snprintf(cStrBuffer, sizeof(cStrBuffer), fmt);
    status = system(cStrBuffer);

    return WEXITSTATUS(status);
}

int callSystemCmd(void)
{
    FILE *pFile = NULL;
    char cStrBuffer[STRING_LENGTH] = {0};
    char cResult[STRING_LENGTH] = {0};
    char *pPrt = NULL;

    sprintf(cStrBuffer,"ifconfig %s", DEFAULT_IF);
    printf("%s\n", cStrBuffer);
    system_call(cStrBuffer);

    sprintf(cStrBuffer,"ifconfig %s", DEFAULT_IF);
    if(NULL==(pFile = popen(cStrBuffer, "r"))) {
        printf("Execute command %s failed!\n",cStrBuffer);
        return -1;
    }

    while(fgets(cResult, sizeof(cResult), pFile)!=NULL) {
        pPrt = strstr(cResult, "inet");
        if (NULL == pPrt) {
            continue;
        }
        memset(cStrBuffer, 0, sizeof(cStrBuffer));
        sprintf(cStrBuffer, "%s", cResult);
        printf(">>>%p %s\n", pPrt, cStrBuffer);
    }

    return 0;
}


int main()
{
    unsigned int ulLoop = 0;
    char buf[16] = {0};

    for (ulLoop = 0; ulLoop < 20; ulLoop++) {
        printf("%d\t hello world.\n", ulLoop);
    }

    for (ulLoop = 0; ulLoop < 3; ulLoop++) {

        memset(buf, 0, sizeof(buf));

        sprintf(buf, "%u", 20 * (ulLoop + 1));

        printf("%s - %d - %d.\n", buf, atoi(buf), atoi(buf) / 20);

    }

    callSystemCmd();
    return 0;
}

