/*
*  Stephen Richardson
*  October 10, 2020
*  Description: Take in astring of characters no more than 50 Chars long
*     count the number of characters in the string and output the string without spaces
*/
#include<stdio.h>
#include <string.h>

//Returns the number of characters in usrStr
int GetNumOfCharacters(const char usrStr[]) {
   
   //variable
   int numChars = 0;

   for (int i = 0; i < (int)strlen(usrStr); i++){
      if (usrStr[i] != '\0') {
         numChars++;
      }
   }
   
   return numChars;
}

void OutputWithoutWhitespace(const char userStr[]) {
   
   for (int i = 0; i < (int)strlen(userStr); i++) {
      if ( (userStr[i] != ' ') && (userStr[i] != '\t') && (userStr[i] != '\n') ) {
         printf("%c", userStr[i]);
      }
   }

}

int main(void) {

   //variables
   const int MAX_STR_LEN = 50;
   char userStr[MAX_STR_LEN];
   int numChars = 0;

   //prompt user for string and print out their input

   printf("Enter a sentence or phrase:\n");
   fgets(userStr, MAX_STR_LEN, stdin);
   printf("\nYou entered: %s\n", userStr);

   //get and print number of characters
   numChars = GetNumOfCharacters(userStr);
   printf("Number of characters: %d\n", numChars);

   //print string without whitespace
   printf("String with no whitespace: ");
   OutputWithoutWhitespace(userStr);
   printf("\n");

   return 0;
}