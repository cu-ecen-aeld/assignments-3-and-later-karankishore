#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char *argv[])
{
    openlog("Test Writer", LOG_PID | LOG_CONS, LOG_USER);
	if(argc < 3){
        syslog(LOG_ERR, "Insufficient args");
        return 1;
    }

    char *filePath = argv[1];
    char *string = argv[2];

    if(strlen(string) == 0){
        syslog(LOG_ERR, "String not provided");
        return 1;
    }

    FILE *file = fopen(filePath, "w");
    if(file == NULL){
        syslog(LOG_ERR, "Failed to open the file");
        return 1;
    }
    syslog(LOG_DEBUG, "Writing %s to %s", string, filePath);
    fprintf(file, "%s", string);
    fclose(file);
    closelog();
}
