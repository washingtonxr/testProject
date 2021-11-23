#include <stdio.h>
#include <string.h>

#define MAX_DEPTH 16

int main(int argc, char *argv)
{
    char cBuffer[] = "this is washington ruan test code @ 2021";
    const char pDelimiter = ' ';
    const char pDelimiter2 = 0xa;
#if 1
    char *pBuffer[MAX_DEPTH] = {0};
    char *pStringSpiltCurrentPrt = NULL;
    unsigned char ucLoop1 = 0;
    unsigned char ucLoop2 = 0;

    printf("Sting: %s\n", cBuffer);
    printf(">>>>>>>>>>>> cBuffer: %s.\n", cBuffer);
    for (ucLoop1 = 0; ucLoop1 < strlen(cBuffer); ucLoop1++) {
        if (pDelimiter == cBuffer[ucLoop1]) {
            cBuffer[ucLoop1] = pDelimiter2;
        }
    }
    printf(">>>>>>>>>>>> cBuffer: %s.\n", cBuffer);
    for (ucLoop1 = 0; ucLoop1 < strlen(cBuffer); ucLoop1++) {
        printf(">>>cBuffer[%d]: 0x%x\n", ucLoop1, cBuffer[ucLoop1]);
    }

    pStringSpiltCurrentPrt = strtok(cBuffer, &pDelimiter2);
    ucLoop1 = 0;
    while(NULL != pStringSpiltCurrentPrt) {
        pBuffer[ucLoop1] = pStringSpiltCurrentPrt;
        printf(">>>ucLoop1:%d - %p - %s\n", ucLoop1, pBuffer[ucLoop1], pBuffer[ucLoop1]);
        ucLoop1++;
        pStringSpiltCurrentPrt = strtok(NULL, &pDelimiter2);
    }

    printf(">>>ucLoop1:%d\n", ucLoop1);
    for (ucLoop2 = 0; ucLoop2 < ucLoop1; ucLoop2++) {
        if (NULL != pBuffer[ucLoop2]) {
            printf(">>>%s\n", pBuffer[ucLoop2]);
        }
    }

#else
    //char cBuffer[BUFSIZ_32] = {0};
    char pSplitBuffer[32][64] = {0, };
    char *pStringSpiltHeadPrt = NULL;
    char *pStringSpiltCurrentPrt = NULL;
    unsigned char ucLoop1 = 0;
    unsigned char ucLoop2 = 0;
    unsigned char ucAccumulative = 0;

    printf(">>>>>>>>>>>> cBuffer: %s.\n", cBuffer);
    for (ucLoop1 = 0; ucLoop1 < strlen(cBuffer); ucLoop1++) {
        if (pDelimiter == cBuffer[ucLoop1]) {
            cBuffer[ucLoop1] = pDelimiter2;
        }
    }

    printf(">>>>>>>>>>>> cBuffer: %s.\n", cBuffer);
    for (ucLoop1 = 0; ucLoop1 < strlen(cBuffer); ucLoop1++) {
        printf(">>>cBuffer[%d]: 0x%x\n", ucLoop1, cBuffer[ucLoop1]);
    }
    pStringSpiltHeadPrt = &cBuffer[0];
    for (ucLoop1 = 0; ucLoop1 < strlen(cBuffer) + 1; ucLoop1++) {
        ucAccumulative++;
        pStringSpiltCurrentPrt = &cBuffer[ucLoop1];
        if (pDelimiter2 == *pStringSpiltCurrentPrt) {
            memcpy(pSplitBuffer[ucLoop2], pStringSpiltHeadPrt, ucAccumulative - 1);
            printf("%s - %d\n", pSplitBuffer[ucLoop2], ucLoop1);
            pStringSpiltHeadPrt = pStringSpiltCurrentPrt + 1;
            ucLoop2++;
            ucAccumulative = 0;
        } else if (0 == *pStringSpiltCurrentPrt) {
            memcpy(pSplitBuffer[ucLoop2], pStringSpiltHeadPrt, ucLoop1);
            ucLoop2++;
        }
    }

    for (ucLoop1 = 0; ucLoop1 < ucLoop2; ucLoop1++) {
        printf("%d: %s\n", ucLoop1, pSplitBuffer[ucLoop1]);
    }
#endif
    return 0;
}