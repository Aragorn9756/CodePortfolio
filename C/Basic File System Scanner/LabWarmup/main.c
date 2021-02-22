/* 
 * Author: Luke Hindman Modified by Stephen Richardson
 * Date: Thu 05 Nov 2020 08:10:44 AM PST  Modified 11/16/2020
 * Description:  Adapted from the Simple Directory Lister Mark II example
 *    provided in the libc manual.
 * https://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister-Mark-II.html
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAX_PATH_LENGTH 4096

//used to cast intentionally unused variables to void to please compiler
#define UNUSED(x) (void)x

/* function to leave dir unsorted */
int noSort(const struct dirent** entryA, const struct dirent **entryB) {
    UNUSED(entryA);
    UNUSED(entryB);
    return 0;
}

static int defaultFilter (const struct dirent *current) {
    UNUSED(current);
    return 1;
}


int main (int argc, char * argv[]) {
    struct dirent **eps;
    int n;
    int opt;

    /* Declare sortFunction pointer*/
    /* This is basically a variable that holds a pointer to a function with
     * the variable name being in the first (). function pointer declarations MUST 
     * include the arguments and return types. ALL functions that can be pointed
     * to with this var MUST have the same arguments and return type.
     * this var is molded to fit the alphasort function used by scandir */
    int (*sortFunction)(const struct dirent**, const struct dirent **);
    sortFunction = noSort;

    /* Declare and initialize filterFunction pointer */
    //same kind of var as sortFunction
    int (*filterFunction)(const struct dirent *);
    filterFunction = defaultFilter;

    /* Declare dirPath and set default to current directory */
    char dirPath[MAX_PATH_LENGTH];
    strcpy(dirPath, "./");

    /* Use getopt() to process command line arguments */
    /* The ':' tells getopt that if -d is found, there MUST follow a string
     * argument. other arguments may be placed anywhere within the quotes
     * as long as they are not between the d and the ':'. 
     * get opt also allows the user to type the args in any order in the 
     * command line. */
    while ( (opt = getopt(argc, argv, "sd:")) != -1) {
        switch(opt) {
            case 'd':
                strncpy(dirPath, optarg, MAX_PATH_LENGTH);
                break;
            case 's':
                sortFunction = alphasort;
                break;
            default:
                fprintf(stderr, "Error: Invalid Option Specified\n");
                fprintf(stderr, "Usage: %s [-d <path>] \n", argv[0]);
                break;
        }
    }

    /* scan dirpath */
    errno = 0;   
    n = scandir (dirPath, &eps, filterFunction, sortFunction);

    /* validate directory was opened successfully */
    if (n < 0) {
        perror("scandir: ");
        exit(1);
    }

    int cnt;
    for (cnt = 0; cnt < n; ++cnt) {
        fprintf(stdout,"%s\n", eps[cnt]->d_name);
    }

    /* Cleanup memory allocated by scandir */
    /* eps is array created by scandir holding each file 
     * walking through array and freeing each index will clean up
     * memory leaks properly (discovered using scandir manpage */
    for (int i = 0; i < n; i++) {
        free (eps[i]);
    }
    free (eps);

    return 0;
}
