#include <stdio.h>
#include <stdlib.h>

unsigned char asicc2hex(const char m)
{
    switch (m)
    {
    case '0' ... '9':
        return (unsigned char)atoi(&m);
    case 'a' ... 'f':
        return 0xa + (m - 'a');
    case 'A' ... 'F':
        return 0xa + (m - 'A');
    default:
        goto error;
    }
error:
    exit(0);
}

/*convert a string,which length is 18, to a macaddress data type.*/
#define MAC_LEN_IN_BYTE 6


#define COPY_STR2MAC(mac, str)                                                  \
    unsigned int i;                                                             \
    do                                                                          \
    {                                                                           \
        for (i = 0; i < MAC_LEN_IN_BYTE; i++)                                   \
        {                                                                       \
            mac[i] = (asicc2hex(str[i * 3]) << 4) + asicc2hex(str[i * 3 + 1]);  \
        }                                                                       \
    } while (0)

/**
 * @brief Convert ASICC code to hex mode.
 * 
 * @param m 
 * @return unsigned char (Valid return 0xFF)
 */
unsigned char convertAsicc2Hex(const char ucElement)
{
    switch (ucElement)
    {
    case '0' ... '9':
        return (unsigned char)atoi(&ucElement);
    case 'a' ... 'f':
        return 0xa + (ucElement - 'a');
    case 'A' ... 'F':
        return 0xa + (ucElement - 'A');
    default:
        return 0xFF;
    }
}

#define CONVERT_MAC_STR2HEX(strMAC, hexMAC)                                                             \
    unsigned char ucLoop;                                                                               \
    do                                                                                                  \
    {                                                                                                   \
        for(ucLoop = 0; ucLoop < 6; ucLoop++)                                                           \
        {                                                                                               \
            hexMAC[i] = (convertAsicc2Hex(strMAC[i * 3]) << 4) + convertAsicc2Hex(strMAC[i * 3 + 1]);   \
        }                                                                                               \
    } while (0);                                                                                        \

int main(int argc, char **argv)
{
    unsigned char macaddr[8] = {0};
    char macaddr_str[18] = "8e:b2:cf:89:00:4a";
    COPY_STR2MAC(macaddr, macaddr_str);
    printf("0x%02x %02x\n", macaddr[0], macaddr[1]);
    printf("%02x %02x\n", macaddr[2], macaddr[3]);
    printf("%02x %02x\n", macaddr[4], macaddr[5]);

    return 0;
}