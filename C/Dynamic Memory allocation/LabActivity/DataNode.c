/* 
 * File: DataNode.c
 * Author: Stephen Richardson  
 * Date: Sat 31 Oct 2020 5:45 MST
 * Description: implementation functions defined in DataNode.h
 *      generic list node used to store string data
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "DataNode.h"

DataNode* CreateDataNode(const char data[]) {
    //exit if empty string
    if (data == NULL) {
        fprintf(stderr, "Empty String\n");
        return NULL;
    }

    //create node and verify it exists
    DataNode* newNode = (DataNode*)malloc(sizeof(DataNode));
    if (newNode == NULL) {return NULL;}
    
    //populate node. verify string allocated correctly
    newNode->nextNodePtr = NULL;
    newNode->dataSize = strlen(data);
    int stringSize = newNode->dataSize + 1; /* +1 for /0 char */
    newNode->dataValue = (char*)malloc(stringSize * sizeof(char));
    
    if (newNode->dataValue == NULL) {return NULL;}
    strcpy(newNode->dataValue, data);

    return newNode;
}

int InsertDataNodeAfter(DataNode* nodeInList, DataNode* newNode) {
    //if either node is null, exit
    if (nodeInList == NULL || newNode == NULL) {return -1;}

    //otherwise, insert into list
    newNode->nextNodePtr = nodeInList->nextNodePtr;
    nodeInList->nextNodePtr = newNode;
    return 0;
}

int SetNextDataNode(DataNode* nodeInList, DataNode* newNode) {
    //make sure nodeInList exists
    if (nodeInList == NULL) {return -1;}
    nodeInList->nextNodePtr = newNode;
    return 0;
}

DataNode* GetNextDataNode(DataNode* nodeInList) {
    if (nodeInList == NULL) {return NULL;}
    return nodeInList->nextNodePtr;
}

void PrintDataNode(DataNode* thisNode) {
    if (thisNode == NULL){return;}
    printf("%s", thisNode->dataValue);
}

void DestroyDataNode(DataNode* thisNode) {
    //free mem for string and node
    free(thisNode->dataValue);
    free(thisNode);
}

DataNode* BuildDataList(char * data[], int numElements) {
    DataNode* headNode = NULL;
    DataNode* newNode = NULL;
    DataNode* currNode = NULL;

    for (int i = 0; i < numElements; i++) {
        //create node
        newNode = CreateDataNode(data[i]);

        //if any node fails to create, destroy existing nodes and return null
        if(newNode == NULL) {
            DestroyDataList(headNode);
            return NULL;
        }
        
        //if first node, set as head and skip to next iteration
        if (i == 0) {
            headNode = newNode;
            currNode = newNode;
            continue;
        }

        //otherwise, add to end of list;
        SetNextDataNode(currNode, newNode);
        currNode = newNode;

    }
    return headNode;
}

int GetDataListSize(DataNode* listHead) {
    int listSize = 0;
    DataNode* currNode = listHead;
    
    if (listHead == NULL) {return -1;}

    while (currNode != NULL) {
        listSize++;
        currNode = currNode->nextNodePtr;
    }

    return listSize;
}

void PrintDataList(DataNode *listHead) {
    DataNode* currNode = listHead;
    while(currNode != NULL) {
        PrintDataNode(currNode);

        //if end of list, print newline, otherwise, print ", "
        currNode = currNode->nextNodePtr;
        if (currNode == NULL) {
            printf("\n");
        }
        else {
            printf(", ");
        }
    }
}

DataNode* GetRandomDataNode(DataNode *listHead) {
    int randNode = -1;
    int listSize = GetDataListSize(listHead);

    //seed num generator with current time
    // srand(time(0));

    if (listHead == NULL){return NULL;}

    //get random node number between 0 and list size
    randNode = rand() % listSize;

    //make sure it's within bounds
    if(randNode < 0 || randNode >= listSize) {return NULL;}

    //find and return node
    if (randNode == 0) {return listHead;}

    DataNode* currNode = listHead;
    //currNode will end the loop 1 node ahead of i
    for (int i = 0; i < randNode; i++) {
        currNode = currNode->nextNodePtr;
    }
    return currNode;
}

void DestroyDataList(DataNode* listHead) {
    DataNode* currNode = listHead;

    // destroy nodes in list until head = NULL
    while (listHead != NULL) {
        listHead = listHead->nextNodePtr;
        DestroyDataNode(currNode);
        currNode = listHead;
    }
}