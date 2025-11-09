#ifndef BOOK
#define BOOK
typedef struct Book Book; 
typedef struct Slot Slot;

Book* create_book(    
    char tieu_de[100],
    char tac_gia[100],
    int  ID,
    int  trang_thai_muon
);

enum STATUS add_book(Slot* slot, Book *book);
enum STATUS_CONVERT string_to_boolean (char in);
enum STATUS search_book (
    char search_criterion[],
    char search_content[], 
    Slot *slot,
    Slot *search_slot, 
    int called_time
);
enum STATUS change_book(Book* book, int element, char content[]);
enum STATUS del_book (Slot* slot, int book_del_order);
#endif
