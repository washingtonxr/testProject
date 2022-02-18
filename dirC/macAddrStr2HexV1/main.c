#include "main.h"

/**
 * @brief Handle MAC address converting.
 * 
 * @param pVapAclInstance 
 * @param newObj 
 * @return CfgRet 
 */
static CfgRet rts_LanWlanHandleMacAddr(localVapACLInstance_t *pVapAclInstance, LanWlanObject *newObj)
{
    const char cDelims1[] = ",";
    const char cDelims2[] = ":";
    unsigned char *ucMacTemp = NULL;
    unsigned char ucMacStrTemp[VAP_ACL_LENGTH_MAC_LIST] = {0};
    unsigned char ucMacStrTemp2[VAP_ACL_LENGHT_MAC_ADDRESS*2] = {0};
    unsigned char ucIndex = 0;
    unsigned char ucLoop1 = 0, ucLoop2 = 0;
    unsigned long long ucMacAddrInHex = {0};

    switch(pVapAclInstance->ucACLMode)
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

    ucMacTemp = strtok(pVapAclInstance->cMACAddresses, cDelims1);
    if(NULL != ucMacTemp)
    {
        memcpy(&pVapAclInstance->ucAclMacStrList[pVapAclInstance->ucMacNum++][0], ucMacTemp, 17);  /* Size of: XXXXXXXXXXXX in Hex. */
        printf("AclMode %d MAC addr(%d): %s\n", pVapAclInstance->ucACLMode, pVapAclInstance->ucMacNum, ucMacTemp);
        while(NULL != ucMacTemp)
        {
            /* Get rid of "," in MAC string. */
            ucMacTemp = strtok( NULL, cDelims1);
            if(NULL != ucMacTemp)
            {
                memcpy(&pVapAclInstance->ucAclMacStrList[pVapAclInstance->ucMacNum++][0], ucMacTemp, 17);  /* Size of: XXXXXXXXXXXX in Hex. */
                printf("AclMode %d MAC addr(%d): %s\n", pVapAclInstance->ucACLMode, pVapAclInstance->ucMacNum, ucMacTemp);
            }
        }
    }
    else
    {
        printf("Mac addr list for DENY is empty.\n");
    }

    /* Convert string to HEX of MAC address. */
    for(ucLoop1 = 0; ucLoop1 < pVapAclInstance->ucMacNum; ucLoop1++)
    {
        ucIndex = 0;
        memcpy(ucMacStrTemp, pVapAclInstance->ucAclMacStrList[ucLoop1], VAP_ACL_LENGTH_MAC_LIST);

        /* Get rid of ":" in MAC string. */
        ucMacTemp = strtok(ucMacStrTemp, cDelims2);
        if(NULL != ucMacTemp)
        {
            memcpy(ucMacStrTemp2 + (ucIndex++ << 1), ucMacTemp, 2);
            while(NULL != ucMacTemp)
            {
                ucMacTemp = strtok(NULL, cDelims2);
                if(NULL != ucMacTemp)
                {
                    memcpy(ucMacStrTemp2 + (ucIndex++ << 1), ucMacTemp, 2);
                    if(VAP_ACL_LENGHT_MAC_ADDRESS < ucIndex)
                    {
                        break;
                    }
                }
            }
        }

        //printf("ucMacTemp(%d) = %s\n", ucLoop1, ucMacStrTemp2);
        ucMacAddrInHex = strtoul(ucMacStrTemp2, NULL, 16);
        printf("0x%lx %d\n", ucMacAddrInHex, sizeof(long));

        for(ucLoop2 = 0; ucLoop2 < VAP_ACL_LENGHT_MAC_ADDRESS; ucLoop2++)
        {
            memcpy(&pVapAclInstance->ucAclMacHexList[ucLoop1][VAP_ACL_LENGHT_MAC_ADDRESS - 1 - ucLoop2], (unsigned char *)&ucMacAddrInHex + ucLoop2, 1);
            //printf("pVapAclInstance->ucAclMacHexList[%d][%d] = %02x\n", ucLoop1, ucLoop2, pVapAclInstance->ucAclMacHexList[ucLoop1][ucLoop2]);
        }
    }
#if 0
    printf("=============\n");
    for(ucLoop1 = 0; ucLoop1 < pVapAclInstance->ucMacNum; ucLoop1++)
    {
        printf("%d\n", ucLoop1);
        for(ucLoop2 = 0; ucLoop2 < VAP_ACL_LENGHT_MAC_ADDRESS; ucLoop2++)
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
    if(NULL == newObj)
    {
        printf("Memory allocate return failure.\n");
        return 0;
    }
    memset(newObj, 0, sizeof(LanWlanObject));

    plocalVapAclInst = (localVapACLInstance_t *)malloc(sizeof(localVapACLInstance_t));
    if(NULL == plocalVapAclInst)
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
        if(CFG_RET_SUCCESS != rts_LanWlanHandleMacAddr(plocalVapAclInst, newObj))
        {
            printf("rts_LanWlanHandleMacAddr return failure.\n");
            free(plocalVapAclInst);
            free(LanWlanObject);
            return CFG_RET_FAIL;
        }
    }
    else if (0 == strcmp(newObj->X_ALU_COM_MACAddressControlMode, "Allow"))
    {
        plocalVapAclInst->ucACLMode = WLDRV_ACL_MODE_ALLOW;
        if(CFG_RET_SUCCESS != rts_LanWlanHandleMacAddr(plocalVapAclInst, newObj))
        {
            printf("rts_LanWlanHandleMacAddr return failure.\n");
            free(plocalVapAclInst);
            free(LanWlanObject);
            return CFG_RET_FAIL;
        }
    }
    else
    {
        plocalVapAclInst->ucACLMode = 0;
    }

    free(plocalVapAclInst);
    free(LanWlanObject);
    printf("End of testing.\n");
    return 0;
}

