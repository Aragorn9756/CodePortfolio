/* 
 * File: PlaylistNode.c
 * Author: Stephen Richardson
 * Date: October 24, 2020 6:41 PM MST
 * Description: Implementation of the functions found in the
 *      playlistNode.h file 
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "PlaylistNode.h"

PlaylistNode* CreatePlaylistNode(char id[], char songName[], char artistName[], int songLength) {
    
    PlaylistNode* newNode = (PlaylistNode*)malloc(sizeof(PlaylistNode));
    if (newNode == NULL) {
        return NULL;
    }

    //populate struct vars with parameters
    strncpy(newNode->uniqueID, id, 49);
    strncpy(newNode->songName, songName, 49);
    strncpy(newNode->artistName, artistName, 49);
    newNode->songLength = songLength;
    newNode->nextNodePtr = NULL;
}

int InsertPlaylistNodeAfter(PlaylistNode* nodeInList, PlaylistNode* newNode) {
    
    if (nodeInList == NULL || newNode == NULL) {
        return -1;
    }

    newNode->nextNodePtr = nodeInList->nextNodePtr;
    nodeInList->nextNodePtr = newNode;
    return 0;
}

int SetNextPlaylistNode(PlaylistNode* nodeInList, PlaylistNode* newNode) {
    
    if(nodeInList == NULL) {return -1;}
    nodeInList->nextNodePtr = newNode;
    return 0;
}

PlaylistNode* GetNextPlaylistNode(PlaylistNode* nodeInList) {
    
    if(nodeInList == NULL){return NULL;}
    return nodeInList->nextNodePtr;
}

void PrintPlaylistNode(PlaylistNode* thisNode) {
    
    if(thisNode == NULL){
        printf("This node does not exist\n\n");
        return;
    }

    printf("Unique ID: %s\n", thisNode->uniqueID);
    printf("Song Name: %s\n", thisNode->songName);
    printf("Artist Name: %s\n", thisNode->artistName);
    printf("Song Length (in seconds): %d\n\n", thisNode->songLength);
}

void DestroyPlaylistNode(PlaylistNode* thisNode) {
    
    if(thisNode == NULL) {return;}
    free(thisNode);
}