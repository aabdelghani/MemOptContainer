#include "error_handling.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void logError(const char *message) {
    // Open the file in append mode, create if it doesn't exist
    FILE *file = fopen("error_log.txt", "a");
    if (!file) {
        perror("Could not open or create error log file");
        return;
    }

    // Get the current time
    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    if (timestamp) {
        timestamp[strlen(timestamp) - 1] = '\0'; // Remove the newline character
    } else {
        timestamp = "Unknown time";
    }

    // Write the error message to the log file
    fprintf(file, "[%s] ERROR: %s\n", timestamp, message);
    fclose(file);
}

