#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HAS_160MHZ_SUPPORT
#define MAX_CH_LIST 27
#define DUAL_BAND

#define BUFSIZ_8    8
#define BUFSIZ_16   16
#define BUFSIZ_32   32
#define BUFSIZ_64   64
#define BUFSIZ_128  128
#define BUFSIZ_256  256
#define BUFSIZ_512  512
#define BUFSIZ_1024 1024

enum BANCH_BW
{
    BANCH_BW_20MHZ,
    BANCH_BW_40MHZ,
    BANCH_BW_80MHZ,
#ifdef HAS_160MHZ_SUPPORT
    BANCH_BW_160MHZ,
#endif
    BANCH_BW_MAX
};

typedef struct _ban_ch_info
{
    int ch_list[MAX_CH_LIST];
    int ch_num;
} ban_ch_info;

typedef enum RADIO_INFO {
#ifdef DUAL_BAND
	RADIO_5G,
	RADIO_2G,
#else
	RADIO_5G_LOW,
	RADIO_2G,
	RADIO_5G_HIGH,
#endif
	RADIO_MAX,
	RADIO_INVALID = RADIO_MAX,
} RADIO_INFO;

enum {
    WLDRV_OK = 0,
    WLDRV_ERR = -1,
    WLDRV_RADIO_DOWN = -2,
    WLDRV_VAP_DOWN = -3,
};
// enum {
//     WLDRV_LOG_LEVEL_EMERG = 0,
//     WLDRV_LOG_LEVEL_ALERT,
//     WLDRV_LOG_LEVEL_CRIT,
//     WLDRV_LOG_LEVEL_ERR,
//     WLDRV_LOG_LEVEL_WARNING,
//     WLDRV_LOG_LEVEL_NOTICE,
//     WLDRV_LOG_LEVEL_INFO,
//     WLDRV_LOG_LEVEL_DEBUG,
//     WLDRV_LOG_LEVEL_NONE
// };

// #define WLDRV_EMERG(args...) printf(WLDRV_LOG_LEVEL_EMERG, __FUNCTION__, __LINE__, args)
// #define WLDRV_ALERT(args...) printf(WLDRV_LOG_LEVEL_ALERT, __FUNCTION__, __LINE__, args)
// #define WLDRV_CRIT(args...) printf(WLDRV_LOG_LEVEL_CRIT, __FUNCTION__, __LINE__, args)
// #define WLDRV_ERROR(args...) printf(WLDRV_LOG_LEVEL_ERR, __FUNCTION__, __LINE__, args)
// #define WLDRV_WARNING(args...) printf(WLDRV_LOG_LEVEL_WARNING, __FUNCTION__, __LINE__, args)
// #define WLDRV_NOTICE(args...) printf(WLDRV_LOG_LEVEL_NOTICE, __FUNCTION__, __LINE__, args)
// #define WLDRV_INFO(args...) printf(WLDRV_LOG_LEVEL_INFO, __FUNCTION__, __LINE__, args)
// #define WLDRV_DEBUG(args...) printf(WLDRV_LOG_LEVEL_DEBUG, __FUNCTION__, __LINE__, args)

#define WLDRV_LOG_LEVEL_EMERG "[EMERG] "
#define WLDRV_LOG_LEVEL_ALERT "[ALERT] "
#define WLDRV_LOG_LEVEL_CRIT "[CRIT] "
#define WLDRV_LOG_LEVEL_ERR "[ERROR] "
#define WLDRV_LOG_LEVEL_WARNING "[WARNING] "
#define WLDRV_LOG_LEVEL_NOTICE "[NOTICE] "
#define WLDRV_LOG_LEVEL_INFO "[INFO] "
#define WLDRV_LOG_LEVEL_DEBUG "[DEBUG] "

#define WLDRV_EMERG(format, ...) printf(WLDRV_LOG_LEVEL_EMERG "%s:%d " format, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define WLDRV_WLDRV_ALERTCRIT(format, ...) printf(WLDRV_LOG_LEVEL_ALERT "%s:%d " format, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define WLDRV_CRIT(format, ...) printf(WLDRV_LOG_LEVEL_CRIT "%s:%d " format, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define WLDRV_ERROR(format, ...) printf(WLDRV_LOG_LEVEL_ERR "%s:%d " format, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define WLDRV_WARNING(format, ...) printf(WLDRV_LOG_LEVEL_WARNING "%s:%d " format, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define WLDRV_NOTICE(format, ...) printf(WLDRV_LOG_LEVEL_NOTICE "%s:%d " format, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define WLDRV_INFO(format, ...) printf(WLDRV_LOG_LEVEL_INFO "%s:%d " format, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define WLDRV_DEBUG(format, ...) printf(WLDRV_LOG_LEVEL_DEBUG "%s:%d " format, __FUNCTION__, __LINE__, ##__VA_ARGS__)
// #define WLDRV_LOG_LEVEL_INFO "[INFO] "




#endif
