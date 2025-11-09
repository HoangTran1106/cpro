#include "../header/book.h"
#include "../header/user.h"
#include "../header/management.h"

void manage (
    Slot* book_slot,
    Slot* user_slot
) {
    int command = 0;
    int user_num = 0;
    int book_num = 0;
    printf("!!! --- Welcom to library apps ---!!!");
    while(1) {
        printf("What do you want to do? ");
        if (0 == user_num) {
            printf("1. Create a user\n");
        } 
        if (0 == book_num) {
            printf("2. Create a book\n");
        }
        if (0 <= user_num) {
            printf("3. Change a user\n");
            printf("4. Search a user\n");
        }
        if (0 <= book_num) {
            printf("5. Change a book\n");
            printf("6. Search book(s)\n");
        }
        if (MAX <= user_num) {
            printf("7. Delete a user\n");
        } 
        if (MAX <= book_num) {
            printf("8. Delete a book\n");
        }
        printf("9. Press 9 to exit the program");
        scanf("%d", &command);
        scanf("");

        if (1 == command) {
            char ten[MAX];
            int ID;
            printf("Username: "); scanf("%s", ten);
            ID = user_num;
            enum STATUS result = add_user(user_slot, create_user(ten, ID));
            switch (result) {
                case FAIL:
                    printf("full users");
                case DONE:
                    printf("Added successfully");
            }
        } else if (2 == command) {
            char tieu_de[100];
            char tac_gia[100];
            int  ID;
            int  trang_thai_muon = 0;
            printf("Username: "); scanf("%s", tieu_de);
            printf("Author: "); scanf("%s", tac_gia);
            ID = book_num;
            enum STATUS result = add_user(book_slot, create_book(tieu_de, tac_gia, ID, trang_thai_muon));
            switch (result) {
                case FAIL:
                    printf("full users");
                case DONE:
                    printf("Added successfully");
            }
        } else if (3 == command) {
            char content[MAX];
            User* user;
            Slot* sach_da_muon_new;
            int element;
            printf("Nhap 0 de thay doi ten"); scanf("%d", &element);
            switch (element) {
                case 0:
                    printf("Ten: "); scanf("%s", content);
                    break;
            }
            for (int i = 0; i < user_slot->content, i++) {

            }
            if (strcmp(user->ten, content)) {
                printf("Ten: "); scanf("%s", content);
            }
            change_user(user, content, sach_da_muon_new, element);
        } else if (4 == command) {
            char search_criterion[MAX];
            int called_time = 0;
            search_user (search_criterion, user_slot, user_search_slot, called_time);
        } else if (5 == command) {
            Book* book;
            int element;
            char content[MAX];
            switch (element) {
                case 0:
                    printf("Title: "); scanf("%s", content);
                    break;
                case 1:
                    printf("Author: "); scanf("%s", content);
                    break;
            }
            change_book(Book* book, int element, int content);
        } else if (6 == command) {
            char search_criterion[MAX];
            int called_time = 0;
            search_book(search_criterion, book_slot, book_search_slot, called_time);
        } else if (7 == command) {
            int user_del_order;
            printf("You want to delete user number ?: "); scanf("%d", user_del_order);
            del_user(&user_slot, user_del_order);
            break;
        }else if (8 == command) {
            int user_del_order;
            printf("You want to delete book number ?: "); scanf("%d", user_del_order);
            del_book(&book_slot, book_del_order);
            break;
        }else if (9 == command) {
            printf("Thank you for using the library");
            break;
        }
    }
}

enum STATUS borrow (User* user, Book book) {
    if (user->sach_da_muon->num >= MAX) {
        return FAIL;
    }
    user->sach_da_muon->content[user->sach_da_muon->num] = book;
    user->sach_da_muon->num++;
    return DONE;
}

enum STATUS return_book (Slot* slot, int book_del_order) {
    for (int i = book_del_order; i < user->sach_da_muon->num, i++) {
        user->sach_da_muon->content[i] = user->sach_da_muon->content[i + 1];
    }
    num--;
}