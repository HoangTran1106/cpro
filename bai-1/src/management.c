#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/book.h"
#include "../header/user.h"
#include "../header/management.h"

void manage(
    Slot* book_slot,
    User_slot* user_slot
) {
    int command = 0;
    printf("!!! --- Welcome to library app ---!!!\n\n");
    
    while(1) {
        printf("\n=== MENU ===\n");
        printf("1. Create a user\n");
        printf("2. Create a book\n");
        printf("3. Change a username\n");
        printf("4. Search a user\n");
        printf("5. Change a book\n");
        printf("6. Search book(s)\n");
        printf("7. Delete a user\n");
        printf("8. Delete a book\n");
        printf("9. Borrow a book\n");
        printf("10. Return a book\n");
        printf("11. Display all books\n");
        printf("12. Display all users\n");
        printf("0. Exit program\n");
        printf("Enter your choice: ");
        scanf("%d", &command);
        getchar();

        if (command == 1) {
            char ten[MAX];
            printf("Username: "); 
            scanf("%[^\n]s", ten); 
            getchar();
            
            User* new_user = create_user(ten, user_slot->num);
            enum STATUS result = add_user(user_slot, new_user);
            if (result == FAIL) {
                printf("Full users!\n");
                free(new_user);
            } else {
                printf("Added successfully!\n");
            }
            
        } else if (command == 2) {
            char tieu_de[100];
            char tac_gia[100];
            printf("Title: "); 
            scanf("%[^\n]s", tieu_de);
            getchar();
            printf("Author: "); 
            scanf("%[^\n]s", tac_gia);
            getchar();
            
            Book* new_book = create_book(tieu_de, tac_gia, book_slot->num, 0);
            enum STATUS result = add_book(book_slot, new_book);
            if (result == FAIL) {
                printf("Full books!\n");
                free(new_book);
            } else {
                printf("Added successfully!\n");
            }
            
        } else if (command == 3) {
            char content[MAX];
            printf("Search word: "); 
            scanf("%s", content);
            getchar();
            change_user(content, user_slot);
            
        } else if (command == 4) {
            char search_criterion[MAX];
            printf("Search (name or leave empty for all): "); 
            scanf("%[^\n]s", search_criterion);
            getchar();
            search_user(search_criterion, user_slot);
            
        } else if (command == 5) {
            if (book_slot->num == 0) {
                printf("No books available.\n");
                continue;
            }
            
            int book_id;
            printf("Enter book ID to change: "); 
            scanf("%d", &book_id);
            getchar();
            
            if (book_id < 0 || book_id >= book_slot->num) {
                printf("Invalid book ID.\n");
                continue;
            }
            
            int element;
            char content[MAX];
            printf("What to change?\n0. Title\n1. Author\n2. Status\nChoice: ");
            scanf("%d", &element);
            getchar();
            
            if (element == 0) {
                printf("New title: "); 
                scanf("%[^\n]s", content);
                getchar();
            } else if (element == 1) {
                printf("New author: "); 
                scanf("%[^\n]s", content);
                getchar();
            } else if (element == 2) {
                printf("New status (0=available, 1=borrowed): "); 
                scanf("%s", content);
                getchar();
            }
            
            enum STATUS result = change_book(&book_slot->content[book_id], element, content);
            if (result == DONE) {
                printf("Changed successfully!\n");
            } else {
                printf("Failed to change!\n");
            }
            
        } else if (command == 6) {
            char search_criterion[MAX];
            char search_content[MAX];
            Slot search_slot;
            search_slot.num = 0;
            
            printf("Search by (tieu_de/tac_gia/ID): "); 
            scanf("%s", search_criterion);
            getchar();
            printf("Search content: "); 
            scanf("%[^\n]s", search_content);
            getchar();
            
            search_book(search_criterion, search_content, book_slot, &search_slot, 0);
            
        } else if (command == 7) {
            if (user_slot->num == 0) {
                printf("No users to delete.\n");
                continue;
            }
            
            int user_del_order;
            printf("You want to delete user number (0-%d): ", user_slot->num - 1); 
            scanf("%d", &user_del_order);
            getchar();
            
            enum STATUS result = del_user(user_slot, user_del_order);
            if (result == DONE) {
                printf("Deleted successfully!\n");
            } else {
                printf("Failed to delete!\n");
            }
            
        } else if (command == 8) {
            if (book_slot->num == 0) {
                printf("No books to delete.\n");
                continue;
            }
            
            int book_del_order;
            printf("You want to delete book number (0-%d): ", book_slot->num - 1); 
            scanf("%d", &book_del_order);
            getchar();
            
            enum STATUS result = del_book(book_slot, book_del_order);
            if (result == DONE) {
                printf("Deleted successfully!\n");
            } else {
                printf("Failed to delete!\n");
            }
            
        } else if (command == 9) {
            int user_id, book_id;
            printf("Enter user ID: "); 
            scanf("%d", &user_id);
            getchar();
            printf("Enter book ID: "); 
            scanf("%d", &book_id);
            getchar();
            
            if (user_id < 0 || user_id >= user_slot->num) {
                printf("Invalid user ID.\n");
                continue;
            }
            if (book_id < 0 || book_id >= book_slot->num) {
                printf("Invalid book ID.\n");
                continue;
            }
            
            enum STATUS result = borrow(&user_slot->content[user_id], &book_slot->content[book_id]);
            if (result == DONE) {
                printf("Borrowed successfully!\n");
            } else {
                printf("Failed to borrow!\n");
            }
            
        } else if (command == 10) {
            int user_id, book_order;
            printf("Enter user ID: "); 
            scanf("%d", &user_id);
            getchar();
            
            if (user_id < 0 || user_id >= user_slot->num) {
                printf("Invalid user ID.\n");
                continue;
            }
            
            print_borrowed_book(&user_slot->content[user_id]);
            printf("Enter book order to return (0-%d): ", user_slot->content[user_id].sach_da_muon.num - 1); 
            scanf("%d", &book_order);
            getchar();
            
            enum STATUS result = return_book(&user_slot->content[user_id], book_order);
            if (result == DONE) {
                printf("Returned successfully!\n");
            } else {
                printf("Failed to return!\n");
            }
            
        } else if (command == 11) {
            printf("\n=== ALL BOOKS ===\n");
            for (int i = 0; i < book_slot->num; i++) {
                printf("\nBook %d:\n", i);
                printf("  Title: %s\n", book_slot->content[i].tieu_de);
                printf("  Author: %s\n", book_slot->content[i].tac_gia);
                printf("  ID: %d\n", book_slot->content[i].ID);
                printf("  Status: %s\n", book_slot->content[i].trang_thai_muon ? "Borrowed" : "Available");
            }
            
        } else if (command == 12) {
            printf("\n=== ALL USERS ===\n");
            for (int i = 0; i < user_slot->num; i++) {
                printf("\nUser %d:\n", i);
                printf("  Name: %s\n", user_slot->content[i].ten);
                printf("  ID: %d\n", user_slot->content[i].ID);
                printf("  Books borrowed: %d\n", user_slot->content[i].sach_da_muon.num);
            }
            
        } else if (command == 0) {
            printf("Thank you for using the library!\n");
            break;
        } else {
            printf("Invalid choice!\n");
        }
    }
}

enum STATUS borrow(User* user, Book* book) {
    if (book->trang_thai_muon == 1) {
        printf("Book is already borrowed!\n");
        return FAIL;
    }
    
    if (user->sach_da_muon.num >= MAX) {
        printf("User has reached maximum borrowed books!\n");
        return FAIL;
    }
    
    user->sach_da_muon.content[user->sach_da_muon.num] = *book;
    user->sach_da_muon.num++;
    user->so_luong_sach_da_muon++;
    book->trang_thai_muon = 1;
    
    return DONE;
}

enum STATUS return_book(User* user, int book_del_order) {
    if (book_del_order < 0 || book_del_order >= user->sach_da_muon.num) {
        return FAIL;
    }
    
    for (int i = book_del_order; i < user->sach_da_muon.num - 1; i++) {
        user->sach_da_muon.content[i] = user->sach_da_muon.content[i + 1];
    }
    user->sach_da_muon.num--;
    user->so_luong_sach_da_muon--;
    
    return DONE;
}
