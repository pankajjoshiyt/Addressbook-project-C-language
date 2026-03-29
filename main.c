/*
In this project I created two versions:
1. main.c and addressbook.c
   - Basic version (no proper UI structure)
2. main1.c and addressbook1.c
   - Improved version with better UI

   Also i have not use the ir_size beacause i have use the contactcount for re indexing
   run commnad for 1  gcc main.c addressbook.c -o addressbook
   run command for 2  gcc main1.c addressbook1.c -o addressbook
   output same file using  ./addressbook
*/
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
		printf("\n========== ADDRESS BOOK ==========\n");
		printf("1. Add Contact\n");
		printf("2. Search Contact\n");
		printf("3. Edit Contact\n");
		printf("4. Delete Contact\n");
		printf("5. List Contacts\n");
		printf("6. Save & Exit\n");
		printf("Enter your choice: ");
		/* Input validation to avoid infinite loop
		   when user enters non-numeric value */
		if (scanf("%d", &choice) != 1)
		{
			printf("Invalid input! Enter a number.\n");

			// clear buffer
			while (getchar() != '\n')
				;
			continue;
		}
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
			printf("Data saved. Exiting...\n");
			return 0;
		default:
			printf("Invalid choice! Try again.\n");
		}
	}

	return 0;
}