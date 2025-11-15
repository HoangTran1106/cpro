#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/book.h"

Book* create_book(
    char tieu_de[100],
    char tac_gia[100],
    int ID,
    int trang_thai_muon
) {
    Book* book = (Book*)malloc(sizeof(Book));
    if (book == NULL) {
        return NULL;
    }
    strcpy(book->tieu_de, tieu_de);
    strcpy(book->tac_gia, tac_gia);
    book->ID = ID;
    book->trang_thai_muon = trang_thai_muon;
    return book;
}

enum STATUS add_book(Slot* slot, Book* book) {
    if (slot->num >= MAX) {
        return FAIL;
    }
    slot->content[slot->num] = *book;
    slot->num++;
    return DONE;
}

enum STATUS_CONVERT string_to_boolean(char in) {
    if (in == '0') 
        return ZERO;
    else if (in == '1') 
        return ONE;
    else 
        return ERROR; 
}

enum STATUS search_book(
    char search_criterion[],
    char search_content[], 
    Slot *slot,
    Slot *search_slot, 
    int called_time
) {
    Slot* temp_slot;
    if (called_time == 0) {
        temp_slot = slot;
    } else {
        temp_slot = search_slot;
    }

    if (temp_slot->num == 0) {
        printf("No books found.\n");
        return FAIL;
    }
    
    search_slot->num = 0;
    int found = 0;
    
    for (int i = 0; i < temp_slot->num; i++) {
        Book book = temp_slot->content[i];
        int match = 0;
        
        if (strcmp(search_criterion, "tieu_de") == 0 && strcmp(search_content, book.tieu_de) == 0) {
            match = 1;
        } else if (strcmp(search_criterion, "tac_gia") == 0 && strcmp(search_content, book.tac_gia) == 0) {
            match = 1;
        } else if (strcmp(search_criterion, "ID") == 0 && atoi(search_content) == book.ID) {
            match = 1;
        }
        
        if (match) {
            printf("\n--- Book Found ---\n");
            printf("Book title: %s\n", book.tieu_de);
            printf("Book author: %s\n", book.tac_gia);
            printf("Book ID: %d\n", book.ID);
            printf("Book status: %s\n", book.trang_thai_muon ? "Borrowed" : "Available");
            
            if (called_time > 0) {
                search_slot->content[search_slot->num] = book;
                search_slot->num++;
            }
            found = 1;
        }
    }
    
    return found ? DONE : FAIL;
}

enum STATUS change_book(Book* book, int element, char content[]) {
    switch (element) {
        case 0:
            strcpy(book->tieu_de, content);
            return DONE;
        case 1:
            strcpy(book->tac_gia, content);
            return DONE;
        case 2: {
            enum STATUS_CONVERT ret_val = string_to_boolean(content[0]);
            if (ret_val == ERROR) {
                return FAIL;
            }
            book->trang_thai_muon = ret_val;
            return DONE;
        }
        default:
            return FAIL;
    }
}

enum STATUS del_book(Slot* slot, int book_del_order) {
    if (book_del_order < 0 || book_del_order >= slot->num) {
        return FAIL;
    }
    
    for (int i = book_del_order; i < slot->num - 1; i++) {
        slot->content[i] = slot->content[i + 1];
    }
    slot->num--;
    return DONE;
}
