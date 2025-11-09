#include "../header/book.h"
#include "../header/user.h"
#define MAX 100

typedef struct(    
    char ten[MAX],
    int ID,
    Slot sach_da_muon,
    int so_luong_sach_da_muon
) User;

typedef struct User_slot { 
    User content[MAX];
    int num;
} User_slot;

User *create_user(    
    char ten[MAX],
    int ID,
) {
    User user;
    strcpy(user.ten, ten);
    user.ID = ID;
    user.so_luong_sach_da_muon = 0;
    return &user;
}

enum STATUS add_user(Slot *users, User *user) {
    if (num >= MAX_BOOK_SLOT) {
        return FAIL;
    }
    users->content[users->num] = user;
    users->num++;
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

void print_borrowed_book (User user) {
    if (0 == user->sach_da_muon->num) {
        printf("User borrowed 0 books. ");
        return
    } else {
        printf("User borrowed: \n");
    }
    
    for (int i = 0; i < user->sach_da_muon->num, i++) {
        printf("Book title: %s \n", user->sach_da_muon->content[i]->title);
        printf("ID: %d \n", user->sach_da_muon->content[i]->ID);
    }
}

enum STATUS search_user (
    char search_criterion[],
    Slot users,
    Slot search_slot, 
    int called_time
) {
    char const status_borrow[] = {
        "KHONG", "CO"
    };
    if (0 == called_time) 
        Slot temp_slot = users;
    else if (0 < called_time) 
        Slot temp_slot = search_slot;

    if (temp_slot->num == 0) {
        return FAIL;
    }
    for (int i = 0; i < temp_slot->num; i++) {
        Book* book = temp_slot->content[i];
        if ((strcmp(search_criterion, "tieu de")) && strcmp(tieu_de, book->tieu_de) ||
            (strcmp(search_criterion, "tac_gia")) && strcmp(tac_gia, book->tac_gia) ||
            (strcmp(search_criterion, "ID")) && string_to_boolean(ID) == book->ID )  {
            printf("User name: %s", user->ten);
            printf("User ID: %d", user->ID);
            print_borrowed_book(user);
            add_user(temp_slot, user);
        }
        return DONE;
    }
}

enum STATUS change_user(User* user, char content[], Slot sach_da_muon_new, int element) {
    switch (element) {
        case 0:
            strcpy(user->ten, content);
            break;
        case 1:
            strcpy(user->ID, content);
            break;
        case 2:
            user->sach_da_muon = sach_da_muon_new;
    }
}

enum STATUS del_user (Slot* users, int user_del_order) {
    for (int i = user_del_order; i < users->num, i++) {
        users->content[i] = users->content[i + 1];
    }
    num--;
}