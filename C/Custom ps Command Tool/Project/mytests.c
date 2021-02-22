#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ProcEntry.h"

int TestBlankEntryCreation(void) {
   int numFails = 0;
   
   ProcEntry * testEntry = CreateProcEntry();

   if (testEntry == NULL) {
      fprintf(stderr, "ERROR: Entry allocation failed\n");
      return 1;
   }

   //make sure all variables are correctly initialized
   if (testEntry->pid != 0) {numFails++;}
   if (testEntry->comm != NULL) {numFails++;}
   if (testEntry->state != '\0') {numFails++;}
   if (testEntry->utime != 0) {numFails++;}
   if (testEntry->stime != 0) {numFails++;}
   if (testEntry->proc != 0) {numFails++;}
   if (testEntry->path != NULL) {numFails++;}

   DestroyProcEntry(testEntry);

   //results
   if (numFails > 0) {
      fprintf(stderr, "ERROR: One or more variables failed to initialize correctly\n");
   }

   return numFails;
}

int testBasicCreateFromFile(void){
   int numFails = 0;
   ProcEntry * testEntry;
   char testProcess[] = "/proc/1/stat";

   //test with incorrect input
   testEntry = CreateProcEntryFromFile(" ");
   if (testEntry != NULL) {
      numFails++;
      DestroyProcEntry(testEntry);
   }

   //test with correct input
   testEntry = CreateProcEntryFromFile(testProcess);
   if(testEntry == NULL) {
      fprintf(stderr, "ERROR: Failed to read file\n");
      numFails++;
      return numFails;
   }
   PrintProcEntry(testEntry);
   DestroyProcEntry(testEntry);
   return numFails;
}

int Test100Processes (void) {
   int numFails = 0;
   ProcEntry * procArray[100];
   char pathStart[] = "/proc/";
   char pathEnd[] = "/stat";
   char fullPath[50];
   char intStr[10];

   //add 100 processes to the array
   for (int i = 1; i <= 100; i++) {
      //put path together
      sprintf(intStr, "%d", i);
      strcpy(fullPath, pathStart);
      strcat(fullPath, intStr);
      strcat(fullPath, pathEnd);
      procArray[i - 1] = CreateProcEntryFromFile(fullPath);
   }

   //read print and clear processes
   for (int i = 0; i < 100; i++) {
      if (procArray[i] == NULL) {
         numFails++;
      }
      else {
         PrintProcEntry(procArray[i]);
         DestroyProcEntry(procArray[i]);
      }
   }
   return numFails;
}

int main(void) {

   int numFails = 0;

   numFails += TestBlankEntryCreation();
   numFails += testBasicCreateFromFile();
   numFails += Test100Processes();

   if (numFails == 0) {
      fprintf(stderr, "No news is good news!\n");
   }

   return 0;
}