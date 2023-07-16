1. This program plays the game Amateur Detective, a text-based adventure game based on Clue. I created this 
project by writing into 5 C files. rooms.c and rooms. h are the source and header files that implement the 
structure of a room, a function that allocate memory space for 9 rooms and randomize their location through 
their names. items.c and items.h are the source and header files that implement the structure of an item, 
as well as functions that set items' names and next items, add, drop items and print their names in a list. 
adventure.c has the main function, which read user input and "react" to the commands. I then link all of 
them and compile into an object file name clue with the command "gcc adventure.c rooms.c items.c -o clue", 
and run the program with "./clue". 

2. I created an array of 9 rooms and allocate memory space for each room with malloc through a for loop.
I then connect the rooms via pointers. Each room has pointers to adjacent rooms in 4 directions: North,
South, East, West. If the rooms are on the edge, at least 1 of the pointers to the rooms are set to NULL.
In each room's struct, there is also the room's name, pointer to a linked list of items in that room and
an array of characters. I use shuffleVal to randomly initialize the rooms' locations. In the main function,
I initialize the rooms' names, their list of items and characters' names.

3. The player first should type "help" to see the list of commands available. They can then type "look" to
see the current room's name, surrounding rooms, characters and list of items. To move to another room, they
must type go and then the direction. If the direction is invalid, they must type again. After moving to 
another room, the player can type "look" again to see the list of items and characters in their current
room. To take an item, the player types "take" and an item's name in the room. The player must retype if
the item's name is invalid. They then can check the inventory by typing "inventory". To drop an item, the 
player types "drop" and an item's name in the room (I'm sorry but somehow my former code gives an error if
the player types an item not in the list, so you can't retype the item's name). To receive clues, the 
player type "clue" and a character's name. Then, that character will be moved to their current room.
Again, I'm really sorry about this but in many times, my code gives a Segmentation fault after the player type a 
character's name. After that, they can type an item's name to see if it is the weapon used. 
If the player is in the correct room and guess the characters and items correctly,
they win the game. Else, they have 9 more attempts before losing the game.

4. I use C structs in my code to represent rooms, items and the avatar.

5. I use malloc/calloc in various places: in add_item and drop_item methods, to allocate memory for 
instances of structs such as avatar, rooms...

6. I use free in the drop_item methods to free memory of the deleted item and the avatar
at the end of the game.