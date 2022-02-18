#include "main.h"

/**
 * @brief Convert ASICC code to hex mode.
 * 
 * @param ucElement
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

#define CONVERT_MAC_STR2HEX(strMAC, hexMAC)                                                           \
    unsigned char i;                                                                                  \
    do                                                                                                \
    {                                                                                                 \
        for (i = 0; i < 6; i++)                                                                       \
        {                                                                                             \
            hexMAC[i] = (convertAsicc2Hex(strMAC[i * 3]) << 4) + convertAsicc2Hex(strMAC[i * 3 + 1]); \
        }                                                                                             \
    } while (0);

/**
 * @brief Handle MAC address converting.
 * 
 * @param pVapAclInstance 
 * @param newObj 
 * @return CfgRet 
 */
static CfgRet rts_LanWlanHandleMacAddr(localVapACLInstance_t *pVapAclInstance, LanWlanObject *newObj)
{
    unsigned char *ucMacTemp = NULL;
    unsigned char ucMacStrTemp[VAP_ACL_LENGTH_MAC_LIST] = {0};
    unsigned char ucMacStrTemp2[VAP_ACL_LENGHT_MAC_ADDRESS * 2] = {0};
    unsigned char ucIndex = 0;
    unsigned char ucLoop1 = 0, ucLoop2 = 0;
    unsigned long long ucMacAddrInHex = {0};

    switch (pVapAclInstance->ucACLMode)
    {
    case WLDRV_ACL_MODE_DENY:
        strcpy(pVapAclInstance->cMACAddresses, newObj->X_ALU_COM_DeniedMACAddresses);
        break;
    case WLDRV_ACL_MODE_ALLOW:
        strcpy(pVapAclInstance->cMACAddresses, newObj->AllowedMACAddresses);
        break;
    default:
        printf("pVapAclInstance->ucACLMode %d is invalid.\n", pVapAclInstance->ucACLMode);
        return CFG_RET_FAIL;
    }

    /* Get rid of "," out of string. */
#if 0
    ucMacTemp = strtok(pVapAclInstance->cMACAddresses, ",");
    if (NULL != ucMacTemp)
    {
        memcpy(&pVapAclInstance->ucAclMacStrList[pVapAclInstance->ucMacNum++][0], ucMacTemp, 17); /* Size of: XXXXXXXXXXXX in Hex. */
        printf("AclMode %d MAC addr(%d): %s\n", pVapAclInstance->ucACLMode, pVapAclInstance->ucMacNum, ucMacTemp);
        while (NULL != ucMacTemp)
        {
            /* Get rid of "," in MAC string. */
            ucMacTemp = strtok(NULL, ",");
            if (NULL != ucMacTemp)
            {
                memcpy(&pVapAclInstance->ucAclMacStrList[pVapAclInstance->ucMacNum++][0], ucMacTemp, 17); /* Size of: XXXXXXXXXXXX in Hex. */
                printf("AclMode %d MAC addr(%d): %s\n", pVapAclInstance->ucACLMode, pVapAclInstance->ucMacNum, ucMacTemp);
            }
        }
    }
    else
    {
        printf("Mac addr list for DENY is empty.\n");
    }
#else
    /* Get rid of "," & ":" from string. */
    char *pStrElement = (char *)&pVapAclInstance->cMACAddresses;
    unsigned char ucEnLoop = 1;
    unsigned int ulCharIndex = 0;
    unsigned int ulMacIndex = 0;

    printf("%s\n", pVapAclInstance->cMACAddresses);

    do
    {
        printf("-------> %c %c 0x%02X 0x%02X\n", (char)*pStrElement, (char)*(pStrElement + 1), (char)*pStrElement, (char)*(pStrElement + 1));
        switch ((char)*pStrElement)
        {
        case '0' ... '9':
        case 'a' ... 'f':
        case 'A' ... 'F':
            pVapAclInstance->ucAclMacHexList[ulMacIndex][ulCharIndex] =
                (convertAsicc2Hex((char)*pStrElement) << 4) + convertAsicc2Hex((char)*(pStrElement + 1));
            printf("ucAclMacHexList[%d][%d] = 0x%02x\n", ulMacIndex, ulCharIndex, pVapAclInstance->ucAclMacHexList[ulMacIndex][ulCharIndex]);
            ulCharIndex++;
            if (ulCharIndex >= VAP_ACL_LENGHT_MAC_ADDRESS)
            {
                ulCharIndex = 0;
                ulMacIndex++;
            }
            pStrElement += 2;
            break;
        case '\0':
            pVapAclInstance->ucMacNum = ulMacIndex;
            printf("pVapAclInstance->ucMacNum = %d\n", pVapAclInstance->ucMacNum);
            ucEnLoop = 0;
            break;
        default:
            pStrElement++;
            break;
        }
    } while (ucEnLoop);

    //exit(0);
#endif

#if 0
    /* Convert string to HEX of MAC address. */
    for (ucLoop1 = 0; ucLoop1 < pVapAclInstance->ucMacNum; ucLoop1++)
    {
        ucIndex = 0;
        memcpy(ucMacStrTemp, pVapAclInstance->ucAclMacStrList[ucLoop1], VAP_ACL_LENGTH_MAC_LIST);
#if 0
        /* Get rid of ":" out of MAC string. */
        ucMacTemp = strtok(ucMacStrTemp, ":");
        if (NULL != ucMacTemp)
        {
            memcpy(ucMacStrTemp2 + (ucIndex << 1), ucMacTemp, 2);
            ucIndex++;
            while (NULL != ucMacTemp)
            {
                ucMacTemp = strtok(NULL, ":");
                if (NULL != ucMacTemp)
                {
                    memcpy(ucMacStrTemp2 + (ucIndex << 1), ucMacTemp, 2);
                    ucIndex++;
                    if (VAP_ACL_LENGHT_MAC_ADDRESS < ucIndex)
                    {
                        break;
                    }
                }
            }
        }
#else

#endif
        printf("ucMacTemp(%d) = %s\n", ucLoop1, ucMacStrTemp2);
        ucMacAddrInHex = strtoul(ucMacStrTemp2, NULL, 16);
        printf("0x%lx %d\n", ucMacAddrInHex, sizeof(long));

        for (ucLoop2 = 0; ucLoop2 < VAP_ACL_LENGHT_MAC_ADDRESS; ucLoop2++)
        {
#if 0
            memcpy(&pVapAclInstance->ucAclMacHexList[ucLoop1][VAP_ACL_LENGHT_MAC_ADDRESS - 1 - ucLoop2], (unsigned char *)&ucMacAddrInHex + ucLoop2, 1);
            //printf("0x%02X ", *((unsigned char *)&ucMacAddrInHex + ucLoop2));
#else
            pVapAclInstance->ucAclMacHexList[ucLoop1][ucLoop2] = ucMacAddrInHex >> 8 * 6 - 8;
            ucMacAddrInHex <<= 8;
#endif
            //printf("pVapAclInstance->ucAclMacHexList[%d][%d] = %02x\n", ucLoop1, ucLoop2, pVapAclInstance->ucAclMacHexList[ucLoop1][ucLoop2]);
        }
        printf("\n");
    }
#endif
#if 1
    printf("=============\n");
    for (ucLoop1 = 0; ucLoop1 < pVapAclInstance->ucMacNum; ucLoop1++)
    {
        printf("%d\n", ucLoop1);
        for (ucLoop2 = 0; ucLoop2 < VAP_ACL_LENGHT_MAC_ADDRESS; ucLoop2++)
        {
            printf("ucAclMacHexList[%d][%d] = %02x\n", ucLoop1, ucLoop2, pVapAclInstance->ucAclMacHexList[ucLoop1][ucLoop2]);
        }
    }
#endif
    return CFG_RET_SUCCESS;
}

/**
 * @brief Main function of mocking.
 * 
 * @return int 
 */
int main(void)
{
    LanWlanObject *newObj = NULL;
    localVapACLInstance_t *plocalVapAclInst = NULL;

    newObj = (LanWlanObject *)malloc(sizeof(LanWlanObject));
    if (NULL == newObj)
    {
        printf("Memory allocate return failure.\n");
        return 0;
    }
    memset(newObj, 0, sizeof(LanWlanObject));

    plocalVapAclInst = (localVapACLInstance_t *)malloc(sizeof(localVapACLInstance_t));
    if (NULL == plocalVapAclInst)
    {
        printf("Memory allocate return failure.\n");
        return 0;
    }
    memset(plocalVapAclInst, 0, sizeof(localVapACLInstance_t));

    /* Set pre-testing parameter. */
    strcpy(newObj->X_ALU_COM_DeniedMACAddresses, "00:11:22:33:44:00,00:11:22:33:44:11,00:11:22:33:44:22,00:11:22:33:44:33,00:11:22:33:44:44");
    strcpy(newObj->X_ALU_COM_MACAddressControlMode, "Deny");

    /* Check the necessary of update ACL rules. */
    if (0 == strcmp(newObj->X_ALU_COM_MACAddressControlMode, "Deny"))
    {
        plocalVapAclInst->ucACLMode = WLDRV_ACL_MODE_DENY;
        if (CFG_RET_SUCCESS != rts_LanWlanHandleMacAddr(plocalVapAclInst, newObj))
        {
            printf("rts_LanWlanHandleMacAddr return failure.\n");
#ifdef VAP_ACL_USE_LINUX_MEM_API
            free(plocalVapAclInst);
#endif
            return CFG_RET_FAIL;
        }
    }
    else if (0 == strcmp(newObj->X_ALU_COM_MACAddressControlMode, "Allow"))
    {
        plocalVapAclInst->ucACLMode = WLDRV_ACL_MODE_ALLOW;
        if (CFG_RET_SUCCESS != rts_LanWlanHandleMacAddr(plocalVapAclInst, newObj))
        {
            printf("rts_LanWlanHandleMacAddr return failure.\n");
#ifdef VAP_ACL_USE_LINUX_MEM_API
            free(plocalVapAclInst);
#endif
            return CFG_RET_FAIL;
        }
    }
    else
    {
        plocalVapAclInst->ucACLMode = 0;
    }

    printf("End of testing.\n");
    return 0;
}
