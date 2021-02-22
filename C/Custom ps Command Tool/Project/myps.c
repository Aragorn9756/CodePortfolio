/* 
 * Author: Stephen Richardson
 * Date: 12/3/2020 3:34 PM
 * Description: simplified version of the ps command. Navigates to
 *          PID directory and saves 6 fields from each process into
 *          a ProcEntry struct. Outputs the fields from each process.
 */

#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <errno.h>
#include "ProcEntry.h"

#define MAX_PATH_LENGTH 4096

static int procFilter (const struct dirent *current) {
    if ((current->d_type != DT_DIR) || !isdigit(current->d_name[0])) {
        return 0;
    }
    return 1;
}

static int pidSort(const void *a, const void *b)
{
     ProcEntry *f = *(ProcEntry **)a;
     ProcEntry *s = *(ProcEntry **)b;
     int rval = f->pid - s->pid;
     return rval;
}

static int commSort(const void *a, const void *b)
{
     ProcEntry *f = *(ProcEntry **)a;
     ProcEntry *s = *(ProcEntry **)b;
     return strcmp(f->comm, s->comm);
}

int main (int argc, char * argv[]) {
    
    struct dirent **dirScan;
    int numDirs;
    int opt;
    int sortChosen = 0; // 0 if false, 1 if true
    int zOnly = 0; // 0 if false, 1 if true
    char sortType = 'p'; // p for pid sort, c for comm sort
    char dirPath[MAX_PATH_LENGTH];
    strcpy(dirPath,"/proc");

    while ((opt = getopt(argc, argv, "pczhd:")) != -1) {
        switch (opt){
            case 'h':
                //display help message
                fprintf(stdout, "Usage: %s [-d <path>] [-p] [-c] [-z] [-h]\n", argv[0]);
                fprintf(stdout, "\t-d <path> Directory containing proc entries (default: /proc)\n");
                fprintf(stdout, "\t-p        Display proc entries sorted by pid (default)\n");
                fprintf(stdout, "\t-c        Display proc entries sorted by command lexicographically\n");
                fprintf(stdout, "\t-z        Display ONLY proc entries in the zombie state\n");
                fprintf(stdout, "\t-h        Display this help message\n");
                exit(0);
                break;
            case 'p':
                // sort processes by PID
                //if sort type already specified, print usage and exit
                if (sortChosen == 1) {
                    printf("Enter either -p or -c, not both\n");
                    return 0;
                }
                //set sort type and indicate sort chosen
                sortChosen = 1;
                sortType = 'p';
                break;
            case 'c':
                //sort processes by comm
                //if sort type already specified, print usage and exit
                if (sortChosen == 1) {
                    printf("Enter either -p or -c, not both\n");
                    return 0;
                }
                //set sort type and indicate sort chosen
                sortChosen = 1;
                sortType = 'c';
                break;
            case 'z':
                // only show processes in zombie state
                zOnly = 1;
                break;
            case 'd':
                //copy specified directory to dirPath
                strncpy(dirPath, optarg, MAX_PATH_LENGTH);
                break;
            default:
                fprintf(stderr, "Usage: %s [-d <path>] [-p] [-c] [-z] [-h]\n", argv[0]);
                fprintf(stderr, "\t-d <path> Directory containing proc entries (default: /proc)\n");
                fprintf(stderr, "\t-p        Display proc entries sorted by pid (default)\n");
                fprintf(stderr, "\t-c        Display proc entries sorted by command lexicographically\n");
                fprintf(stderr, "\t-z        Display ONLY proc entries in the zombie state\n");
                fprintf(stderr, "\t-h        Display this help message\n");
                exit(1);
                break;
        }
    }

    //scan directory and find proc directories.
    errno = 0;
    numDirs = scandir(dirPath, &dirScan, procFilter, alphasort);
    //validate scan
    if (numDirs < 0) {
        perror("scandir: ");
        exit(1);
    }
    if (numDirs == 0) {
        fprintf(stdout, "No processes found\n");
        return 0;
    }

    /* DEBUG display proc entries found 
    for (int i = 0; i < numDirs; i++) {
        fprintf(stdout, "%s\n", dirScan[i]->d_name);
    }
    */

    //create and populate array of procEntrys using dirScan
    ProcEntry ** myprocs = (ProcEntry **) (malloc(sizeof(ProcEntry *) * numDirs));

    char procDir[MAX_PATH_LENGTH];
    int maxPIDLength; //max length of pid name while leaving room path to pid and following /stat
    maxPIDLength = MAX_PATH_LENGTH - strlen(dirPath) - 7;
    for (int i = 0; i < numDirs; i++) {
        // put together path to process stat file
        strcpy(procDir, dirPath);
        strcat(procDir, "/");
        strncat(procDir, dirScan[i]->d_name, maxPIDLength);
        strcat(procDir, "/stat");
        
        myprocs[i] = CreateProcEntryFromFile(procDir);

        
        // validate ProcEntry creation
        if (myprocs[i] == NULL) {
            fprintf(stderr, "ERROR: ProcEntry creation failed. Exiting program\n");
            for (int j = 0; j < numDirs; j++)  {
                free(dirScan[j]);
                DestroyProcEntry(myprocs[i]);
            }
            free(dirScan);
            free(myprocs);
            exit(3);
        }
        
    }
    // clean up dirScan
    for (int i = 0; i < numDirs; i++)  {
        free(dirScan[i]);
    }
    free(dirScan);
    
    //sort myprocs using specified sorting method
    if (sortType == 'p') {
        qsort(myprocs, numDirs, sizeof(ProcEntry *), pidSort);
    } else if (sortType == 'c') {
        qsort(myprocs, numDirs, sizeof(ProcEntry *), commSort);
    } else {
        fprintf(stderr, "ERROR: impossible sort chosen\n");
        for (int i = 0; i < numDirs; i++)  {
            DestroyProcEntry(myprocs[i]);
        }
        free(myprocs);
        exit(4);
    }

    //display results
    fprintf(stdout,"%7s %5s %5s %5s %4s %-25s %-20s\n",
            "PID","STATE","UTIME","STIME","PROC","CMD","STAT_FILE");
    for(int i = 0; i < numDirs; i++) {
        if (zOnly == 1 && myprocs[i]->state != 'Z') {
            continue;
        }
        PrintProcEntry(myprocs[i]);
    }

    //clean up myprocs
    for (int i = 0; i < numDirs; i++)  {
        DestroyProcEntry(myprocs[i]);
    }
    free(myprocs);

    return 0;
}
