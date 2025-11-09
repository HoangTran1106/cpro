#ifndef USER
#define USER
typedef struct Book Book; 
typedef struct Slot Slot;
typedef struct User User;
enum STATUS add_user(Slot *users, User *user);
enum STATUS_CONVERT string_to_boolean (char in);
void print_borrowed_book (User user);

enum STATUS search_user (
    char search_criterion[],
    Slot users,
    Slot search_slot, 
    int called_time
);

enum STATUS change_user(User* user, char content[], Slot sach_da_muon_new, int element);
enum STATUS del_user (Slot users, int user_del_order);
#endif
