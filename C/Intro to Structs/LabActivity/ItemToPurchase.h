#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H

#define MAX_NAME_SIZE 80

// define itemtopurchase struct
struct itemtopurchase {
    char itemName[MAX_NAME_SIZE];
    char itemDescription[MAX_NAME_SIZE];
    int itemPrice;
    int itemQuantity;
};

// define ItemToPurchase type
typedef struct itemtopurchase ItemToPurchase;

/* 
 * MakeItemBlank(): Initialize the fields in the 
 *    specified ItemToPurchase struct
 * item - pointer to ItemToPurchase object
 * return - 0 on success, -1 on error 
 */
int MakeItemBlank(ItemToPurchase * itemPtr);

/*
 * PrintItemCost(): Display Item cost
 *    by printing to stdout
 * item - ItemToPurchase object to be displayed
 */
void PrintItemCost(ItemToPurchase item);

/* 
 * PrintItemDescription(): Display Item Description
 *    by printing to stdout
 * item - ItemToPurchase object to be displayed
 */
void PrintItemDescription(ItemToPurchase item);

/*
 * GetItemTotal(): returns the total cost of the item
 *      i.e. price * quantity
 * item - The ItemToPurchase object whose total price
 *      is to be determined.
 */
int GetItemTotal(ItemToPurchase item);

#endif