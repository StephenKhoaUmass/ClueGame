#include "items.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
 * Function to set a new item's name and next item in the linked list.
 * Parameters: the item's name of type pointer variable and pointer to the next item.
 * Returns a pointer to the new item 
 */
struct Item* setItem (char* name, struct Item* nextItem) {
    struct Item* newItem = (struct Item*)malloc(sizeof(struct Item));
    newItem->name = name;
    newItem->nextItem = nextItem;
    return newItem;
}

/**
 * Function to add a new item to the player's inventory.
 * Parameters: a double pointer to the 1st item of the inventory (if exists) and the name of the new item
 */
void add_item (struct Item ** head, char* name) {
    struct Item* newItem = (struct Item*)malloc(sizeof(struct Item));
    if (newItem == NULL) {
       exit(1);
   }
    newItem->name = name;
    newItem->nextItem = NULL;
    if (*head == NULL) {
        *head = newItem;
        return;
    }
    struct Item* currItem = *head;
    while (currItem->nextItem != NULL) {
        currItem = currItem->nextItem;
    }
    currItem->nextItem = newItem;
    return;
}

/**
 * Function to drop an item from the player's inventory.
 * Parameters: a double pointer to the 1st item of the inventory (if exists) and the name of the new item
 */
void drop_item (struct Item ** head, char* itemToDrop) {
    struct Item* currItem = *head;
    if (currItem == NULL) {
        printf("Inventory is empty so drop command can't be done. Please choose another command.");
        return;
    }
    if (strncmp(currItem->name, itemToDrop, strlen(currItem->name)) == 0 && currItem != NULL) {
        struct Item* tempItem = currItem->nextItem;
        *head = tempItem;
        free(currItem);
        return;
    }
    while (currItem->nextItem != NULL) {
        if (strncmp(currItem->nextItem->name, itemToDrop, strlen(currItem->nextItem->name)) == 0) {
            struct Item* tempItem = currItem->nextItem;
            currItem->nextItem = currItem->nextItem->nextItem;
            free(tempItem);
            break;
        }
        currItem = currItem->nextItem;
    }
}

//Function to print the items' names in the list
void printItem (struct Item * itemList) {
    while (itemList != NULL) {
        printf("%s\n", itemList->name);
        itemList = itemList->nextItem;
    }
}