#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#define MAX_CONTACTS 100

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

struct AddressBook {
    struct Contact contacts[MAX_CONTACTS];
    int contactCount;
};

// Function declarations
void initialize(struct AddressBook *);
void load_contacts(struct AddressBook *);
void save_contact(struct AddressBook *);
void add_contact(struct AddressBook *);
void search_contact(struct AddressBook *);
void edit_contact(struct AddressBook *);
void delete_contact(struct AddressBook *);
void list_contacts(struct AddressBook *);

#endif