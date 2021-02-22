/* 
 * File: mytests.c
 * Author: Stephen Richardson
 * Date: 10/31/2020 6:36 PM MST
 * Description: Comprehensive test cases for the DataNode.c 
 *       functions
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DataNode.h"

/* TEST FUNCTIONS */

// create/destroy node tests
int BasicCreateDestroyTest (void) {
   char testName[] = "Basic Create/Destroy test";
   DataNode* testData = CreateDataNode("Hoping this works");
   if (testData == NULL){
      fprintf(stderr, "%s failed\n", testName);
      return 1;
   }
   DestroyDataNode(testData);
   fprintf(stderr, "%s passed\n", testName);
   return 0;
}

int NullStringCreateTest (void){
   char testName[] = "Null String Create Test";
   DataNode* nullNode = CreateDataNode(NULL);
   if (nullNode != NULL) {
      fprintf(stderr, "%s failed\n", testName);
      DestroyDataNode(nullNode);
      return 1;
   }
   fprintf(stderr, "%s passed\n", testName);
   return 0;
}

int LongStringCreateTest (void) {
   char testName[] = "Long String Create Test";
   
   //create long string
   int lnStrLength = 1024 * 1024;
   char longString[lnStrLength];

   //populate longString with '.'
   for (int i = 0; i < lnStrLength; i++) {
      longString[i] = '.';
   }

   //add null to the end
   longString[lnStrLength - 1] = '\0';

   DataNode* longNode = CreateDataNode(longString);
   if (longNode == NULL) {
      fprintf(stderr, "%s failed\n", testName);
      return 1;
   }
   
   DestroyDataNode(longNode);
   fprintf(stderr, "%s passed\n", testName);
   return 0;
}

// GetNode tests

int GetNodeGeneralTest(void) {
   char testName[] = "GetNode general Test";
   DataNode* newNode = CreateDataNode("testing");
   DataNode* pointedTo = CreateDataNode("Passed");
   newNode->nextNodePtr = pointedTo;
   
   //should get a pointer pointing to PointedTo
   if (GetNextDataNode(newNode) != pointedTo) {
      fprintf(stderr, "%s failed\n", testName);
      DestroyDataNode(newNode);
      DestroyDataNode(pointedTo);
      return 1;
   }

   DestroyDataNode(newNode);
   DestroyDataNode(pointedTo);
   fprintf(stderr, "%s passed\n", testName);
   return 0;
}

int SendNullGetNodeTest(void) {
   char testName[] = "send NULL node GetNode Test";
   DataNode* EmptyNode = NULL;

   //should recieve a Null back
   if (GetNextDataNode(EmptyNode) != NULL){
      fprintf(stderr, "%s failed\n", testName);
      return 1;
   }

   fprintf(stderr, "%s passed\n", testName);
   return 0;
}

int ReturnNULLGetNodeGeneralTest(void) {
   char testName[] = "node pointing to NULL GetNode Test";
   DataNode* endNode = CreateDataNode("Points to nothing");

   // new nodes point to null by default
   if (GetNextDataNode(endNode) != NULL) {
      fprintf(stderr, "%s failed\n", testName);
      DestroyDataNode(endNode);
      return 1;
   }

   fprintf(stderr, "%s passed\n", testName);
   DestroyDataNode(endNode);
   return 0;
}

// SetNode tests

int SetNextNodeGeneralTest (void) {
   char testName[] = "SetNextDataNode general test";
   DataNode* nodeInList = CreateDataNode("original");
   DataNode* newNode = CreateDataNode("newNode");

   SetNextDataNode(nodeInList, newNode);

   // nodeInList should point to newNode
   if (nodeInList->nextNodePtr != newNode) {
      fprintf(stderr, "%s failed\n", testName);
      DestroyDataNode(nodeInList);
      DestroyDataNode(newNode);
      return 1;
   }

   fprintf(stderr, "%s passed\n", testName);
   DestroyDataNode(nodeInList);
   DestroyDataNode(newNode);
   return 0;
}

int NULLOriginalSetNextNodeTest (void) {
   char testName[] = "SetNextDataNode with NULL original test";
   DataNode* nodeInList = NULL;
   DataNode* newNode = NULL;
   int rc;

   rc = SetNextDataNode(nodeInList, newNode);

   //should receive a -1 return code
   if (rc != -1) {
      fprintf(stderr, "%s failed\n", testName);
      return 1;
   }

   fprintf(stderr, "%s passed\n", testName);
   return 0;


}

int SetNextNodeToNULLTest (void) {
   char testName[] = "SetNextDataNode pointing to NULL test";
   DataNode* nodeInList = CreateDataNode("original");
   DataNode* newNode = NULL;
   int rc;

   rc = SetNextDataNode(nodeInList, newNode);

   //should receive a 0 error code and nodeInList pointing to NULL
   if (rc != 0 || nodeInList->nextNodePtr != NULL) {
      fprintf(stderr, "%s failed\n", testName);
      DestroyDataNode(nodeInList);
      return 1;
   }

   fprintf(stderr, "%s passed\n", testName);
   DestroyDataNode(nodeInList);
   return 0;
}

// *****insert after test*****
// tests to make sure function handles receiving NULL nodes in either spot,
// inserts correctly at end of list, and inserts correctly between 2 nodes
int InsertDataNodeAfterTest(void) {
   char testName[] = "InsertDataNodeAfter test";
   DataNode* firstNode = NULL;
   DataNode* secondNode = CreateDataNode("second node");
   DataNode* nodeToInsert = NULL;
   int totalErrors = 0;
   int rc;

   //test null in both spots
   rc = InsertDataNodeAfter(firstNode, nodeToInsert);
   if (rc != -1) {
      fprintf(stderr, "%s failed at both nodes NULL\n", testName);
      totalErrors++;
   }

   //test NULL in first spot
   rc = InsertDataNodeAfter(firstNode, secondNode);
   if (rc != -1) {
      fprintf(stderr, "%s failed at first node NULL\n", testName);
      totalErrors++;
   }

   //test NULL in second spot
   firstNode = CreateDataNode("I'm number one!");
   rc = InsertDataNodeAfter(firstNode, nodeToInsert);
   if (rc != -1) {
      fprintf(stderr, "%s failed at second node NULL\n", testName);
      totalErrors++;
   }

   //test adding to end. all nodes currently have NULL nextNodePtrs
   //result should be rc = 0, first points to insert and insert points to NULL
   nodeToInsert = CreateDataNode("I'm special");
   rc = InsertDataNodeAfter(firstNode, nodeToInsert);
   if ((rc != 0) || (firstNode->nextNodePtr != nodeToInsert) ||
                  (nodeToInsert->nextNodePtr != NULL)) {
      fprintf(stderr, "%s failed at inserting on the end\n", testName);
      totalErrors++;
   }

   //test adding nodeToInsert between first and second nodes.
   //results should be first->insert->second->null and rc = 0
   firstNode->nextNodePtr = secondNode;
   rc = InsertDataNodeAfter(firstNode, nodeToInsert);
   //must meet all above results
   if ((rc != 0) || (firstNode->nextNodePtr != nodeToInsert ||
            nodeToInsert->nextNodePtr != secondNode)) {
      fprintf(stderr, "%s failed at adding between nodes\n", testName);
      totalErrors++;
   }

   //return results and release memory
   if (totalErrors == 0) {
      fprintf(stderr, "%s passed\n", testName);
   }
   DestroyDataNode(firstNode);
   DestroyDataNode(secondNode);
   DestroyDataNode(nodeToInsert);

   return totalErrors;
}

int PrintDataNodeTest(void) {
   DataNode* testNode = CreateDataNode("Red Dwarf");
   char testName[] = "Print Node Test";

   if (testNode == NULL) {
      fprintf(stderr, "%s failed\n", testName);
      return 1;
   }

   fprintf(stderr, "%s\n", testName);
   PrintDataNode(testNode);
   fprintf(stderr, "Expected output: Red Dwarf\n");

   DestroyDataNode(testNode);
   return 0;
}

/* Data List Tests */

// test for proper list creation and verify contents.
// memory leaks as evidence of improper freeing
int CreateDestroyDataListTest (void) {
   char testName[] = "Create/Destroy Data List Test";
   char* testList[] = {"mansion", "apartment", "shack", "house"};
   DataNode* listHead = BuildDataList(testList, 4);

   //verify list was created
   if (listHead == NULL) {
      fprintf(stderr, "%s failed. NULL list\n", testName);
      return 1;
   }

   //test listSize function
   if (GetDataListSize(listHead) != 4) {
      fprintf(stderr, "%s failed. Incorrect Size\n", testName);
   }

   //verify list contents
   int index = 0;
   DataNode* current = listHead;
   while (current != NULL) {
      if(strcmp(current->dataValue,testList[index]) != 0) {
         fprintf(stderr, "%s failed. data differs at %d\n", testName, index);
         fprintf(stderr, "\texpected: %s\n", testList[index]);
         fprintf(stderr, "\t   found: %s\n", current->dataValue);
         return 1;
      }

      /* Move to the next node / index */
      index++;
      current = current->nextNodePtr;
   }

   // cleanup list and exist
   DestroyDataList(listHead);
   fprintf(stderr, "%s passed\n", testName);
   return 0;
}

int PrintDataListTest (void) {
   char testName[] = "Print Data List Test";
   char* testList[] = {"mansion", "apartment", "shack", "house"};
   DataNode* listHead = BuildDataList(testList, 4);

   //verify list was created
   if (listHead == NULL) {
      fprintf(stderr, "%s failed. NULL list\n", testName);
      return 1;
   }

   printf("%s  -  expected output\n", testName); 
   PrintDataList(listHead);
   printf("%s  -  Actual Output\n", testName);

   for (int i = 0; i < 4; i++) {
      printf("%s", testList[i]);
      if(i == 3) {printf("\n");}
      else {printf(", ");}
   }

   //destroy Datalist
   DestroyDataList(listHead);
   return 0;
}

int GetRandomNodeTest (void) {
   char testName[] = "Get Random Data Node Test";
   char* testList[] = {"1st", "2nd", "3rd", "4th"};
   DataNode* testHead = BuildDataList(testList, 4);

   if (testHead == NULL) {
      fprintf(stderr, "%s failed. NULL list\n", testName);
      return 1;
   }

   DataNode* randomNode = NULL;

   //test 100 times to check for randomness
   for (int i = 0; i < 100; i++) {
      randomNode = GetRandomDataNode(testHead);

      if (randomNode == NULL) {
         fprintf(stderr, "%s failed. rand returned NULL node\n", testName);
         DestroyDataList(testHead);
         return 1;
      }

      printf("%s, ", randomNode->dataValue);
   }

   DestroyDataList(testHead);
   fprintf(stderr, "%s passed\n", testName);
   return 0;
}

int main(void) {

   int status = 0;
   status += BasicCreateDestroyTest();
   status += NullStringCreateTest();
   status += LongStringCreateTest();
   status += GetNodeGeneralTest();
   status += SendNullGetNodeTest();
   status += ReturnNULLGetNodeGeneralTest();
   status += SetNextNodeGeneralTest();
   status += SetNextNodeToNULLTest();
   status += NULLOriginalSetNextNodeTest();
   status += InsertDataNodeAfterTest();
   status += PrintDataNodeTest();
   status += CreateDestroyDataListTest();
   status += PrintDataListTest();
   status += GetRandomNodeTest();

   printf("%d\n", status);

   return 0;
}