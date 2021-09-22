#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//#define VAP_ACL_USE_LINUX_MEM_API
#define VAP_ACL_LENGTH_VAP_NAME 32   /* Length of VAP name. */
#define VAP_ACL_LENGHT_MAC_ADDRESS 6 /* Size of: XXXXXXXXXXXX in hex. */
#define VAP_ACL_DEPTH_MAC_LIST 28    /* sizeof(AllowedMACAddresses) / 18 ~= 28 */
#define VAP_ACL_LENGTH_MAC_LIST 17   /* Size of: XX:XX:XX:XX:XX:XX in string. */
#define VAP_ACL_LENGTH_MAC_STR 513   /* Equal to sizeof LanWlanObject->X_ALU_COM_DeniedMACAddresses. */

/* Definition for mock */
#define WLDRV_ACL_MODE_DENY 1
#define WLDRV_ACL_MODE_ALLOW 2

#define BOOL unsigned char

/* InternetGatewayDevice.LANDevice.{i}.WLANConfiguration.{i}. */
typedef struct
{
    char X_ALU_COM_MACAddressControlMode[17];
    BOOL MACAddressControlEnabled;
    char AllowedMACAddresses[513];
    char X_ALU_COM_DeniedMACAddresses[513];
    char X_ALU_COM_MACAddressesDescription[1025];
} __attribute__((packed)) LanWlanObject;

typedef enum
{
    CFG_RET_FAIL = -1,  /* genernal error */
    CFG_RET_SUCCESS = 0 /**<Success. */
} CfgRet;

/* A type of structure for local VAP ACL instance control. */
typedef struct localVapACLInstance_T
{
    char cVapIfName[VAP_ACL_LENGTH_VAP_NAME];                                          /* Name of VAP. */
    unsigned char ucVapIndex;                                                          /* Index of VAP. */
    unsigned char ucACLMode;                                                           /* ACL mode: WLDRV_ACL_MODE_DENY or WLDRV_ACL_MODE_ALLOW. */
    unsigned char ucMacNum;                                                            /* Number of MAC address in the list. */
    unsigned char ucAclMacStrList[VAP_ACL_DEPTH_MAC_LIST][VAP_ACL_LENGTH_MAC_LIST];    /* MAC address list. */
    unsigned char ucAclMacHexList[VAP_ACL_DEPTH_MAC_LIST][VAP_ACL_LENGHT_MAC_ADDRESS]; /* MAC address list in HEX. */
    char cMACAddresses[VAP_ACL_LENGTH_MAC_STR];                                        /* MAC address in type of CHAR. */
} __attribute__((aligned(4))) localVapACLInstance_t;

/* End of mock...*/

#endif