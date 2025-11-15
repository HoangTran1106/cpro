#ifndef BOOK_H
#define BOOK_H

#define MAX 100

enum STATUS {DONE, FAIL};
enum STATUS_CONVERT {ZERO, ONE, ERROR};

typedef struct Book {
    char tieu_de[100];
    char tac_gia[100];
    int ID;
    int trang_thai_muon;  // 0: available, 1: borrowed
} Book;

typedef struct Slot { 
    Book content[MAX];
    int num;
} Slot;

// Function declarations
Book* create_book(char tieu_de[100], char tac_gia[100], int ID, int trang_thai_muon);
enum STATUS add_book(Slot* slot, Book* book);
enum STATUS_CONVERT string_to_boolean(char in);
enum STATUS search_book(char search_criterion[], char search_content[], Slot *slot, Slot *search_slot, int called_time);
enum STATUS change_book(Book* book, int element, char content[]);
enum STATUS del_book(Slot* slot, int book_del_order);

#endif
