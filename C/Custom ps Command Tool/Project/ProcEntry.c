/* 
 * Author: Stephen Richardson
 * Date: 12/3/2020 3:43 PM MST
 * Description: Implmentation of the ProcEntry header file.
 *          A struct to hold information from a processes statistics
 *          as well as the path to that statistic.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ProcEntry.h"

ProcEntry * CreateProcEntry(void) {
    ProcEntry * newEntry = (ProcEntry*)malloc(sizeof(ProcEntry));
    
    //if failed to allocate, return null
    if (newEntry == NULL) {
        return NULL;
    }

    //intialize all variables to 0 or NULL
    newEntry->pid = 0;
    newEntry->comm = NULL;
    newEntry->state = '\0';
    newEntry->utime = 0;
    newEntry->stime = 0;
    newEntry->proc = 0;
    newEntry->path = NULL;
    
    return newEntry;
}

ProcEntry * CreateProcEntryFromFile(const char statFile[]) {
    FILE * datafile;
    ProcEntry * newEntry;
    
    //make sure file opens correctly
    datafile = fopen(statFile, "r");
    if (datafile == NULL) {
        perror("fopen");
        return NULL;
    }

    //allocate new entry
    newEntry = (ProcEntry *)malloc(sizeof(ProcEntry));
    if (newEntry == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate ProcEntry\n");
        fclose(datafile);
        return NULL;
    }

    //allocate new string and save the path
    newEntry->path = (char *)malloc(sizeof(char) * (strlen(statFile) + 1));
    if(newEntry->path == NULL) {
        fprintf(stderr, "ERROR: failed to allocate path\n");
        DestroyProcEntry(newEntry);
        fclose(datafile);
        return NULL;
    }
    strncpy(newEntry->path, statFile, strlen(statFile) + 1);

    //read through file up to the 39th item and save them to the relevant variables
    //return null if read incorrectly.
    int itemsread = 0;
    for(int i = 1; i <= 39; i++) {
        switch (i) {
            case 1: ;
                //read in pid %d
                itemsread = fscanf(datafile, " %d", &newEntry->pid);
                if (itemsread != 1) {
                    fprintf(stderr, "ERROR: failed to read in PID\n");
                    DestroyProcEntry(newEntry);
                    fclose(datafile);
                    return NULL;
                }
                break;
            case 2: ;
                //read in comm %s
                char tempString[500];
                itemsread = fscanf(datafile, " %500s", tempString);
                if (itemsread != 1) {
                    fprintf(stderr, "ERROR: failed to read in Comm\n");
                    DestroyProcEntry(newEntry);
                    fclose(datafile);
                    return NULL;
                }

                //allocate new string and save the comm
                newEntry->comm = (char *)malloc(sizeof(char) * (strlen(tempString) + 1));
                if(newEntry->comm == NULL) {
                    fprintf(stderr, "ERROR: failed to allocate Comm\n");
                    DestroyProcEntry(newEntry);
                    fclose(datafile);
                    return NULL;
                }
                strncpy(newEntry->comm, tempString, strlen(tempString) + 1);
                            break;
            case 3: ;
                //read in state %c
                itemsread = fscanf(datafile, " %c", &newEntry->state);
                if (itemsread != 1) {
                    fprintf(stderr, "ERROR: failed to read in state\n");
                    DestroyProcEntry(newEntry);
                    fclose(datafile);
                    return NULL;
                }
                break;
            case 14:
                //read in utime %lu
                itemsread = fscanf(datafile, " %lu", &newEntry->utime);
                if (itemsread != 1) {
                    fprintf(stderr, "ERROR: failed to read in utime\n");
                    DestroyProcEntry(newEntry);
                    fclose(datafile);
                    return NULL;
                }
                break;
            case 15:
                //read in stime %lu
                itemsread = fscanf(datafile, " %lu", &newEntry->stime);
                if (itemsread != 1) {
                    fprintf(stderr, "ERROR: failed to read in stime\n");
                    DestroyProcEntry(newEntry);
                    fclose(datafile);
                    return NULL;
                }
                break;
            case 39:
                //read in processor %d
                itemsread = fscanf(datafile, " %d", &newEntry->proc);
                if (itemsread != 1) {
                    fprintf(stderr, "ERROR: failed to read in processor number\n");
                    DestroyProcEntry(newEntry);
                    fclose(datafile);
                    return NULL;
                }
                break;
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 38:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 24:
                //ignore %d
                fscanf(datafile, " %*d");
                break;
            default:
                //otherwise, ignore %lu
                fscanf(datafile, " %*u");
                break;
       }
    }

    fclose(datafile);
    return newEntry;
}

void DestroyProcEntry(ProcEntry * entry) {
    //free comm, path, and then entry
    if (entry == NULL) {return;}
    free(entry->comm);
    free(entry->path);
    free(entry);
}

void PrintProcEntry(ProcEntry *entry)
{
    if(entry == NULL) {return;}
     unsigned long int utime = entry->utime / sysconf(_SC_CLK_TCK);
     unsigned long int stime = entry->stime / sysconf(_SC_CLK_TCK);
     fprintf(stdout, "%7d %5c %5lu %5lu %4d %-25s %-20s\n",
             entry->pid,
             entry->state,
             utime,
             stime,
             entry->proc,
             entry->comm,
             entry->path);
}