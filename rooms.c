#include "rooms.h"
#include "items.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Function to allocate space for 9 rooms with (struct Room) using malloc
 * Parameter: an array of rooms with (struct Room)
 */
void roomsList (struct Room* arrayOfRooms[]) {
    for (int i = 0; i < 9; i++) {
        arrayOfRooms[i] = (struct Room*) malloc(sizeof(struct Room));    
    } 
}

/**
 * Function to shuffle the names of the rooms
 * Parameters: an array of rooms with (struct Room), an integer n for 
 * the number of times the names are shuffled.
 */ 
void shuffleVal (struct Room * listOfRooms[], int n) {
    srand(100);
    for (int i = n - 1; i > 0; i--) {
        int a = rand() % (i+1);
        char * tempRoom = listOfRooms[i]->name;
        listOfRooms[i]->name = listOfRooms[a]->name;
        listOfRooms[a]->name = tempRoom;
    }
}

int numOfCharInCurrRoom (char * character[]) {
    int count = 0;
    int i = 0;
    while (character[i] != NULL) {
        count++;
        i++;
    }
    return count;
}
