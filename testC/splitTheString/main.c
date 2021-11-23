#include <stdio.h>
#include <string.h>

#define MAX_DEPTH 16

int main(int argc, char *argv)
{
    char cBuffer[] = "this is washington ruan test code @ 2021";
#if 0
    char *pBuffer[MAX_DEPTH] = {NULL};
    char *p = NULL;
    int i = 0;

    printf("Sting: %s\n", pString);
    /*
    分割同一字符串，第一次调用时传入字符串的首地址，第二个参数是分割符
    这里的分割符是空格，假如 buf = "hello;world;123"，你还可以按照 ";" 来分割buf
    此时第二个参数就填写 ";"
    */
    p = strtok(pString, " ");
    while(NULL != p) {
        pBuffer[i] = p;
        ++i;
        // 再次调用分割时指针要变为NULL, 也就是这里的第一个参数，分割的字符串还是str
        // 第二个参数要和第一次调用时的分割符保持一致
        p = strtok(NULL, " ");
    }

    for (i = 0; i < MAX_DEPTH - 1; ++i) {
        if (NULL != pBuffer[i]) {
            printf("%s\n", pBuffer[i]);
        }
    }

#else
    //char cBuffer[BUFSIZ_32] = {0};
    char pSplitBuffer[32][64] = {0, };
    char *pStringSpiltHeadPrt = NULL;
    char *pStringSpiltCurrentPrt = NULL;
    const char pDelim = 0x20;
    unsigned char ucLoop1 = 0;
    unsigned char ucLoop2 = 0;
    unsigned char ucAccumulative = 0;

    printf(">>>>>>>>>>>> cBuffer: %s.\n", cBuffer);
    for (ucLoop1 = 0; ucLoop1 < strlen(cBuffer); ucLoop1++) {
        printf(">>>cBuffer[%d]: 0x%x\n", ucLoop1, cBuffer[ucLoop1]);
    }
    pStringSpiltHeadPrt = &cBuffer[0];
    for (ucLoop1 = 0; ucLoop1 < strlen(cBuffer) + 1; ucLoop1++) {
        ucAccumulative++;
        pStringSpiltCurrentPrt = &cBuffer[ucLoop1];
        if (pDelim == *pStringSpiltCurrentPrt) {
            memcpy(pSplitBuffer[ucLoop2], pStringSpiltHeadPrt, ucAccumulative);
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