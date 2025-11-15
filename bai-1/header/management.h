#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include "book.h"
#include "user.h"

// Function declarations
void manage(Slot* book_slot, User_slot* user_slot);
enum STATUS borrow(User* user, Book* book);
enum STATUS return_book(User* user, int book_del_order);

#endif
