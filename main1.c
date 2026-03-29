#include <stdio.h>
#include "addressbook.h"

int main()
{
    int choice;
    struct AddressBook addressBook;
    // Initialize and load
    initialize(&addressBook);
    load_contacts(&addressBook);
    while (1)
    {
        printf("\n====================================\n");
        printf("           ADDRESS BOOK             \n");
        printf("====================================\n");
        printf(" 1. Add Contact\n");
        printf(" 2. Search Contact\n");
        printf(" 3. Edit Contact\n");
        printf(" 4. Delete Contact\n");
        printf(" 5. List Contacts\n");
        printf(" 6. Save & Exit\n");
        printf("====================================\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("\n[!] Invalid input! Enter a number.\n");
            // clear buffer
            while (getchar() != '\n')
                ;
            continue;
        }
        printf("\n------------------------------------\n");
        switch (choice)
        {
        case 1:
            add_contact(&addressBook);
            break;
        case 2:
            search_contact(&addressBook);
            break;
        case 3:
            edit_contact(&addressBook);
            break;
        case 4:
            delete_contact(&addressBook);
            break;
        case 5:
            list_contacts(&addressBook);
            break;
        case 6:
            save_contact(&addressBook);
            printf("\nData saved successfully.\n");
            printf("Exiting program...\n");
            return 0;
        default:
            printf("Invalid choice! Please try again.\n");
        }
        printf("------------------------------------\n");
    }
    return 0;
}