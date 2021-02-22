/* 
 * Author: Luke Hindman
 * Date: Fri 13 Nov 2020 12:21:37 PM PST
 * Description: basic implementation of sort command
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define READ_BUFFER_SIZE 1024
#define MAX_FILEPATH_SIZE 4096

int SortDataStream(int reverse, FILE * in, FILE * out);

int main (int argc, char * argv[]) {

    int reverseFlag = false;

    /* Allocate space for filePath on stack and
     *      initialize filepath to empty string */
    char filePath[MAX_FILEPATH_SIZE];
    filePath[0] = '\0';

    int opt;

    while ((opt = getopt(argc, argv, "hrf:")) != -1) {
        switch (opt){
            case 'h':
                fprintf(stderr, "Usage: %s [-f <file>] [-h]\n", argv[0]);
                exit(0);
                break;
            case 'f':
                strncpy(filePath, optarg, MAX_FILEPATH_SIZE);
                break;
            case 'r':
                reverseFlag = true;
                break;
            default:
                fprintf(stderr, "Usage: %s [-f <file>] [-h]\n", argv[0]);
                exit(1);
                break;
        }
    }

    int status;

    // if empty string, read from stdin, else read from specified file
    if(strcmp(filePath,"") == 0) {
        status = SortDataStream(reverseFlag, stdin, stdout);
    } else {
        FILE * inputStream = fopen(filePath, "r");
        
        //exit if file doesn't exist
        if (inputStream == NULL) {
            fprintf(stderr, "ERROR: File could not be found\n");
            exit(1);
        }

        status = SortDataStream(reverseFlag, inputStream, stdout);
        fclose(inputStream);
    }

    if (status != 0) {
        fprintf(stderr, "Error: Copy did not complete Successfully\n");
        exit(1);
    }

    return 0;
}

char **GrowArray(char **array, int current_length, int new_length) {
    /* Validate parameters */
    if (array == NULL) {
        return NULL;
    }
    if (new_length <= current_length) {
        return NULL;
    }

    /* Create a new int array that is the requested size */
    char **newArray = (char**)malloc(sizeof(char *) * new_length);
    if (newArray == NULL) {
        return NULL;
    }

    /* Copy the contents from current array to new array */
    for (int i = 0; i < current_length; i++) {
        newArray[i] = array[i];
    }

    /* Free the old array to prevent memory leaks */
    free(array);

    /* Display some status info for debugging purposes */
    fprintf(stderr, "Growing Array: %d -> %d\n", current_length, new_length);

    return newArray;
}

int MyStringCompare(const void *entryA, const void *entryB) {
    char *string1 = *(char**)entryA;
    char *string2 = *(char**)entryB;

    int result = strcmp(string1, string2);

    return result;
}

int MyReverseStringCompare(const void *entryA, const void *entryB) {
    char *string1 = *(char**)entryA;
    char *string2 = *(char**)entryB;

    int result = strcmp(string2, string1);

    return result;
}

int SortDataStream(int reverse, FILE * in, FILE * out) {
    char buffer[READ_BUFFER_SIZE];
    size_t readCount = 0;
    size_t writeCount = 0;

    /* Setup lineArray */
    const size_t INIT_NUM_LINE = 16;
    char ** lineArray = (char**)malloc(sizeof(char*) * INIT_NUM_LINE);
    int lineArrayCapacity = INIT_NUM_LINE;

    if (lineArray == NULL) {
        fprintf(stderr, "Error: Failed to allocate lineArray\n");
        return -1;
    }

    /* Read data from input stream and sort lines in the array */
    int lineCount = 0;
    while (fgets(buffer, READ_BUFFER_SIZE, in) != NULL) {
        readCount = strlen(buffer);

        if (lineCount >= lineArrayCapacity) {
            lineArray = GrowArray(lineArray, lineArrayCapacity, lineArrayCapacity * 2);
            if (lineArray == NULL) {
                fprintf(stderr, "Error: Unable to grow array\n");
                return -1;
            }
            lineArrayCapacity *= 2;
        }

        lineArray[lineCount] = (char*)malloc(sizeof(char) * readCount + 1);
        if (lineArray[lineCount] == NULL) {
            fprintf(stderr, "Error: Unable to allocate memory\n");
            return -1;
        }

        strcpy(lineArray[lineCount], buffer);
        lineCount++;
    }

    /* Sort the lineArray */
    if (reverse == true){
        qsort(lineArray, lineCount, sizeof(char*), MyReverseStringCompare);
    } else {
        qsort(lineArray, lineCount, sizeof(char*), MyStringCompare);
    }

    /* Write the lines array */
    for (int i = 0; i < lineCount; i++) {
        writeCount = fwrite(lineArray[i], sizeof(char), strlen(lineArray[i]), out);

        if (writeCount != strlen(lineArray[i])) {
            fprintf(stderr, "Error: An error occurred while writing to output stream\n");
            return -1;
        }
    }

    /* Cleanup line array */
    for (int i = 0; i < lineCount; i++) {
        free(lineArray[i]);
    }
    free(lineArray);

    return 0;
}