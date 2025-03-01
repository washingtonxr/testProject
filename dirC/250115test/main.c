#include "main.h"

static void func1(int argc, char *argv[]) {
    printf("func1\n");
#if 0
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", argv[1]);
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1) {
        line[read - 1] = '\0'; // Remove newline character
        process_line(line);
    }

    free(line);
    fclose(file);
#endif
}

static int separate(char *previous, int *next)
{
    const char *delim = ",";
    char *token = NULL, *ptr = NULL;
    int i = 0;
    token = strtok_r(previous, delim, &ptr);
    while (token)
    {
        next[i++] = atoi(token);
        token = strtok_r(NULL, delim, &ptr);
    }
    return i;
}

static bool banned_5g_is_in(ban_ch_info *ban_ch_info, int ch)
{
    for (int i = 0; i < ban_ch_info->ch_num; i++)
    {
        if (ban_ch_info->ch_list[i] == ch)
            return true;
    }

    return false;
}

static void banned_5g_set_ch(int ch[], int ch_start, int bw_num)
{
    for (int i = 0; i < bw_num; i++)
    {
        ch[i] = ch_start + 4 * i;
    }
}

static void ban_5g_channels_by_range(
#if 0
	ban_ch_info *ban_ch_info,
#else
    ban_ch_info ban_ch_info[BANCH_BW_MAX],
#endif
	int start_channel, int end_channel, int channel)
{
    for (int bw = 0; bw < BANCH_BW_MAX; bw++)
    {
        int bw_num = (1<<bw);                                       // how many 20MHz in this bandwidth
        if (channel >= start_channel && channel <= end_channel      // channel should be in [start_channel, end_channel]
            && end_channel - start_channel >= 4*(bw_num-1))         // channel range should be large enough for this bandwidth
        {
            int ban_ch_start = start_channel + (((channel - start_channel) >> (bw+2)) << (bw+2));   // the first 20MHz for this channel
            int ban_ch_end = ban_ch_start + 4 * (bw_num-1);                                         // the last 20MHz for this channel
            if (ban_ch_end <= end_channel && !banned_5g_is_in(&ban_ch_info[bw], ban_ch_start))      // should not exceed the channel range
            {
				if (ban_ch_info[bw].ch_num + bw_num <= MAX_CH_LIST)
				{
					banned_5g_set_ch(&ban_ch_info[bw].ch_list[ban_ch_info[bw].ch_num], ban_ch_start, bw_num);
					ban_ch_info[bw].ch_num += bw_num;
				}
				else
				{
					WLDRV_ERROR("ERROR: ch_num(%d), bw_num(%d), will overflow", ban_ch_info[bw].ch_num, bw_num);
				}
            }
        }
    }
}

static void ban_5g_channels(
#if 0
ban_ch_info *ban_ch_info, 
#else
ban_ch_info ban_ch_info[BANCH_BW_MAX],
#endif
int s)
{
    ban_5g_channels_by_range(ban_ch_info, 36, 64, s);
    ban_5g_channels_by_range(ban_ch_info, 100, 144, s);
    ban_5g_channels_by_range(ban_ch_info, 149, 161, s);
    ban_5g_channels_by_range(ban_ch_info, 165, 173, s);
}

static void ban_5g_channels2(
    ban_ch_info ban_ch_info[BANCH_BW_MAX],
    int channel)
{
    /* WLAN 5G channels map */
    const int ranges[][2] = {
        /* Start, End */
        {36,   64}, /* U-NII-1 & U-NII-2A */
        {100, 144}, /* U-NII-2C */
        {149, 161}, /* U-NII-3 */
        {165, 173}  /* U-NII-E */
    };
    const int num_ranges = sizeof(ranges) / sizeof(ranges[0]);

    // Iterate through each range
    for (int i = 0; i < num_ranges; i++) {
        int start_channel = ranges[i][0];
        int end_channel = ranges[i][1];

        for (int bw = 0; bw < BANCH_BW_MAX; bw++) {
            int bw_num = (1 << bw); // Number of 20MHz segments in this bandwidth
            int range_threshold = 4 * (bw_num - 1); // Minimum range required for this bandwidth

            // Check if the channel is within range and the range is sufficient
            if (channel < start_channel || channel > end_channel ||
                (end_channel - start_channel < range_threshold)) {
                continue;
            }

            // Calculate the start and end of the banned channels for this bandwidth
            int ban_ch_start = start_channel + (((channel - start_channel) >> (bw + 2)) << (bw + 2));
            int ban_ch_end = ban_ch_start + range_threshold;

            // Validate if ban_ch_end is within the range and if the channel is not already banned
            if (ban_ch_end > end_channel || banned_5g_is_in(&ban_ch_info[bw], ban_ch_start)) {
                continue;
            }

            // Check if adding the channels will exceed the maximum limit
            if (ban_ch_info[bw].ch_num + bw_num > MAX_CH_LIST) {
                WLDRV_ERROR("ERROR: ch_num(%d), bw_num(%d), will overflow",
                            ban_ch_info[bw].ch_num, bw_num);
                continue;
            }

            // Ban the channels and update the count
            banned_5g_set_ch(&ban_ch_info[bw].ch_list[ban_ch_info[bw].ch_num],
                             ban_ch_start, bw_num);
            ban_ch_info[bw].ch_num += bw_num;
        }
    }
}

static void toString(int *sequence, int len, char *buf, bool spaceFlag)
{
    int i = 0;
    char string[100];
    if (len > 0)
    {
        memset(string, 0, sizeof(string));
        snprintf(string, sizeof(string), "%d", sequence[i]);
        strncpy(buf, string, sizeof(string));
    }
    for (i = 1; i < len; i++)
    {
        memset(string, 0, sizeof(string));
        if (spaceFlag)
            snprintf(string, sizeof(string), "%s %d", string, sequence[i]);
        else
            snprintf(string, sizeof(string), "%s,%d", string, sequence[i]);
        strncat(buf, string, strlen(string));
    }
}

static RADIO_INFO check_radio_name(char *radio)
{
#if 0
	int i = 0, j = 0;
	for (i = 0; i < MAX_NUM_RADIO; i++)
	{
		for (j = 0; j < MAX_NUM_RADIO; j++)
			if (wldrv_all[i].radio[j] && (strcmp(wldrv_all[i].radio[j], radio) == 0))
				return j;
	}
    WLDRV_ERROR("Can't find radio %s\n", radio);
    return RADIO_INVALID;
#else
    return RADIO_5G;
#endif
}

static int saveBannedChannels(char *radio, const char *ch_20M, const char *ch_40M, const char *ch_80M, const char *ch_160M)
{
    char ch[BUFSIZ_512] = {0};
    char ch_20M_tmp[BUFSIZ_128] = {0};
    char ch_40M_tmp[BUFSIZ_128] = {0};
    char ch_80M_tmp[BUFSIZ_128] = {0};
    char ch_160M_tmp[BUFSIZ_128] = {0};

    RADIO_INFO radio_info = check_radio_name(radio);
    if (RADIO_INVALID == radio_info)
    {
        WLDRV_ERROR("error radio: %s\n", radio);
        return WLDRV_ERR;
    }
    WLDRV_DEBUG("Wifi radio %s, %d\n", radio, radio_info);
    if ( ch_20M != NULL )
    {
        if (strlen(ch_20M) != 0)
        {
            strncpy(ch_20M_tmp, ch_20M, BUFSIZ_128-1);
        }
    }

    if ( ch_40M != NULL )
    {
        if (strlen(ch_40M) != 0)
        {
            strncpy(ch_40M_tmp, ch_40M, BUFSIZ_128-1);
        }
    }

    if ( ch_80M != NULL )
    {
        if (strlen(ch_80M) != 0)
        {
            strncpy(ch_80M_tmp, ch_80M, BUFSIZ_128-1);
        }
    }

    if ( ch_160M != NULL )
    {
        if (strlen(ch_160M) != 0)
        {
            strncpy(ch_160M_tmp, ch_160M, BUFSIZ_128-1);
        }
    }
    
    WLDRV_DEBUG("Wifi radio %s, %d, ch_20M_tmp<%s>, ch_40M_tmp<%s>, ch_80M_tmp<%s>, ch_160M_tmp<%s>\n", 
                        radio, radio_info, ch_20M_tmp, ch_40M_tmp, ch_80M_tmp, ch_160M_tmp);

    if ((strlen(ch_20M_tmp) == 0) && (strlen(ch_40M_tmp) == 0) && (strlen(ch_80M_tmp) == 0) && (strlen(ch_160M_tmp) == 0))
    {
        WLDRV_DEBUG("Wifi radio %s, %d, no banned channels\n", radio, radio_info);
    }
    else
    {
        strcat(ch, ch_20M_tmp);
        strcat(ch, ";");
        strcat(ch, ch_40M_tmp);
        if (RADIO_2G != radio_info)
        {
            strcat(ch, ";");
            strcat(ch, ch_80M_tmp);
#ifdef HAS_160MHZ_SUPPORT
            strcat(ch, ";");
            strcat(ch, ch_160M_tmp);
#endif
        }
    }
         
    WLDRV_DEBUG("Wifi radio %s banned channels are <%s>--\n", radio, ch);
#if 0
    /*SET banned channel list for localrrm */
    if (set_uci_config("wireless", radio, "banned_chan_list", ch, true))
    {
        return WLDRV_OK;
    }
    else
    {
        WLDRV_ERROR("set_uci_config fail: vap: %s, banned channel list <%s>\n", radio, ch);
        return WLDRV_ERR;
    }
#endif
    return WLDRV_OK;
}

static int fun2(void) {
    WLDRV_INFO("func2\n");
    char bannedChList[256] = "132,136";
    char radio[32] = "wifi0";

    int chans_20M[32] = {0};
    int chans_count_20M = 0;
    char banned_chans_160[128] = {0};
    char banned_chans_20[128] = {0};
    char banned_chans_40[128] = {0};
    char banned_chans_80[128] = {0};

	ban_ch_info ban_ch_info[BANCH_BW_MAX];
	memset(ban_ch_info, 0, sizeof(ban_ch_info));

    WLDRV_INFO("DUMP-common_radio_banned_channels----<%s>-----\n", bannedChList);

    snprintf(banned_chans_20, sizeof(banned_chans_20), "%s", bannedChList);

    chans_count_20M = separate(banned_chans_20, chans_20M); // int array(44,104)
    for (int i = 0; i < chans_count_20M; i++)
    {
        ban_5g_channels2(ban_ch_info, chans_20M[i]);
    }

    toString(ban_ch_info[BANCH_BW_40MHZ].ch_list, ban_ch_info[BANCH_BW_40MHZ].ch_num, banned_chans_40, false);
    toString(ban_ch_info[BANCH_BW_80MHZ].ch_list, ban_ch_info[BANCH_BW_80MHZ].ch_num, banned_chans_80, false);
    toString(ban_ch_info[BANCH_BW_160MHZ].ch_list, ban_ch_info[BANCH_BW_160MHZ].ch_num, banned_chans_160, false);
    saveBannedChannels(radio, bannedChList, banned_chans_40, banned_chans_80, banned_chans_160);	//save banned channels for localrrm
    WLDRV_INFO("Black List----40M are <%s>--80M are-<%s>--160M are-<%s>--\n", banned_chans_40, banned_chans_80, banned_chans_160);

    return 0;
}

int main(int argc, char *argv[]) {
#if 0
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
#endif
    func1(argc, argv);
    fun2();

    return 0;
}
