#include <stdio.h>
#include "../header/book.h"
#include <string.h>
#define MAX 100

enum STATUS {DONE, FAIL};   
enum STATUS_CONVERT {ZERO, ONE, ERROR};

/*
    add_book: them sach
*/
typedef struct Book {
    char tieu_de[100];
    char tac_gia[100];
    int ID;
    int trang_thai_muon;
} Book;
typedef struct Slot { 
    Book content[MAX];
    int num;
} Slot;


Book *create_book(    
    char tieu_de[100],
    char tac_gia[100],
    int  ID,
    int  trang_thai_muon
) {
    Book book;
    strcpy(book.tieu_de, tieu_de);
    strcpy(book.tac_gia, tac_gia);
    book.ID = ID;
    book.trang_thai_muon = trang_thai_muon;
    return &book;
}

enum STATUS add_book(Slot* slot, Book* book) {
    if (slot->num >= MAX) {
        return FAIL;
    }
    slot->content[slot->num] = *book;
    slot->num++;
    return DONE;
}

enum STATUS_CONVERT string_to_boolean (char in) {
    if (in == '0') 
        return ZERO;
    else if (in == '1') 
        return ONE;
    else 
        return ERROR; 
}

enum STATUS search_book (
    char search_criterion[],
    char search_content[], 
    Slot *slot,
    Slot *search_slot, 
    int called_time
) {
    Slot* temp_slot;
    if (0 == called_time) {
        temp_slot = slot;
    }
    else if (0 < called_time) {
        temp_slot = search_slot;
    }

    if (temp_slot->num == 0) {
        return FAIL;
    }
    for (int i = 0; i < temp_slot->num; i++) {
        Book book = temp_slot->content[i];
        int check;
        if ((strcmp(search_criterion, "tieu de")) && strcmp(search_content, book.tieu_de) ||
            (strcmp(search_criterion, "tac_gia")) && strcmp(search_content, book.tac_gia) ||
            (strcmp(search_criterion, "ID")) && string_to_boolean(search_content) == book.ID )  {
            printf("Book title: %s", book.tieu_de);
            printf("Book author: %s", book.tac_gia);
            printf("Book ID: %d", book.ID);
            printf("Book status: %d", book.trang_thai_muon);
            add_book(temp_slot, &book);
        }
        return DONE;
    }
}

enum STATUS change_book(Book* book, int element, char content[]) {
    switch (element) {
        case 0:
            strcpy(book->tieu_de, content);
            break;
        case 1:
            strcpy(book->tac_gia, content);
            break;
        case 2:
            enum STATUS_CONVERT ret_val = string_to_boolean(content);
            if (ret_val == ERROR) 
                return FAIL;
            else 
                book->trang_thai_muon = ret_val;
                return DONE;
            break;
    }
    
}

enum STATUS del_book (Slot* slot, int book_del_order) {
    for (int i = book_del_order; i < slot->num; i++) {
        slot->content[i] = slot->content[i + 1];
    }
    slot->num--;
}

