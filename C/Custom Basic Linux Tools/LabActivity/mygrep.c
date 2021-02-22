/* 
 * Author: Luke Hindman
 * Date: Fri 13 Nov 2020 12:21:37 PM PST
 * Description: imitates the grep command
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define READ_BUFFER_SIZE 1024
#define MAX_FILEPATH_SIZE 4096
#define Max_FILTER_SIZE 256

int FilterDataStream(const char* filter, FILE * in, FILE * out);

int main (int argc, char * argv[]) {

    /* Allocate space for filePath on stack and
     *      initialize filepath to empty string */
    char filePath[MAX_FILEPATH_SIZE];
    filePath[0] = '\0';

    /* Allocate space for searcFilter on stack and initialize
     * searchFilter to empty string */
    char searchFilter[Max_FILTER_SIZE];
    searchFilter[0] = '\0';

    int opt;

    while ((opt = getopt(argc, argv, "hf:s:")) != -1) {
        switch (opt){
            case 'h':
                fprintf(stderr, "Usage: %s -s <filter> [-f <file>] [-h]\n", argv[0]);
                exit(0);
                break;
            case 'f':
                strncpy(filePath, optarg, MAX_FILEPATH_SIZE);
                break;
            case 's':
                strncpy(searchFilter, optarg, Max_FILTER_SIZE);
                break;
            default:
                fprintf(stderr, "Usage: %s -s <filter> [-f <file>] [-h]\n", argv[0]);
                exit(1);
                break;
        }
    }

    /* Validate that the user specified a search filter*/
    if(strcmp(searchFilter, "") == 0) {
        fprintf(stderr, "Usage: %s -s <filter> [-f <file>] [-h]\n", argv[0]);
        exit(1);
    }

    int status;

    // if empty string, read from stdin, else read from specified file
    if(strcmp(filePath,"") == 0) {
        status = FilterDataStream(searchFilter, stdin, stdout);
    } else {
        FILE * inputStream = fopen(filePath, "r");
        
        //exit if file doesn't exist
        if (inputStream == NULL) {
            fprintf(stderr, "ERROR: File could not be found\n");
            exit(1);
        }

        status = FilterDataStream(searchFilter, inputStream, stdout);
        fclose(inputStream);
    }

    if (status != 0) {
        fprintf(stderr, "Error: Copy did not complete Successfully\n");
        exit(1);
    }

    return 0;
}

int FilterDataStream(const char* filter, FILE * in, FILE * out) {
    char buffer[READ_BUFFER_SIZE];
    int readCount = 0;
    int writeCount = 0;

    while (fgets(buffer, READ_BUFFER_SIZE, in) != NULL) {

        if (strstr(buffer, filter) != NULL) {
            readCount = strlen(buffer);
            writeCount = fwrite(buffer, sizeof(char), readCount, out);

            if (writeCount != readCount) {
                fprintf(stderr, "Error: an error occurred while writing to output stream\n");
                return -1;
            }
        }
    }

    return 0;
}
