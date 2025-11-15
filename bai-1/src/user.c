#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/book.h"
#include "../header/user.h"

User* create_user(
    char ten[MAX],
    int ID
) {
    User* user = (User*)malloc(sizeof(User));
    if (user == NULL) {
        return NULL;
    }
    strcpy(user->ten, ten);
    user->ID = ID;
    user->so_luong_sach_da_muon = 0;
    user->sach_da_muon.num = 0;
    return user;
}

enum STATUS add_user(User_slot *users, User *user) {
    if (users->num >= MAX) {
        return FAIL;
    }
    users->content[users->num] = *user;
    users->num++;
    return DONE;
}

void print_borrowed_book(User* user) {
    if (user->sach_da_muon.num == 0) {
        printf("User borrowed 0 books.\n");
        return;
    }
    
    printf("User borrowed %d book(s):\n", user->sach_da_muon.num);
    for (int i = 0; i < user->sach_da_muon.num; i++) {
        printf("  %d. Book title: %s\n", i + 1, user->sach_da_muon.content[i].tieu_de);
        printf("     ID: %d\n", user->sach_da_muon.content[i].ID);
    }
}

enum STATUS search_user(
    char search_criterion[],
    User_slot* users
) {
    if (users->num == 0) {
        printf("No users found.\n");
        return FAIL;
    }
    
    int found = 0;
    for (int i = 0; i < users->num; i++) {
        User* user = &users->content[i];
        int match = 0;
        
        if (strcmp(search_criterion, "ten") == 0 || strstr(user->ten, search_criterion) != NULL) {
            match = 1;
        } else if (strcmp(search_criterion, "ID") == 0 && atoi(search_criterion) == user->ID) {
            match = 1;
        }
        
        if (match || strcmp(search_criterion, "") == 0) {
            printf("\n--- User Found ---\n");
            printf("User name: %s\n", user->ten);
            printf("User ID: %d\n", user->ID);
            print_borrowed_book(user);
            found = 1;
        }
    }
    
    return found ? DONE : FAIL;
}

enum STATUS change_user(char content[], User_slot* user_slot) {
    if (user_slot->num == 0) {
        printf("No users available.\n");
        return FAIL;
    }
    
    int user_input = -1;
    int user_main_list_order[MAX];
    int user_search_order = 0;
    char words[MAX][MAX_WORD_LEN];
    
    printf("\nUsers matching '%s':\n", content);
    for (int i = 0; i < user_slot->num; i++) {
        int count = split_string(user_slot->content[i].ten, words);
        for (int j = 0; j < count; j++) {
            if (strcmp(words[j], content) == 0) {
                printf("%d. %s (ID: %d)\n", user_search_order, user_slot->content[i].ten, user_slot->content[i].ID);
                user_main_list_order[user_search_order] = i;
                user_search_order++;
                break;
            }
        }
    }
    
    if (user_search_order == 0) {
        printf("No matching users found.\n");
        return FAIL;
    }
    
    printf("Enter user number to change name: ");
    scanf("%d", &user_input);
    getchar();
    
    if (user_input < 0 || user_input >= user_search_order) {
        printf("Invalid selection.\n");
        return FAIL;
    }
    
    printf("Enter new name: ");
    char new_name[MAX];
    scanf("%[^\n]s", new_name);
    getchar();
    
    strcpy(user_slot->content[user_main_list_order[user_input]].ten, new_name);
    printf("Name changed successfully.\n");
    return DONE;
}

enum STATUS del_user(User_slot* users, int user_del_order) {
    if (user_del_order < 0 || user_del_order >= users->num) {
        return FAIL;
    }
    
    for (int i = user_del_order; i < users->num - 1; i++) {
        users->content[i] = users->content[i + 1];
    }
    users->num--;
    return DONE;
}

int split_string(const char* str, char words[][MAX_WORD_LEN]) {
    if (!str) return 0;
    
    int word_count = 0;
    int word_pos = 0;
    
    for (int i = 0; str[i] && word_count < MAX; i++) {
        if (str[i] != ' ') {
            if (word_pos < MAX_WORD_LEN - 1) {
                words[word_count][word_pos++] = str[i];
            }
        } else if (word_pos > 0) {
            words[word_count][word_pos] = '\0';
            word_count++;
            word_pos = 0;
        }
    }
    
    if (word_pos > 0) {
        words[word_count][word_pos] = '\0';
        word_count++;
    }
    
    return word_count;
}
