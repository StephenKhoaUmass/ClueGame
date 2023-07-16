#define NUM_OF_CHARACTERS 6   //Maximum number of characters in a room

/**
 * Structure for a room. It has a room's name, its pointers to the adjacent rooms in 4 directions (North, 
 * South, East, West), a pointer to the list of items and an array of characters in the room, as well as
 * an integer that keeps track of the size of the characters array.
 */
struct Room {
   char* name;
   struct Room * North;
   struct Room * South;
   struct Room * East;
   struct Room * West;
   struct Item * itemList;
   char *character[NUM_OF_CHARACTERS];
   int sizeOfCharacterArray;
};

void roomsList (struct Room* arrayOfRooms[]);

void shuffleVal (struct Room * listOfRooms[], int n);

int numOfCharInCurrRoom (char * character[]);

