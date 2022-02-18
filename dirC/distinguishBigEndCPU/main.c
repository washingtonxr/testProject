#include <stdio.h>

int main(void)
{
    int a = 0x12345678;
    char *cp = (char *)&a;
    if (*cp == 0x78)
    {
        printf("CPU is LITTLE endian.\n");
    }
    else
    {
        printf("CPU is BIG endian.\n");
    }
    return 0;
}