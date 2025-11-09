#ifndef MANAGEMENT
#define MANAGEMENT
#define MAX 100
enum STATUS {DONE, FAIL};   
enum STATUS_CONVERT {ZERO, ONE, ERROR};
typedef struct User User; 
typedef struct Book Book;
typedef struct Slot Slot;
void manage (Slot* book_slot,Slot* user_slot);
enum STATUS borrow (User* user, Book book);
enum STATUS return_book (Slot* slot, int book_del_order);
#endif
