/* 
 * File: ContactNode.c
 * Author: Stephen Richardson
 * Date: 10/24/20
 * Description: implementations of the functions declared in
 *    in ContactNode.h
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "ContactNode.h"

ContactNode* CreateContactNode(char name[], char phoneNum[]) {
   ContactNode* thisNode = (ContactNode*)malloc(sizeof(ContactNode));

   // make sure it allocated correctly
   if(thisNode == NULL) {
      return NULL;
   }

   // copy parameters into corresponding variables
   strncpy(thisNode->contactName, name, CONTACT_FIELD_SIZE);
   strncpy(thisNode->contactPhoneNum, phoneNum, CONTACT_FIELD_SIZE);
   thisNode->nextNodePtr = NULL;

   return thisNode;
}

int InsertContactAfter(ContactNode* nodeInList, ContactNode* newNode) {
   ContactNode* tempPtr = NULL;

   // make sure neither node is null
   if (nodeInList == NULL || newNode == NULL) {
      return -1;
   }

   tempPtr = nodeInList->nextNodePtr;
   nodeInList->nextNodePtr = newNode;
   newNode->nextNodePtr = tempPtr;

   return 0;
}

ContactNode* GetNextContact(ContactNode* nodeInList) {
   // validate parameter
   if(nodeInList == NULL) {
      return NULL;
   }

   return nodeInList->nextNodePtr;
}

void PrintContactNode(ContactNode* thisNode) {
   //validate parameter
   if (thisNode == NULL) {
      return;
   }

   printf("Name: %s\n", thisNode->contactName);
   printf("Phone number: %s\n\n", thisNode->contactPhoneNum);
}

void DestroyContactNode(ContactNode* thisNode) {
   //validate parameter
   if(thisNode == NULL) {
      return;
   }
   free(thisNode);
}