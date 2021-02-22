/*
 * File: main.c
 * Author: Stephen Richardson
 * Date: 11/7/20 8:12 PM
 * Description: Read song data from a CSV file into a Song struct
 *       and save the songs to a dynamically alocated list.
 *       Command line arguments specify CSV file and length of list
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "Song.h"

// argc is number of arguments passsed in. filename (main.c)
// counts as 1 argument
// argv is an array of the arguments passed in, saved as strings.
int main(int argc, char * argv[]) {

   //if insufficient number of args
   if (argc != 3) {
      fprintf(stderr, "Usage: %s <catalog.csv> <size>\n", argv[0]);
      exit(1);
   }   

   char * userFilename = argv[1];
   char * userSize = argv[2];

   /* Open and validate file */
   errno = 0;
   FILE * dataFile = fopen(userFilename, "r");
   if(dataFile == NULL) {
      perror("fopen");
      exit(1);
   }

   //convert and validate size from string to int
   int listSize = 0;
   int rc = sscanf(userSize, "%d", &listSize);
   if (rc != 1){
      fprintf(stderr, "Error: Please enter an Integer value for size\n");
      exit(1);
   }

   if (listSize <= 0) {
      fprintf(stderr, "Error: list size must be greater than 0"); 
      exit(1);
   }

   //dynamically allocate array of song pointers
   // same as Song * songlist[]
   Song ** songlist = (Song **)malloc(sizeof(Song *) * listSize);
   if (songlist == NULL) {
      fprintf(stderr, "Error: Unable to allocate memory for song list\n");
      exit(1);
   }

   /* temp variables for holding CSV fields */
   const int MAX_FIELD_SIZE = 256;
   char artistField[MAX_FIELD_SIZE];
   char albumField[MAX_FIELD_SIZE];
   char titleField[MAX_FIELD_SIZE];
   int durationField;
   
   int songCount = 0;
   int numRead = 0;

   // read songs from file and add to array until end of file
   //    or list size
   while (!feof(dataFile) && songCount < listSize) {
      //[^,] means read until a comma, but not including the comma
      numRead = fscanf(dataFile, "%255[^,],%255[^,],%255[^,],%d\n", artistField, albumField,
               titleField, &durationField);
      
      //if we read correctly, add to song list else print error to console
      if (numRead == 4) {
         //increment song count after Song struct to array
         songlist[songCount++] = CreateSong(artistField, albumField, titleField, durationField);
      } else {
         fprintf(stderr, "Error: read %d of 4 parameters when processing CSV\n", numRead);
      }
   }

   //close files and print results
   fclose(dataFile);

   printf("Successfully loaded %d songs\n", songCount);

   /* Display the songlist and free memory immediately afterwards*/
   for (int i = 0; i < songCount; i++){
      PrintSong(songlist[i]);
      DestroySong(songlist[i]);
   }

   free(songlist);

   return 0;
}