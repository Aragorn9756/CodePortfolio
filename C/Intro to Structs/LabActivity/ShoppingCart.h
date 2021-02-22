/*
 * Stephen Richardson
 * ShoppingCart.h
 * October 19, 2020
 * header file for ShoppingCart.c
 */
#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include "ItemToPurchase.h"

#define MAX_NAME_SIZE 80
#define MAX_DATE_SIZE 20
#define NUM_ITEMS 10

struct shoppingcart {
    char customerName[MAX_NAME_SIZE];   
    char currentDate[MAX_DATE_SIZE];
    ItemToPurchase cartItems[NUM_ITEMS];
    int cartSize;
};

typedef struct shoppingcart ShoppingCart;

/*
 * AddItem(): Adds an item to the cart's cartItems array
 * item - the ItemToPurchase item to be added to the cart
 * cart - the ShoppingCart item that holds the cartItems array
 */
ShoppingCart AddItem(ItemToPurchase item, ShoppingCart cart);

/*
 * RemoveItem(): Takes in a char[] and sees if there is
 *      a match in the cart's cartItems[]. if match found
 *      remove the item and return the changed ShoppingCart.
 *      if not found, prints "Item not found" message
 *      CASE SENSITIVE
 * itemName[] - name of the item to be removed from the cart
 * cart - ShoppingCart object with the cartItems[] to be searched
 */
ShoppingCart RemoveItem(char itemName[], ShoppingCart cart);

/*
 * ModifyItem(): Searches cart's cartItems[] for the item.
 *      If found, allows user to modify the item's 
 *      description, price or quantity. Returns the modified
 *      ShoppingCart item.
 *      CASE SENSITIVE
 * item - the ItemToPurchase object to be modified
 * cart - the ShoppingCart object containing the cartItems array
 *      to be searched
 */
ShoppingCart ModifyItem(ItemToPurchase item, ShoppingCart cart);

/*
 * GetNumItemsInCart(): return the number of items currently
 *      int the cart's cartItems[]
 * cart - the ShoppingCart object containig the cartItems[]
 */
int GetNumItemsInCart(ShoppingCart cart);

/*
 * GetCostOfCart(): adds up and returns the total price
 *      of the items in the cart's cartItems[]
 * cart - The ShoppingCart object containing the cartItem's array
 *      to be added up
 */
int GetCostOfCart(ShoppingCart cart);

/*
 * PrintTotal(): Outputs the total of all the objects in 
 *      the cart. if cart is empty, outputs
 *      "SHOPPING CART IS EMPTY"
 * cart - the ShoppingCart object containing the cartItems[]
 *      to be displayed
 */
void PrintTotal(ShoppingCart cart);

/*
 * PrintDescriptions(): outputs the descriptions of all the 
 *      items in the cartItems[]. if cart empty, prints
 *      "SHOPPING CART IS EMPTY"
 * cart - The ShoppingCart object containing the cartItems[]
 *      with the descriptions to be printed out.
 */
void PrintDescriptions(ShoppingCart cart);

#endif