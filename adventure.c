#include "rooms.h"
#include "items.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Maximum number of characters fgets() can take in
#define MAX_NUM_OF_CHAR 100

// Function that prints the characters in a room
void printCharacter (char *character[NUM_OF_CHARACTERS]) {
    for (int i = 0; i < NUM_OF_CHARACTERS; i++) {
        if (character[i] == NULL) {
            break;
        }
        printf("%s\n", character[i]);
    }
}
                           
int main () {
    struct Room* listRooms[9];
    roomsList(listRooms);
    //Initializes the rooms' names
    listRooms[0]->name = "Kitchen";
    listRooms[1]->name = "Bathroom 1";
    listRooms[2]->name = "Bathroom 2"; 
    listRooms[3]->name = "Living room";
    listRooms[4]->name = "Bedroom 1";
    listRooms[5]->name = "Bedroom 2";
    listRooms[6]->name = "Bedroom 3";
    listRooms[7]->name = "Gym";
    listRooms[8]->name = "Mini cinema";

    //Connect each room to surrounding rooms im 4 directions: North, South, East, West (if valid) using pointers
    listRooms[0]->North = NULL;
    listRooms[0]->South = listRooms[3];
    listRooms[0]->East = listRooms[1];
    listRooms[0]->West = NULL;

    listRooms[1]->North = NULL;
    listRooms[1]->South = listRooms[4];
    listRooms[1]->East = listRooms[2];
    listRooms[1]->West = listRooms[0];

    listRooms[2]->North = NULL;
    listRooms[2]->South = listRooms[5];
    listRooms[2]->East = NULL;
    listRooms[2]->West = listRooms[1];

    listRooms[3]->North = listRooms[0];
    listRooms[3]->South = listRooms[6];
    listRooms[3]->East = listRooms[4];
    listRooms[3]->West = NULL;

    listRooms[4]->North = listRooms[1];
    listRooms[4]->South = listRooms[7];
    listRooms[4]->East = listRooms[5];
    listRooms[4]->West = listRooms[3];

    listRooms[5]->North = listRooms[2];
    listRooms[5]->South = listRooms[8];
    listRooms[5]->East = NULL;
    listRooms[5]->West = listRooms[4];

    listRooms[6]->North = listRooms[3];
    listRooms[6]->South = NULL;
    listRooms[6]->East = listRooms[7];
    listRooms[6]->West = NULL;

    listRooms[7]->North = listRooms[4];
    listRooms[7]->South = NULL;
    listRooms[7]->East = listRooms[8];
    listRooms[7]->West = listRooms[6];

    listRooms[8]->North = listRooms[5];
    listRooms[8]->South = NULL;
    listRooms[8]->East = NULL;
    listRooms[8]->West = listRooms[7];

    /**
     * Initialize the items' names and next items in the itemList from listRooms[0] to listRooms[5] 
     * or from room 1 to room 6.
     */
    listRooms[0]->itemList = setItem("golf club", NULL);
    listRooms[1]->itemList = setItem("knife", NULL);
    listRooms[2]->itemList = setItem("rope", NULL);
    listRooms[3]->itemList = setItem("handgun", NULL);
    listRooms[4]->itemList = setItem("poison", NULL);
    listRooms[5]->itemList = setItem("wine bottle", NULL);

    //Initialize the characters' names of each room from listRooms[0] to listRooms[6], except for listRooms[4]
    listRooms[0]->character[0] = "Miss Scarlet";
    listRooms[0]->sizeOfCharacterArray = 1;
    listRooms[1]->character[0] = "Donald Trump";
    listRooms[1]->sizeOfCharacterArray = 1;
    listRooms[2]->character[0] = "Andrew Tate";
    listRooms[2]->sizeOfCharacterArray = 1;
    listRooms[3]->character[0] = "Mrs. White";
    listRooms[3]->sizeOfCharacterArray = 1;
    listRooms[5]->character[0] = "Joe Chiu";
    listRooms[5]->sizeOfCharacterArray = 1;
    listRooms[6]->character[0] =  "Mrs. Peacock";
    listRooms[6]->sizeOfCharacterArray = 1;

    listRooms[7]->sizeOfCharacterArray = 0;
    listRooms[8]->sizeOfCharacterArray = 0;

    shuffleVal(listRooms, 9);

    int randIdx = rand() % 9;   
    char *roomAnswer = listRooms[randIdx]->name; // Name of the room where the murder occured.

    while (listRooms[randIdx]->itemList == NULL) {
        randIdx = rand() % 9; 
    }

    char *weapon = listRooms[randIdx]->itemList->name; //The murder weapon used
    
    while (listRooms[randIdx]->character[0] == NULL) {
        randIdx = rand() % 9;
    }

    char *murderer = listRooms[randIdx]->character[0]; //The murderer
    
    //Structure for the avatar, which includes a pointer to the current room and the player's inventory.
    struct Avatar {
        struct Room * currRoom;
        struct Item * itemList;
    };

    struct Avatar *avatar = (struct Avatar *) malloc(sizeof(struct Avatar));
    struct Item *inventory = (struct Item *) malloc(sizeof(struct Item));

    inventory = NULL;

    //Initialize the player's current room to listRooms[4], aka room 5.
    avatar->currRoom = listRooms[4];
    avatar->itemList = inventory;

    int attemptCount = 0; // Count the number of attempts the player made

    printf("Welcome to the game Amateur Detective, a text adventure game inspired by Clue.\n");
    printf("In this game, you're going to solve a murder mystery based on clues given to you.\n");
    printf("On September 7th, 2022, Mrs. Im Jong Kun was found hanging herself in her bedroom.\n");
    printf("However, after further investigation, police suspected that she was actually murdered.\n");
    printf("You need to find out exactly who murdered Mrs. Kun with what item and in which room.\n");
    printf("Guessing 1 of the 3 incorrectly and you will lose the game.\n");
    printf("Now, let the games begin.\n");
    printf("You are in the %s.\n", avatar->currRoom->name);
    printf("Please enter a command: ");

    char *inputCommand = (char *)malloc(MAX_NUM_OF_CHAR); // char * buffer used to input the commands the player types in
    
    //If the player can't guess all 3 answers correctly after their 10th clue command, they lose the game.
    while (attemptCount < 11) { 
        fgets(inputCommand, MAX_NUM_OF_CHAR, stdin);

        if (strncmp(inputCommand, "help", 4) == 0) {
            printf("Table of commands:\n");
            printf("list: Present the list of rooms, items and characters.\n");
            printf("look: Show the rooms next to the current room, as well as the characters and the items in the current room.\n");
            printf("go: Move to another room next to the current one.\n");
            printf("take: Pick up an item.\n");
            printf("drop: Drop an item.\n");
            printf("inventory: Show your current list of items.\n");
            printf("clue: Make a clue on who the murderer is and what weapon they used.\n");
        }
        else if (strncmp(inputCommand, "list", 4) == 0) {
            printf("\nList of rooms: \n");
            for (int i = 0; i < 9; i++) {
                printf("%s\n", listRooms[i]->name);
            }
            printf("\nList of items: \n");
            for (int i = 0; i < 9; i++) {
                printItem(listRooms[i]->itemList);
            }
            printf("\nList of characters: \n");
            for (int i = 0; i < 9; i++) {
                printCharacter(listRooms[i]->character);
            }
        }
        else if (strncmp(inputCommand, "look", 4) == 0) {
            printf("Current room: %s\n", avatar->currRoom->name);
            printf("\nSurrounding rooms: \n");
            printf("North: %s\n", (avatar->currRoom->North != NULL) ? avatar->currRoom->North->name : "No room to the North.");
            printf("South: %s\n", (avatar->currRoom->South != NULL) ? avatar->currRoom->South->name : "No room to the South.");
            printf("East: %s\n", (avatar->currRoom->East != NULL) ? avatar->currRoom->East->name : "No room to the East.");
            printf("West: %s\n", (avatar->currRoom->West != NULL) ? avatar->currRoom->West->name : "No room to the West.");
            printf("\nCharacters in the room: \n");
            printf("You\n");
            if (avatar->currRoom->character[0] != NULL) {
                for (int i = 0; i < 6; i++) {
                    if (avatar->currRoom->character[i] == NULL) {
                        break;
                    }
                    printf("%s\n", avatar->currRoom->character[i]);
                }
            }
            printf("Items in the room: \n");
            if (avatar->currRoom->itemList != NULL) {
                printItem(avatar->currRoom->itemList);
            }
            else {
                printf("There is no item in this room.\n");
            }
        }

        else if (strncmp(inputCommand, "go", 2) == 0) {
            printf("\nPlease enter a direction (North, South, East, West): ");
            while (1) {
                // char* buffer used in fgets() to input the direction the player want to go
                char * direction = (char *)malloc(MAX_NUM_OF_CHAR);
                fgets(direction, MAX_NUM_OF_CHAR, stdin);
                if (strncmp(direction, "East", 4) == 0) {
                    if (avatar->currRoom->East == NULL) {
                        printf("\nCan't go East. Please try another direction: ");
                    }
                    else {
                        avatar->currRoom = avatar->currRoom->East;
                        printf("You are now in the %s.", avatar->currRoom->name);
                        break;
                    }
                }
                else if (strncmp(direction, "West", 4) == 0) {
                    if (avatar->currRoom->West == NULL) {
                        printf("\nCan't go West. Please try another direction: ");
                    }
                    else {
                        avatar->currRoom = avatar->currRoom->West;
                        printf("You are now in the %s.", avatar->currRoom->name);
                        break;
                    }
                }
                else if (strncmp(direction, "North", 5) == 0) {
                    if (avatar->currRoom->North == NULL) {
                        printf("\nCan't go North. Please try another direction: ");
                    }
                    else {
                        avatar->currRoom = avatar->currRoom->North;
                        printf("You are now in the %s.", avatar->currRoom->name);
                        break;
                    }
                }
                else if (strncmp(direction, "South", 5) == 0) {
                    if (avatar->currRoom->South == NULL) {
                        printf("\nCan't go South. Please try another direction: ");
                    }
                    else {
                        avatar->currRoom = avatar->currRoom->South;
                        printf("You are now in the %s.", avatar->currRoom->name);
                        break;
                    }
                }
                else {
                    printf("Invalid direction. Please try again.\n");
                }
            }
        }
        else if (strncmp(inputCommand, "take", 4) == 0) {
            if (avatar->currRoom->itemList == NULL) {
                printf("There is no item in this room. Please type another command: ");
            }
            else {
                printf("\nEnter the item you want to take: ");
                char *inputItem = (char *)malloc(MAX_NUM_OF_CHAR);
                while (1) {
                    fgets(inputItem, MAX_NUM_OF_CHAR, stdin);
                    if (strncmp(inputItem, avatar->currRoom->itemList->name, strlen(avatar->currRoom->itemList->name)) == 0) {
                        add_item(&inventory, avatar->currRoom->itemList->name);
                        printf("Item %s added to your inventory!\n", avatar->currRoom->itemList->name);
                        avatar->currRoom->itemList = NULL;
                        break;
                    }
                    else {
                        printf("\nInvalid item or item is not in the room. Please type again: ");
                    }
                }
            }
        }
        else if (strncmp(inputCommand, "drop", 4) == 0) {
            if (inventory == NULL) {
                printf("\nThere is no item in your inventory. Please type another command: ");
            }
            else {
                printf("\nEnter the item you want to drop: ");
                char *inputItem = (char *)malloc(MAX_NUM_OF_CHAR);
                fgets(inputItem, MAX_NUM_OF_CHAR, stdin);
                struct Item* tempVal = inventory;
                while (tempVal != NULL) {
                    if (strncmp(inputItem, tempVal->name, strlen(tempVal->name)) == 0) {
                        printf("Item %s removed from your inventory.\n", tempVal->name);
                        drop_item(&inventory, tempVal->name);
                        break;
                    } 
                    tempVal = tempVal->nextItem;
                }
            }
        }
        else if (strncmp(inputCommand, "inventory", 9) == 0) {
            if (inventory == NULL) {
                printf("Inventory is now empty.");
            }
            else {
                printf("Items in your inventory: \n");
                printItem(inventory);
            }
        }
        else if (strncmp(inputCommand, "clue", 4) == 0) {
            //Integer varible to count the number of correct guesses the player makes in a row.
            int correctGuesses = 0;

            if (strncmp(roomAnswer, avatar->currRoom->name, strlen(roomAnswer)) == 0) {
                printf("Room match.\n");
                correctGuesses++;
            }
            printf("\nType a character: ");
            char *inputCharacter = (char *)malloc(MAX_NUM_OF_CHAR);
            fgets(inputCharacter, MAX_NUM_OF_CHAR, stdin);

            // Move the character types into the player's current room and remove them from where
            // that character was.
            for (int i = 0; i < 9; i++) {
                int countChar = numOfCharInCurrRoom(listRooms[i]->character);
                for (int j = 0; j < countChar; j++) {
                   if (strncmp(inputCharacter, listRooms[i]->character[j], strlen(listRooms[i]->character[j])) == 0) {
                        if (strncmp(murderer, inputCharacter, strlen(murderer)) == 0) {
                           printf("Character Match.\n");
                           correctGuesses++;
                        }
                        avatar->currRoom->character[avatar->currRoom->sizeOfCharacterArray] = inputCharacter;
                        listRooms[i]->character[j] = NULL;
                        avatar->currRoom->sizeOfCharacterArray++;
                        break;
                    }
                }
            }
            
            printf("\nType an item: ");
            char *inputItem = (char *)malloc(MAX_NUM_OF_CHAR);
            fgets(inputItem, MAX_NUM_OF_CHAR, stdin);
            if (avatar->currRoom->itemList != NULL && strncmp(weapon, avatar->currRoom->itemList->name, strlen(avatar->currRoom->itemList->name)) == 0) {
                if (strncmp(weapon, inputItem, strlen(weapon)) == 0) {
                    printf("Item match.");
                    correctGuesses++;
                }
            }

            if (correctGuesses == 3) {
                printf("Congratulations! You won the game.");
                exit(0);
            }
            else {
                printf("Incorrect guesses. Please try again.");
                attemptCount++;
            }
        }
        else {
            printf("Invalid command. Please type again: ");
        }
    }
    printf("You lost the game. Good luck next time.");

    // Freeing memory space
    free(avatar);
    return 0;
}