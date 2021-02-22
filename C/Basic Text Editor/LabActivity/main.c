/*
*  Stephen Richardson
*  Lab Activity 7
*  October 10, 2020
*  Description: Allows the user to enter in sample text and then prints a menu
*     The menu allows user to output number of non-whitespace characters,
*     the number of words, fix the capitalization, replace all '!', shorten
*     spaces or quit.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char PrintMenu(char userText[]);
int GetNumOfNonWSCharacters(const char userText[]);
int GetNumOfWords(const char userText[]);
void FixCapitalization(char userText[]);
void ReplaceExclamation(char userText[]);
void ShortenSpace(char userText[]);

int main(void) {

   //variables
   const int MAX_NUM_CHARS = 1001;
   int numNonWSChars = -1;//initialize to something impossible
   int numWords = -1;
   char userText[MAX_NUM_CHARS];
   char menuChar = ' ';

   /*
      Sample text for debugging purposes
      we'll continue our quest in space.  there will be more shuttle flights and more shuttle crews and,  yes,  more volunteers, more civilians,  more teachers in space.  nothing ends here;  our hopes and our journeys continue!
   */

   //get sample text
   printf("Enter a sample text up to 1000 characters:\n");
   fgets(userText, MAX_NUM_CHARS, stdin);

   //if last character is a newline, replace it with a null
   if (userText[strlen(userText) - 1] == '\n') {
      userText[strlen(userText) - 1] = '\0';
   }

   //print sample text
   printf("You entered: %s\n", userText);

   //display menu and continue until a q is received;
   while (menuChar != 'q') {
      menuChar = PrintMenu(userText);

      switch (menuChar) {
         case 'c':
            numNonWSChars = GetNumOfNonWSCharacters(userText);
            printf("Number of non-whitespace characters: %d\n", numNonWSChars);
            break;
         case 'w':
            numWords = GetNumOfWords(userText);
            printf("number of words: %d\n", numWords);
            break;
         case 'f':
            //arrays automatically pass via pointer
            FixCapitalization(userText);
            printf("Edited text: %s\n", userText);
            break;
         case 'r':
            ReplaceExclamation(userText);
            printf("Edited text: %s\n", userText);
            break;
         case 's':
            ShortenSpace(userText);
            printf("Edited text: %s\n", userText);
            break;
         default:
            break;
      }
   }

   printf("Thank you for using the Authoring Assistant\nGoodbye!\n");

   return 0;
}

//displays the menu to the user and get's the user's input
char PrintMenu(char userText[]) {

   char menuChar = ' ';
   //do something w/ user text to eliminate warning
   userText[1] = userText[1];

   //print menu
   printf("\nMENU\n");
   printf("c - Number of non-whitespace characters\n");
   printf("w - Number of words\n");
   printf("f - Fix capitalization\n");
   printf("r - Replace all !'s\n");
   printf("s - Shorten spaces\n");
   printf("q - Quit\n\n");
   printf("Choose an option: ");

   //get user input and clear buffer
   scanf(" %c", &menuChar);
   while(getchar() != '\n');

   switch (menuChar) {
      case 'c':
      case 'C':
         menuChar = 'c';
         break;
      case 'w':
      case 'W':
         menuChar = 'w';
         break;
      case 'f':
      case 'F':
         menuChar = 'f';
         break;
      case 'r':
      case 'R':
         menuChar = 'r';
         break;
      case 's':
      case 'S':
         menuChar = 's';
         break;
      case 'q':
      case 'Q':
         menuChar = 'q';
         break;
      default:
         printf("Invalid input\n");
   }

   return menuChar;
   
}

int GetNumOfNonWSCharacters(const char userText[]) {
   int nonWSChars = 0;

   for (int i = 0; i < (int)strlen(userText); i++) {
      if (userText[i] != ' ' && userText[i] != '\t') {
         nonWSChars++;
      }
   }

   return nonWSChars;
}

int GetNumOfWords( const char userText[]) {
   int numWords = 0;

   for (int i = 0; i < (int)strlen(userText); i++) {

      /* if there is a whitespace and the previous char was NOT a whitespace
      it must be a new word. two words smashed together are counted as one */
      if (userText[i] == ' ' || userText[i] == '\t') {
         if (userText[i - 1] != ' ' && userText[i - 1] != '\t') {
            numWords++;
         }
      }

      // if at the last char and it isn't a whitespace, count it as a word
      if (i == ((int)strlen(userText) - 1) && userText[i] != ' ' && userText[i] != '\t') {
         numWords++;
      }
   }

   return numWords;
}

void FixCapitalization(char userText[]) {
   bool newSentence = true;
   
   /* if newSentence is true check for nonWS characters. once one is found
      see if it is lowercase. if so, capitalize it. exit if loop and see if
      char is a punctuation mark (i.e. . ! or ?) if so, set newSentence to true. 
      this should catch double punctuation marks*/
   for (int i = 0; i < (int)strlen(userText); i++) {
      if (newSentence == true) {
         if (isblank(userText[i]) == false) {
            newSentence = false;
            userText[i] = toupper(userText[i]);
         }
      }
      //catches double punctuation
      if (userText[i] == '.' || userText[i] == '?' || userText[i] == '!'){
         newSentence = true;
      }
   }
}

void ReplaceExclamation(char userText[]) {
   //any exclamation point will be replaced with a '.'
   for (int i = 0; i < (int)strlen(userText); i++) {
      if (userText[i] == '!') {
         userText[i] = '.';
      }
   }
}

/* makes a new string array the same size as user text and adds characters from original
   one at a time, skipping extraneous spaces*/
void ShortenSpace(char userText[]) {
   char tempText[(int)strlen(userText) + 1];
   int tempIndex = 0; //where we are in the temp string

   //copy first char to temp text so we don't accidently leave array in for loop
   if (userText[0] != ' '){
      tempText[0] = userText[0];
      tempIndex++;
   }

   //if char is a ' ' AND previous char was a whitespace, don't add it into tempText,
   //otherwise copy into temp text
   for (int i = 1; i < (int)strlen(userText); i++){
      if(userText[i] == ' ' && (userText[i - 1] == ' ' || userText[i - 1] == '\t')){
         //do nothing
      } else { //otherwise, copy char to tempText
         tempText[tempIndex] = userText[i];
         tempIndex++;
      }
   }

   //once all done, add a null character to the end of temp text
   tempText[tempIndex] = '\0';

   //if tempText and userText are not the same, copy tempText onto userText
   if(strcmp(userText, tempText) != 0) {
      strcpy(userText, tempText);
   }
   
}