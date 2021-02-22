/*
 * Stephen Richardson
 * Online Shopping Cart
 * description: Users enter name and date and can then
 *      add and remove items from their cart and get the
 *      total
 */
#include <stdio.h>
#include <string.h>

#include "ItemToPurchase.h"
#include "ShoppingCart.h"

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

/*
 * PrintMenu: displays options for manipulating cart
 *      and calls necessary functions. exits until 
 *      user chooses to quit
 */
void PrintMenu(ShoppingCart cart);

int main(void) {
    //variables
    ShoppingCart custCart;
    //Initialize cartSize to 0
    custCart.cartSize = 0;

    //get name and date
    printf("Enter Customer's Name:\n");
    fgets(custCart.customerName, MAX_NAME_SIZE, stdin);
    printf("Enter Today's Date:\n");
    fgets(custCart.currentDate, MAX_DATE_SIZE, stdin);

    //remove hanging \n
    custCart.customerName[strlen(custCart.customerName) - 1] = '\0';
    custCart.currentDate[strlen(custCart.currentDate) - 1] = '\0';

    //print out cust name and date
    printf("\nCustomer Name: %s\n", custCart.customerName);
    printf("Today's Date: %s\n", custCart.currentDate);

    PrintMenu(custCart);

    return 0;
}

void PrintMenu(ShoppingCart cart) {
    char userChar = ' ';
    char itemToRemove[MAX_NAME_SIZE];
    ItemToPurchase newItem;//used as a placeholder

    //stay in function until user chooses quit
    do{
        //Display menu
        printf("\nMenu\n");
        printf("a - Add item to cart\n");
        printf("r - Remove item from cart\n");
        printf("c - Change item quantity\n");
        printf("i - Output items' descriptions\n");
        printf("o - Output shopping cart\n");
        printf("q - Quit\n");
        printf("\nChoose an option: ");

        //get user input and match up to options
        scanf(" %c", &userChar);
        BufferPurge();
        printf("\n");
        switch(userChar) {
            case 'a':
            case 'A':
                printf("ADD ITEM TO CART\n");
                MakeItemBlank(&newItem);
                cart = AddItem(newItem, cart);
                break;
            case 'r':
            case 'R':
                printf("REMOVE ITEM FROM CART\n");
                printf("Enter name of item to remove\n");
                fgets(itemToRemove, MAX_NAME_SIZE, stdin);
                //remove hanging \n
                itemToRemove[strlen(itemToRemove) - 1] = '\0';
                cart = RemoveItem(itemToRemove, cart);
                break;
            case 'c':
            case 'C':
                printf("CHANGE ITEM QUANTITY\n");
                MakeItemBlank(&newItem);
                printf("Enter the item name:\n");
                fgets(newItem.itemName, MAX_NAME_SIZE, stdin);
                //remove hanging \n
                newItem.itemName[strlen(newItem.itemName) - 1]
                            = '\0';
                printf("Enter the item quantity:\n");
                while (scanf(" %d", &newItem.itemQuantity) < 1
                            || newItem.itemQuantity <= 0) {
                    printf("Please input a positive integer:\n");
                    BufferPurge();
                }
                BufferPurge();
                cart = ModifyItem(newItem, cart);
                break;
            case 'i':
            case 'I':
                printf("OUTPUT ITEMS' DESCRIPTIONS\n");
                PrintDescriptions(cart);
                break;
            case 'o':
            case 'O':
                printf("OUTPUT SHOPPING CART\n");
                PrintTotal(cart);
                break;
            case 'q':
            case 'Q':
                //force to lower for while loop comparison
                userChar = 'q';
                printf("Thank you for shopping with us!\n");
                break;
            default:
                printf("That was not valid input. Please try again.");
                break;
        }
    }while (userChar != 'q');
    return;
}