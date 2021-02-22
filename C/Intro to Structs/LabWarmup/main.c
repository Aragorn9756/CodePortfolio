#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "ItemToPurchase.h"

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
   
   // declare variables
   int rc = 0;
   int totalCost = 0;
   ItemToPurchase item1, item2;

   //initialize items
   rc = MakeItemBlank(&item1);
   if (rc < 0) {
      printf("Error: Unable to initialize item1\n");
      exit(1);
   }

   rc = MakeItemBlank(&item2);
   if (rc < 0) {
      printf("Error: Unable to initialize item2\n");
      exit(1);
   }

   // Setup first item
   printf("Item 1\n");
   printf("Enter the item name:\n");
   // [^\n] is regular expression for not return 
   scanf("%79[^\n]s", item1.itemName);
   BufferPurge();

   // read item1 price and validate user response
   printf("Enter the item price:\n");
   while (scanf(" %d", &item1.itemPrice) < 1) {
      printf("Please input an integer:\n");
      BufferPurge();
   }
   BufferPurge();

   // read item1 quantity and validate user response
   printf("Enter the item quantity:\n");
   while (scanf(" %d", &item1.itemQuantity) < 1) {
      printf("Please input an integer:\n");
      BufferPurge();
   }
   BufferPurge();

   //setup second item
   printf("\nItem 2\n");
   printf("Enter the item name:\n");
   // [^\n] is regular expression for not return 
   scanf("%79[^\n]s", item2.itemName);
   BufferPurge();

   // read item2 price and validate user response
   printf("Enter the item price:\n");
   while (scanf(" %d", &item2.itemPrice) < 1) {
      printf("Please input an integer:\n");
      BufferPurge();
   }
   BufferPurge();

   // read item2 quantity and validate user response
   printf("Enter the item quantity:\n");
   while (scanf(" %d", &item2.itemQuantity) < 1) {
      printf("Please input an integer:\n");
      BufferPurge();
   }
   BufferPurge();

   // calculate total cost
   totalCost = (item1.itemPrice * item1.itemQuantity)
               + (item2.itemPrice * item2.itemQuantity);

   // print total cost
   printf("\n\nTOTAL Cost\n");
   PrintItemCost(item1);
   PrintItemCost(item2);
   printf("\nTotal: %d\n", totalCost);
   
   return 0;
}