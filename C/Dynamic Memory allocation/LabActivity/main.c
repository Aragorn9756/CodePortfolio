/* 
 * File: main.c
 * Author: Stephen Richardson
 * Date: 11/2/2020 2:11 PM MST
 * Description: Play a game of M.A.S.H. using linked lists
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "DataNode.h"

enum DataBase{Home, Female, Male, Job, Trans, City};

void InitDatabase( DataNode* database[]) {
   //string lists
   char* HomeList[] = {"trailer", "mansion", "fixer-upper", "high-end apartment",
            "low-end apartment", "suburban home", "cabin", "homeless shelter"};
   char* MaleList[] = {"Frederick", "Jose", "Jean de Baptiste", "Bob", "John", "Moe"};
   char* FemaleList[] = {"Peggy Sue", "Karen", "Agatha", "Annicka", "La-A", "Lafonda"};
   char* OccupationList[] = {"surgeon", "lawyer", "developer", "teacher", "garbage man",
            "paint watcher", "police officer", "crossing guard"};
   char* TransportationList[] = {"fly your private jet", "drive a sports car", 
            "drive an SUV", "ride the bus", "bike",
            "skate", "Walk", "ride your scooter", "longboard"};
   char* HometownList[] = {"Salt Lake City", "Seattle", "Tokyo", "Melbourne",
            "Boston", "Houston", "Anchorage", "Beijing", "Dubai"};
   
   //fill array
   database[Home] = BuildDataList(HomeList, 8);
   database[Female] = BuildDataList(FemaleList, 6);
   database[Male] = BuildDataList(MaleList, 6);
   database[Job] = BuildDataList(OccupationList, 8);
   database[Trans] = BuildDataList(TransportationList, 9);
   database[City] = BuildDataList(HometownList, 9);
}

int main(void) {
   const int MAX_NAME_SIZE = 30;
   char playerName[30];

   //create and initialize array of dataNodes
   DataNode* database[6];
   InitDatabase(database);

   srand(time(0));
   
   // print out database
   printf("---------------------------------------- Future Possibilities");
   printf(" Database ----------------------------------------\n");
   printf("Home List: ");
   PrintDataList(database[Home]);
   printf("Female Spouse List: ");
   PrintDataList(database[Female]);
   printf("Male Spouse List: ");
   PrintDataList(database[Male]);
   printf("Occupation List: ");
   PrintDataList(database[Job]);
   printf("Transportation List: ");
   PrintDataList(database[Trans]);
   printf("Hometown List: ");
   PrintDataList(database[City]);
   printf("-------------------------------------------------------------");
   printf("--------------------------------------------------\n\n");

   //get player name
   printf("Please enter your name: ");
   fgets(playerName, MAX_NAME_SIZE, stdin);
   int length = strlen(playerName);

   //trim off possible newline char and 
   if (playerName[length - 1] == '\n') {
      playerName[length - 1] = '\0';
   }
   else{
      char c = getchar();
      while(c != '\n' && c != EOF) {
      c = getchar();
      }
   }

   //Start game! populate randomly generated spots as they are reached
   printf("\n\n\nWelcome %s, this is your future...\n", playerName);
   printf("You will marry ");
   //randomly choose 0 or 1 to choose male or female spouse
   // 0 for male, 1 for female
   int maleOrFemale = rand() % 2;
   if(maleOrFemale == 0) {
   PrintDataNode(GetRandomDataNode(database[Male]));
   }
   else {
      PrintDataNode(GetRandomDataNode(database[Female]));
   }
   printf(" and live in a ");
   PrintDataNode(GetRandomDataNode(database[Home]));
   //get random number between 0 and 20 for years married
   int yearsMarried = rand() % 20;
   printf(".\nAfter %d years of marriage, you will finally get ", yearsMarried);
   printf("your dream job of being a ");
   PrintDataNode(GetRandomDataNode(database[Job]));
   printf(".\nYour family will move to a ");
   PrintDataNode(GetRandomDataNode(database[Home]));
   printf(" in ");
   PrintDataNode(GetRandomDataNode(database[City]));
   printf(" where you will ");
   PrintDataNode(GetRandomDataNode(database[Trans]));
   printf(" to work each day.\n");
   
   //deallocate lists
   for (int i = Home; i <= City; i++){
      DestroyDataList(database[i]);
   }
   return 0;
}