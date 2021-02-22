/*
 * Stephen Richardson
 * ShoppingCart.c
 * function definitions for the ShoppingCart struct
 */
#include <stdio.h>
#include <string.h>

#include "ShoppingCart.h"

/*
 * ClearBuffer: Remove all remaining charaacters
 *    from the input buffer
 */
void ClearBuffer(void) {
    char c = getchar();
   while(c != '\n' && c != EOF) {
      c = getchar();
    }
}

ShoppingCart AddItem(ItemToPurchase item, ShoppingCart cart) {
    //populate new item
    printf("Enter the Item name:\n");
    fgets(item.itemName, MAX_NAME_SIZE, stdin);
    printf("Enter the item description:\n");
    fgets(item.itemDescription, MAX_NAME_SIZE, stdin);
    printf("Enter the item price:\n");
    while (scanf(" %d", &item.itemPrice) < 1 
                || item.itemPrice <= 0) {
       printf("Please input a positive integer:\n");
       ClearBuffer();
    }
    ClearBuffer();
    printf("Enter the item quantity:\n");
    while (scanf(" %d", &item.itemQuantity) < 1 
                || item.itemQuantity <= 0) {
       printf("Please input a positive integer:\n");
       ClearBuffer();
    }
    ClearBuffer();

    //remove \n at end of name and description
    item.itemName[strlen(item.itemName) - 1] = '\0';
    item.itemDescription[strlen(item.itemDescription) - 1] = '\0';
    
    //add item to cart
    cart.cartItems[cart.cartSize] = item;
    cart.cartSize++;
    return cart;
}

ShoppingCart RemoveItem(char itemName[], ShoppingCart cart) {
    int rc;
    int i = -1;

    /* while strcmp comes back not matching and we haven't 
     *      reached the end of the cart, iterate through the
     *      cartItems array and search for a matching string
     */
    do {
        i++;
        rc = strcmp(itemName, cart.cartItems[i].itemName);
    } while(rc != 0 && i < (cart.cartSize - 1));

    //if no match, exit loop
    if (rc != 0) {
        printf("Item not found in cart. Nothing Removed.\n");
        return cart;
    }

    // otherwise, update cartSize and, starting at match, 
    // move all following items forward one index
    cart.cartSize--;
    for (int j = i; j < cart.cartSize; j++) {
        cart.cartItems[j] = cart.cartItems[j + 1];
    }
    printf("Item removed\n");

    return cart;
}

ShoppingCart ModifyItem(ItemToPurchase item, ShoppingCart cart){
    int rc;
    int i = -1;

    /* while strcmp comes back not matching and we haven't 
     *      reached the end of the cart, iterate through the
     *      cartItems array and search for a matching string
     */
    do {
        i++;
        rc = strcmp(item.itemName, cart.cartItems[i].itemName);
    } while(rc != 0 && i < (cart.cartSize - 1));

    //if no match, exit loop
    if (rc != 0) {
        printf("Item not found in cart.\n");
        return cart;
    }

    //otherwise, allow modifications
    //only modify variables that are non-blank in item
    if(strcmp(item.itemName, cart.cartItems[i].itemName) == 0) {
        strcpy(cart.cartItems[i].itemName, item.itemName);
    }
    if (item.itemPrice != 0){
        cart.cartItems[i].itemPrice = item.itemPrice;
    }
    if (item.itemQuantity != 0) {
        cart.cartItems[i].itemQuantity = item.itemQuantity;
    }

    return cart;
}

int GetNumItemsInCart(ShoppingCart cart){
    return cart.cartSize;
}

int GetCostOfCart(ShoppingCart cart){
    int totalCost = 0;

    //add up individual item's totals
    for(int i = 0; i < cart.cartSize; i++) {
        totalCost += GetItemTotal(cart.cartItems[i]);
    }

    return totalCost;
}

void PrintTotal(ShoppingCart cart){
    printf("%s's Shopping Cart - %s\n",
            cart.customerName, cart.currentDate);
    printf("Number of Items: %d\n\n", cart.cartSize);
    
    //if no items in cart, inform user and exit function
    if(cart.cartSize <= 0){
        printf("SHOPPING CART IS EMPTY\n\n");
        return;
    }
    
    //otherwise, cycle through array and print each cart
    //item's cost
    for(int i = 0; i < cart.cartSize; i++) {
        PrintItemCost(cart.cartItems[i]);
    }
    
    printf("\nTotal: $%d\n", GetCostOfCart(cart));
}

void PrintDescriptions(ShoppingCart cart) {
    printf("%s's Shopping Cart - %s\n",
            cart.customerName, cart.currentDate);
    
    //if no items in cart, inform user and exit function
    if(cart.cartSize <= 0){
        printf("\nSHOPPING CART IS EMPTY\n");
        return;
    }
    
    //otherwise, cycle through array and print each cart
    //item's description
    printf("\nItem Descriptions\n");
    for(int i = 0; i < cart.cartSize; i++) {
        PrintItemDescription(cart.cartItems[i]);
    }
}