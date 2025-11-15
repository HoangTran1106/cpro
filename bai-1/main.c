#include <stdio.h>
#include <stdlib.h>
#include "header/book.h"
#include "header/user.h"
#include "header/management.h"

int main() {
    // Initialize book storage
    Slot book_slot;
    book_slot.num = 0;
    
    // Initialize user storage
    User_slot user_slot;
    user_slot.num = 0;
    
    // Start management system
    manage(&book_slot, &user_slot);
    
    return 0;
}
