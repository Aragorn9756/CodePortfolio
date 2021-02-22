#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H

#define MAX_ITEM_NAME_SIZE 80

// define itemtopurchase struct
struct itemtopurchase {
    char itemName[MAX_ITEM_NAME_SIZE];
    int itemPrice;
    int itemQuantity;
};

// define ItemToPurchase type
typedef struct itemtopurchase ItemToPurchase;

/* Initialize the fields in the 
        specified ItemToPurchase struct
 * item - pointer to ItemToPurchase object
 * return - 0 on success, -1 on error 
 */
int MakeItemBlank(ItemToPurchase * itemPtr);

/*
 * PrintItemCost: Display Item cost
 *    by printing to stdout
 * item - ItemToPurchase object to be displayed*/
void PrintItemCost(ItemToPurchase item);

#endif