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
#include <stdbool.h>

#define MAX_PATH_LENGTH 4096

//used to cast intentionally unused variables to void to please compiler
#define UNUSED(x) (void)x

/* a simple help menu to define usage */
void printHelp (char * currdir) {
    printf("Usage: %s [-d <path>] [-s] [-r] [-f OR -a]\n", currdir);
    printf("\t-d <path> Directoryto list the contents of\n");
    printf("\t-a        Display all files, including hidden files\n");
    printf("\t-f        Display only regular files\n");
    printf("\t-r        Display entries alphabetically in descending order\n");
    printf("\t-s        Display entries alphabetically in ascending order\n");
}

/* Sort directory in reverse alphabetic order */
int reverseSort(const struct dirent** entryA, const struct dirent **entryB) {
    //return the inverse of alphasort
    return alphasort(entryA, entryB) * -1;
}

/* function to leave dir unsorted */
int noSort(const struct dirent** entryA, const struct dirent **entryB) {
    UNUSED(entryA);
    UNUSED(entryB);
    return 0;
}

/* Return 1 so all files are shown */
static int showAll (const struct dirent *current) {
    UNUSED(current);
    return 1;
}

/* only show regular files i.e. entries with d_type dt_reg (see dirent struct definition) */
static int showFilesOnly (const struct dirent *current) {
    if (current->d_type != DT_REG) {
        return 0;
    }
    return 1;
}

/* Only show non-hidden files. The names of hidden files begins with '.' */
static int defaultFilter (const struct dirent *current) {
    if (current->d_name[0] == '.') {
        return 0;
    }
    return 1;
}

int main (int argc, char * argv[]) {
    struct dirent **eps;
    int n;
    int opt;
    bool filter = false;

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
    while ( (opt = getopt(argc, argv, "hsrd:af")) != -1) {
        switch(opt) {
            case 'h':
                /* print help menu and exit program */
                printHelp(argv[0]);
                exit(0);
            case 'd':
                /* define directory */
                strncpy(dirPath, optarg, MAX_PATH_LENGTH);
                break;
            case 's':
                /* sort directory alphabetically (ascii) */
                sortFunction = alphasort;
                break;
            case 'r':
                /* sort directory reverse alphabetically (ascii) */
                sortFunction = reverseSort;
                break;
            case 'a':
                /* show all files, including hidden */
                //if filter already selected, exit program
                if (filter == true) {
                    fprintf(stderr, "ERROR: multiple filters Selected\n");
                    fprintf(stderr, "Usage: %s [-a OR -f]\n", argv[0]);
                    exit(1);
                }
                filter = true;
                filterFunction = showAll;
                break;
            case 'f':
                /* Only show regular files */
                //if filter already selected, exit program
                if (filter == true) {
                    fprintf(stderr, "ERROR: multiple filters Selected\n");
                    fprintf(stderr, "Usage: %s [-a || -f]\n", argv[0]);
                    exit(1);
                }
                filter = true;
                filterFunction = showFilesOnly;
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
