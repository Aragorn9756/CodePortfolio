/*
 * File: Main.c
 * Author: Stephen Richardson
 * Date: 24 Oct, 2020 5:00 PM MST
 * Description: Takes user input to create 3 Contact nodes into a
 *    Linked List. Prints out the nodes and runs valgrind to check for 
 *    memory leaks
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "ContactNode.h"

/*
 * BufferPurge: Remove all remaining charaacters
 *    from the input buffer
 */
void BufferPurge(void) {
    char c = getchar();
   while(c != '\n' && c != EOF) {
      c = getchar();
    }
}

int main(void) {

   //variables
   const int NUM_CONTACTS = 3;
   int rc = 0;
   char name[CONTACT_FIELD_SIZE];
   char phoneNum[CONTACT_FIELD_SIZE];
   ContactNode* listHead = NULL;
   ContactNode* listTail = NULL;
   ContactNode* tempNodePtr = NULL;

   //create contacts
   for(int i = 0; i < NUM_CONTACTS; i++) {
      printf("Person %d\nEnter name:\n", i + 1);
      fgets(name, CONTACT_FIELD_SIZE, stdin);
      //remove any hanging return chars and leftover characters
      if (name[strlen(name) - 1] == '\n') {
         name[strlen(name) - 1] = '\0';
      }
      //otherwise, must be extra long, so need to clear buffer
      else{BufferPurge();}
      
      printf("Enter phone number:\n");
      fgets(phoneNum, CONTACT_FIELD_SIZE, stdin);
      //remove any hanging return chars and leftover characters
      if (phoneNum[strlen(phoneNum) - 1] == '\n') {
         phoneNum[strlen(phoneNum) - 1] = '\0';
      }
      //otherwise, must be extra long, so need to clear buffer
      else{BufferPurge();}

      printf("You Entered: %s, %s\n\n", name, phoneNum);

      //create node and add to list
      tempNodePtr = CreateContactNode(name, phoneNum);
      //if null, exit the program
      if (tempNodePtr == NULL) {
         printf("Failed to allocate memory for the contact. Exiting program.\n");
         exit(1);
      }
      //if first node, initialize head and tail pointers.
      if(i == 0) {
         listHead = tempNodePtr;
         listTail = tempNodePtr;
      }
      //otherwise, add to end of the list and update tail
      else {
         rc = InsertContactAfter(listTail, tempNodePtr);
         listTail = tempNodePtr;
         //make sure insertion was successful
         if (rc < 0) {
            printf("Error: unable to insert node into list...\n");
            PrintContactNode(tempNodePtr);
            exit(1);
         }
      }
   }

   //print out list
   printf("CONTACT LIST\n");
   tempNodePtr = listHead;
   while(tempNodePtr != NULL) {
      PrintContactNode(tempNodePtr);
      tempNodePtr = GetNextContact(tempNodePtr);
   }

   //clear contacts
   tempNodePtr = listHead;
   while(tempNodePtr != NULL) {
      listHead = tempNodePtr;
      tempNodePtr = GetNextContact(listHead);
      DestroyContactNode(listHead);
      listHead = tempNodePtr;
   }

   return 0;
}