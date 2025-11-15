#ifndef USER_H
#define USER_H

#include "book.h"

#define MAX_WORD_LEN 50

typedef struct User {    
    char ten[MAX];
    int ID;
    Slot sach_da_muon;
    int so_luong_sach_da_muon;
} User;

typedef struct User_slot { 
    User content[MAX];
    int num;
} User_slot;

// Function declarations
User* create_user(char ten[MAX], int ID);
enum STATUS add_user(User_slot *users, User *user);
void print_borrowed_book(User* user);
enum STATUS search_user(char search_criterion[], User_slot* users);
enum STATUS change_user(char content[], User_slot* user_slot);
enum STATUS del_user(User_slot* users, int user_del_order);
int split_string(const char* str, char words[][MAX_WORD_LEN]);

#endif
