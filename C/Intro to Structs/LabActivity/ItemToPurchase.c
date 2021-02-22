#include<stdio.h>
#include<string.h>

#include "ItemToPurchase.h"

int MakeItemBlank(ItemToPurchase * itemPtr) {

    //trying to dereference a ptr pointing to null will cause segFault
    if (itemPtr == NULL) {
        return -1;
    }

    strcpy(itemPtr->itemName, "none");
    strcpy(itemPtr->itemDescription, "none");
    itemPtr->itemPrice = 0;
    itemPtr->itemQuantity = 0;

    return 0;
}

void PrintItemCost(ItemToPurchase item) {
    printf("%s: %d @ $%d = %d\n",
            item.itemName,
            item.itemQuantity,
            item.itemPrice,
            item.itemQuantity * item.itemPrice);
}

void PrintItemDescription(ItemToPurchase item) {
    printf("%s: %s\n", item.itemName, 
            item.itemDescription);
}

int GetItemTotal(ItemToPurchase item) {
    return (item.itemPrice * item.itemQuantity);
}