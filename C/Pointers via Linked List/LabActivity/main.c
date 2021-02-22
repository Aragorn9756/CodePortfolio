/* 
 * File: main.c
 * Author: Stephen Richardson
 * Date: October 24, 2020 7:27 PM MST
 * Description: Allows the player to create and manipulate
 *      a playlist using a PlaylistNode struct and a linked list
 */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "PlaylistNode.h"

//global var
const int MAX_STR_LEN = 50;

/*
 * StringTrim: after getting a string using the fgets function,
 *    replace the \n if it's there. if not, clear the buffer
 */
void StringTrim(char myString[50]) {
    
    int length = strlen(myString);
    if (myString[length - 1] == '\n') {
        myString[length - 1] = '\0';
    }
    else{
        char c = getchar();
        while(c != '\n' && c != EOF) {
        c = getchar();
        }
    }
    
}

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

void PrintMenu(char playlistName[]);

int main(void) {

    char playlistName[MAX_STR_LEN];

    //get playlist name
    printf("Enter playlist's title:\n");
    fgets(playlistName, MAX_STR_LEN - 1, stdin);
    StringTrim(playlistName);

    PrintMenu(playlistName);
    
    return 0;
}

void PrintMenu(char playlistName[]) {
    
    //variables
    char userChar = ' ';
    int rc = 0;
    int numNodes = 0;
    int songCurrPos = 0;
    int songNewPos = 0;
    int currSongNum = 0;
    int found = 0; // 1 for true, 0 for false
    int songLength = 0;
    char ID[MAX_STR_LEN];
    char songName[MAX_STR_LEN];
    char artistName[MAX_STR_LEN];
    PlaylistNode* headNode = NULL;
    PlaylistNode* tailNode = NULL;
    PlaylistNode* currentNode = NULL;
    PlaylistNode* previousNode = NULL;

    //menu loop
    do {
        // print menu
        printf("\n%s PLAYLIST MENU\n", playlistName);
        printf("a - Add song\n");
        printf("r - Remove song\n");
        printf("c - Change position of song\n");
        printf("s - Output songs by specific artist\n");
        printf("t - Output total time of playlist (in seconds)\n");
        printf("o - Output full playlist\n");
        printf("q - Quit\n");
        printf("\nChoose an option: ");

        //get user input then clear buffer
        scanf(" %c", &userChar);
        BufferPurge();

        //switch to validate input
        switch (userChar)
        {
        case 'a':
        case 'A':
            printf("\nADD SONG\n");
            
            //get user input
            /*used scanf on ID instead of fgets because I didn't want
                to allow spaces in the unique ID */
            printf("Enter song's unique ID:\n");
            scanf(" %49s", ID);
            BufferPurge();

            printf("Enter song's name:\n");
            fgets(songName, MAX_STR_LEN - 1, stdin);
            StringTrim(songName);

            printf("Enter Artist's name:\n");
            fgets(artistName, MAX_STR_LEN - 1, stdin);
            StringTrim(artistName);

            printf("Enter song's length (in seconds):\n");
            //make sure to get valid input for seconds
            rc = scanf(" %d", &songLength);
            BufferPurge();

            while (rc <= 0) {
                printf("Invalid input detected. Please try again.\n");
                printf("Enter song's length (in seconds):\n");
                rc = scanf(" %d", &songLength);
                BufferPurge();
            }

            //create first node and make sure it allocated correctly
            currentNode = CreatePlaylistNode(ID, songName, artistName, songLength);
            if (currentNode == NULL) {
                printf("Error allocating memorory for node. Exiting program.");
                exit(1);
            }

            //if first node, initialize head and tail
            if (headNode == NULL) {
                headNode = currentNode;
                tailNode = currentNode;
            }
            //otherwise, add to end of the list and make sure memory allocated correctly
            else {
                InsertPlaylistNodeAfter(tailNode, currentNode);
                if (tailNode == NULL || currentNode == NULL) {
                    printf("Error adding node to list. Exiting program.");
                    exit(1);
                }
                //make sure to update tail node
                tailNode = currentNode;
            }
            //update numNodes
            numNodes++;
            break;
        
        case 'r':
        case 'R':
            printf("\nREMOVE SONG\n");

            //get ID of song to remove
            printf("Enter the song's unique ID:\n");
            scanf(" %49s", ID);
            BufferPurge();

            //reset nodes and scan list for ID until either match found or end reached
            currentNode = headNode;
            previousNode = NULL;
            found = 0;
            do {
                
                rc = strcmp(ID, currentNode->uniqueID);
                //if IDs match 
                if (rc == 0) {
                    found = 1;
                    numNodes--;
                    strcpy(songName, currentNode->songName);

                    //if at the head, make next node new head and destroy current
                    if (currentNode == headNode) {
                        headNode = currentNode->nextNodePtr;
                        DestroyPlaylistNode(currentNode);
                        currentNode = headNode;
                    }
                    //otherwise make previous point to next and destroy current
                    else {
                        previousNode->nextNodePtr = currentNode->nextNodePtr;
                        DestroyPlaylistNode(currentNode);
                        currentNode = previousNode;
                    }
                }
                //otherwise, update node pointers
                else {
                    //if we are moving from first node, need to set previous to head
                    if (currentNode == headNode) {
                        currentNode = currentNode->nextNodePtr;
                        previousNode = headNode;
                    }
                    //otherwise, move both nodes forward.
                    else {
                        previousNode = currentNode;
                        currentNode = currentNode->nextNodePtr;
                    }
                }

            } while (currentNode != NULL && found == 0);

            //print results
            if (found == 1) {
                printf("\"%s\" removed\n", songName);
            } else
            {
                printf("ID \"%s\" not found in playlist\n", ID);
            }

            break;
        
        case 'c':
        case 'C':
            printf("\nCHANGE POSITION OF SONG\n");

            //can't change around songs if only 1 or 0 songs
            if (numNodes <= 1) {
                printf("Not enough songs in playlist to change position.\n");
                break;
            }
            
            //get and ensure validity of user input
            printf("Enter song's current position:\n");
            rc = scanf(" %d", &songCurrPos);
            BufferPurge();

            while (rc <= 0 || songCurrPos > numNodes) {
                printf("Invalid input detected. Please try again.\n");
                printf("Enter song's current position:\n");
                rc = scanf(" %d", &songCurrPos);
                BufferPurge();
            }
            if (songCurrPos < 1){songCurrPos = 1;}

            printf("Enter new position for song:\n");
            rc = scanf(" %d", &songNewPos);
            BufferPurge();

            while (rc <= 0 || songNewPos > numNodes) {
                printf("Invalid input detected. Please try again.\n");
                printf("Enter new position for song:\n");
                rc = scanf(" %d", &songNewPos);
                BufferPurge();
            }
            if (songNewPos < 1){songNewPos = 1;}

            /*GRAB NODE FROM OLD POSITION*/
            // if grabbing the head, make sure to update head
            if(songCurrPos <= 1) {
                currentNode = headNode;
                headNode = headNode->nextNodePtr;
            }
            // if grabbing tail, set current to tail and find and set previous to new tail
            else if(songCurrPos == numNodes) {
                currentNode = tailNode;
                previousNode = headNode;
                // find node BEFORE tail, not tail
                for (int i = 1; i < numNodes - 1; i++) {
                    previousNode = previousNode->nextNodePtr;
                }
                tailNode = previousNode;
                tailNode->nextNodePtr = NULL;
            }
            // otherwise, must be grabbing a middle node, so grab and move pointers
            else {
                currentNode = headNode;
                for (int i = 1; i < songCurrPos; i++) {
                    previousNode = currentNode;
                    currentNode = currentNode->nextNodePtr;
                }
                previousNode->nextNodePtr = currentNode->nextNodePtr;
            }
            //store song name for print statement
            strncpy(songName, currentNode->songName, MAX_STR_LEN - 1);

            /*MOVE CURRENTNODE TO NEW POSITION*/
            // if moving currentNode to head position
            if (songNewPos <= 1){
                currentNode->nextNodePtr = headNode;
                headNode = currentNode;
            }
            //if moving currentNode to tail position
            else if (songNewPos == numNodes) {
                tailNode->nextNodePtr = currentNode;
                currentNode->nextNodePtr = NULL;
                tailNode = currentNode;
            }
            // otherwise, must be placing somewhere in the middle
            else {
                previousNode = headNode;
                for (int i = 1; i < songNewPos - 1; i++) {
                    previousNode = previousNode->nextNodePtr;
                }
                currentNode->nextNodePtr = previousNode->nextNodePtr;
                previousNode->nextNodePtr = currentNode;
            }

            //print results
            printf("\"%s\" moved to position %d\n", songName, songNewPos);

            break;

        case 's':
        case 'S':
            printf("\nOUTPUT SONGS BY A SPECIFIC ARTIST\n");

            //make sure there are songs to check
            if (headNode == NULL) {
                printf("There are no songs in your playlist.\n");
                break;
            }

            //get the artist's name
            printf("Enter the artist's name:\n");
            fgets(artistName, 49, stdin);
            StringTrim(artistName);
            printf("\n");

            //search list for matches and print any found
            currentNode = headNode;
            found = 0;
            currSongNum = 1;
            do {

                if (strncmp(artistName, currentNode->artistName, 
                        MAX_STR_LEN - 1) == 0){
                    found  = 1;
                    printf("%d.\n", currSongNum);
                    PrintPlaylistNode(currentNode);
                }
                currSongNum++;
                currentNode = currentNode->nextNodePtr;
            } while (currentNode != NULL);

            //if no matches found, notify user
            if (found == 0) {
                printf("No songs by that artist were found.\n");
            }

            break;

        case 't':
        case 'T':
            printf("\nOUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)\n");

            //make sure songs are in playlist
            if (headNode == NULL) {
                printf("There are no songs in your playlist.\n");
            }
            //run through list and add each songs time to total
            else {
                currentNode = headNode;
                int totalTime = 0;
                do {
                    totalTime += currentNode->songLength;
                    currentNode = currentNode->nextNodePtr;
                } while (currentNode != NULL);
                printf("Total time: %d seconds\n", totalTime);
            }
            break;

        case 'o':
        case 'O':
            // output full playlist
            printf("\n%s - OUTPUT FULL PLAYLIST\n", playlistName);
            //if no playlist, say so and exit. otherwise, print songs
            if (headNode == NULL) {
                printf("Your Playlist is empty.\n");
            } else {
                int currentSongNum = 1;
                currentNode = headNode;

                //print first node
                printf("1.\n");
                PrintPlaylistNode(headNode);

                //continue printing until reaching the tail node
                while (currentNode != tailNode){
                    //move to the nodes up and increment song count
                    currentNode = currentNode->nextNodePtr;
                    currentSongNum++;

                    printf("%d.\n", currentSongNum);
                    PrintPlaylistNode(currentNode);
                }
            }
            break;
        
        case 'q':
        case 'Q':
            //force to lower for while expression
            userChar = 'q';
            printf("Clearing your playlist and exiting the program.\n\n");
            break;
        
        default:
            printf("That character was not recognized. please try again.");
            break;
        }

    } while (userChar != 'q');

    //Clear out linked list
    PlaylistNode* tobeDestroyed = NULL;
    currentNode = headNode;
    while (currentNode != NULL) {
        tobeDestroyed = currentNode;
        currentNode = currentNode->nextNodePtr;
        DestroyPlaylistNode(tobeDestroyed);
    }
}