/* 
 * Author: Luke Hindman
 * Date: Fri 13 Nov 2020 12:21:37 PM PST
 * Description: imitate wc command
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define READ_BUFFER_SIZE 1024
#define MAX_FILEPATH_SIZE 4096

struct data_stats_struct {
    int num_chars;
    int num_words;
    int num_lines;
};

typedef struct data_stats_struct DataStats;

DataStats ProcessDataStream(FILE * in);

int main (int argc, char * argv[]) {

    /* display flags */
    int charFlag = false;
    int wordFlag = false;
    int lineFlag = false;

    /* Allocate space for filePath on stack and
     *      initialize filepath to empty string */
    char filePath[MAX_FILEPATH_SIZE];
    filePath[0] = '\0';

    int opt;

    while ((opt = getopt(argc, argv, "cwlhf:")) != -1) {
        switch (opt){
            case 'h':
                fprintf(stderr, "Usage: %s [-f <file>] [-c] [-w] [-l] [-h]\n", argv[0]);
                exit(0);
                break;
            case 'f':
                strncpy(filePath, optarg, MAX_FILEPATH_SIZE);
                break;
            case 'c':
                charFlag = true;
                break;
            case 'w':
                wordFlag = true;
                break;
            case 'l':
                lineFlag = true;
                break;
            default:
                fprintf(stderr, "Usage: %s [-f <file>] [-c] [-w] [-l] [-h]\n", argv[0]);
                exit(1);
                break;
        }
    }

    DataStats streamStats;

    // if empty string, read from stdin, else read from specified file
    if(strcmp(filePath,"") == 0) {
        streamStats = ProcessDataStream(stdin);
    } else {
        FILE * inputStream = fopen(filePath, "r");
        
        //exit if file doesn't exist
        if (inputStream == NULL) {
            fprintf(stderr, "ERROR: File could not be found\n");
            exit(1);
        }

        streamStats = ProcessDataStream(inputStream);
        fclose(inputStream);
    }

    /* Display appropriate fields from streamStats
     *  based on user input */
    if (!charFlag && !wordFlag && !lineFlag) {
        fprintf(stdout, "%7d lines %7d words %7d characters\n", streamStats.num_lines,
                        streamStats.num_words, streamStats.num_chars);
    } else {
        if (lineFlag) {
            fprintf(stdout, "%7d lines", streamStats.num_lines);
        }
        if (wordFlag) {
            fprintf(stdout, "%7d words", streamStats.num_words);
        }
        if (charFlag) {
            fprintf(stdout, "%7d characters", streamStats.num_chars);
        }
        fprintf(stdout, "\n");
    }

    return 0;
}

DataStats ProcessDataStream(FILE * in) {
    char buffer[READ_BUFFER_SIZE];
    int readCount = 0;

    DataStats stats = {0,0,0};

    while (fgets(buffer, READ_BUFFER_SIZE, in) != NULL) {
        readCount = strlen(buffer);
        /* Update char stats */
        stats.num_chars += readCount;

        /* Update line stats*/
        if (buffer[readCount - 1] == '\n') {
            stats.num_lines++;
        }

        /* Update word stats */
        char * token = strtok(buffer, " \n\t");
        if (token != NULL) {
            stats.num_words++;
            while (strtok(NULL, " \n\t") != NULL) {
                stats.num_words++;
            }
        }
    }

    return stats;
}