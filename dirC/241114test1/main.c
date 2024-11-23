#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

int main(int argc, char *argv[]) {
    // Check for filename argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int channel_count = 0;
    char channels[MAX_LINE_LENGTH * 2] = "";  // Holds channel numbers as a single string

    // Read each line and process
    while (fgets(line, sizeof(line), file) != NULL) {
        int channel, cac;
        char type[4] = {0};
        //printf(">>>Check line: %s\n", line);
        // Check if line starts with a number (indicating a channel line)
        if (3 == sscanf(line, "%d %*d %*d %d %s", &channel, &cac, type)) {
            //printf(">>>Channel %d, CAC remain time: %d, type: %s\n", channel, cac, type);
            if (0 == strncmp("DFS", type, 3)) {
                // If cac is non-zero, add channel to list and increment count
                if (cac != 0) {
                    char channel_str[10];
                    snprintf(channel_str, sizeof(channel_str), " %d", channel);
                    strcat(channels, channel_str);  // Append channel to the list
                    channel_count++;
                }
            }
        }
    }

    fclose(file);

    // Output results
    if (channel_count > 0) {
        printf("Channels with cac != 0:%s\n", channels);
        printf("Total number of channels with cac != 0: %d\n", channel_count);
    } else {
        printf("No channels found with cac != 0.\n");
    }

    return 0;
}
