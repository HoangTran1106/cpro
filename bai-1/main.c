#include <stdio.h>
#include "header/management.h"

int main ()  {
    Book *book_list[MAX];
    Book *user_list[MAX];
    Slot *book_slot = {*book_list, 0};
    Slot *user_slot ={*user_list, 0};
    manage(book_slot, user_slot);
    return 0;
}

