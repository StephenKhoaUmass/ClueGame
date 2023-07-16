// Structure for an item, including a name and a pointer to the next item in a linked list of items.
struct Item {
    char* name;
    struct Item* nextItem; 
};

struct Item* setItem (char* name, struct Item* nextItem);

void add_item (struct Item ** head, char* name);

void drop_item (struct Item ** head, char* itemToDrop);

void printItem (struct Item * itemList);

