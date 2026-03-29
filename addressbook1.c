#include "addressbook.h" 
#include <stdio.h>
#include <string.h>
#include <ctype.h>
// ================= Validattion =================


// ================= INITIALIZE =================
void initialize(struct AddressBook *addressBook)
{
    addressBook->contactCount = 0;
}
int isValidName(char name[])
{
    int letter = 0;
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (isalpha(name[i]))
        {
            letter = 1;
        }
        else if (name[i] == ' ' || name[i] == '.' || name[i] == '-' || name[i] == '\'')
        {
            // allowed special characters
            continue;
        }
        else
        {
            return 0; // invalid character
        }
    }

    return letter; // must contain at least one letter
}

int isValidPhone(char phone[])
{
    int len = strlen(phone);
    if (len != 10)
        return 0;
    for (int i = 0; i < len; i++)
    {
        if (!isdigit(phone[i]))
            return 0;
    }
    return 1;
}

int isValidEmail(char email[])
{
    int at = -1, dot = -1;
    int len = strlen(email);
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
            at = i;
        if (email[i] == '.')
            dot = i;
    }
    if (at == -1 || dot == -1 || at > dot)
        return 0;
    if (len < 4)
        return 0;
    if (strcmp(&email[len - 4], ".com") != 0)
        return 0;
    return 1;
}

// ================== Duplicate==================
int isDuplicatePhone(struct AddressBook *addressBook, char phone[])
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
            return 1; // duplicate found
    }
    return 0;
}

int isDuplicateEmail(struct AddressBook *addressBook, char email[])
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
            return 1; // duplicate found
    }
    return 0;
}



// ================= LOAD =================
void load_contacts(struct AddressBook *addressBook)
{
    FILE *fp = fopen("database.csv", "r");

    if (fp == NULL)
    {
        printf("No file found, starting fresh.\n");
        return;
    }

    addressBook->contactCount = 0;

    while (addressBook->contactCount < MAX_CONTACTS &&
           fscanf(fp, "%[^,],%[^,],%[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }

    fclose(fp);
}

// ================= SAVE =================
void save_contact(struct AddressBook *addressBook)
{
    FILE *fp = fopen("database.csv", "w");

    if (fp == NULL)
    {
        printf("Error saving file!\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);
}

// ================= ADD =================
void add_contact(struct AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("\n====================================\n");
        printf("        ADDRESS BOOK FULL           \n");
        printf("====================================\n");
        return;
    }
    struct Contact *c = &addressBook->contacts[addressBook->contactCount];
    printf("\n==================================\n");
    printf("           ADD NEW CONTACT          \n");
    printf("====================================\n");

    // Name validation no dublicate checing for name 
    do
    {
        printf("Enter Name  : ");
        scanf(" %[^\n]", c->name);
        if (!isValidName(c->name))
            printf(" Invalid Name! Only letters allowed.\n");

    } while (!isValidName(c->name));

    // Phone validation and  duplicate checking
    do
    {
        printf("Enter Phone : ");
        scanf("%14s", c->phone);
        if (!isValidPhone(c->phone))
            printf(" Invalid Phone! Enter exactly 10 digits.\n");
        else if (isDuplicatePhone(addressBook, c->phone))
            printf(" Phone already exists!\n");
    } while (!isValidPhone(c->phone) || isDuplicatePhone(addressBook, c->phone));

    // Email validation and duplicate checking
    do
    {
        printf("Enter Email : ");
        scanf("%s", c->email);

        if (!isValidEmail(c->email))
            printf(" Invalid Email!\n");
        else if (isDuplicateEmail(addressBook, c->email))
            printf("Email already exists!\n");

    } while (!isValidEmail(c->email) || isDuplicateEmail(addressBook, c->email));

    addressBook->contactCount++;

    printf("------------------------------------\n");
    printf("Contact added successfully.\n");
    printf("------------------------------------\n");
}
// ================= SEARCH =================
void search_contact(struct AddressBook *addressBook)
{
    int choice;
    printf("\n====================================\n");
    printf("           SEARCH CONTACT           \n");
    printf("====================================\n");
    printf("Search By:\n");
    printf(" 1. Name\n");
    printf(" 2. Phone\n");
    printf(" 3. Email\n");
    printf("------------------------------------\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    int Index[MAX_CONTACTS];
    int count = 0;
    if (choice == 1)
    {
        char name[50];
        printf("\nEnter Name (matching similer): ");
        scanf(" %[^\n]", name);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].name, name) != NULL)
            {
                Index[count++] = i;
            }
        }
    }
    else if (choice == 2)
    {
        char phone[15];
        printf("\nEnter Phone: ");
        scanf("%s", phone);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, phone) == 0)
            {
                Index[count++] = i;
            }
        }
    }
    else if (choice == 3)
    {
        char email[50];
        printf("\nEnter Email: ");
        scanf("%s", email);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, email) == 0)
            {
                Index[count++] = i;
            }
        }
    }
    else
    {
        printf(" Invalid choice!\n");
        return;
    }

    if (count == 0)
    {
        printf("\nNo matching contacts found!\n");
        return;
    }

    // here we are showing the names where matched found with the name and number 
    printf("\n====================================\n");
    printf("         MATCHING CONTACTS          \n");
    printf("====================================\n");
    printf("No   %-20s %-15s\n", "Name", "Phone");
    printf("------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        int idx = Index[i];
        printf("%-4d %-20s %-15s\n", i + 1,
               addressBook->contacts[idx].name,
               addressBook->contacts[idx].phone);
    }

    // Ask user to select
    int select;
    printf("------------------------------------\n");
    printf("Enter number to view full details: ");
    scanf("%d", &select);

    if (select < 1 || select > count)
    {
        printf("Invalid selection!\n");
        return;
    }

    int idx = Index[select - 1];

    // After the slection showing the full details
    printf("\n====================================\n");
    printf("          CONTACT DETAILS           \n");
    printf("====================================\n");
    printf("Name  : %s\n", addressBook->contacts[idx].name);
    printf("Phone : %s\n", addressBook->contacts[idx].phone);
    printf("Email : %s\n", addressBook->contacts[idx].email);
    printf("====================================\n");
}
// ================= EDIT =================
void edit_contact(struct AddressBook *addressBook)
{
    char name[50];
    int Index[MAX_CONTACTS];
    int count = 0;

    printf("\n====================================\n");
    printf("           EDIT CONTACT             \n");
    printf("====================================\n");
    printf("Enter Name to edit: ");
    scanf(" %[^\n]", name);

    // when the find matchess 
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].name, name) != NULL)
        {
            Index[count++] = i;
        }
    }

    if (count == 0)
    {
        printf("\n No matching contacts found!\n");
        return;
    }

    // showing match 
    printf("\n====================================\n");
    printf("         MATCHING CONTACTS          \n");
    printf("====================================\n");
    printf("No   %-20s %-15s\n", "Name", "Phone");
    printf("------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        int idx = Index[i];
        printf("%-4d %-20s %-15s\n", i + 1,
               addressBook->contacts[idx].name,
               addressBook->contacts[idx].phone);
    }

    int select;
    printf("------------------------------------\n");
    printf("Enter number to edit: ");
    scanf("%d", &select);

    if (select < 1 || select > count)
    {
        printf(" Invalid selection!\n");
        return;
    }

    int idx = Index[select - 1];

    printf("\n====================================\n");
    printf("          EDITING CONTACT           \n");
    printf("====================================\n");

    // ================= NAME =================================================
    do
    {
        printf("Enter New Name  : ");
        scanf(" %[^\n]", addressBook->contacts[idx].name);

        if (!isValidName(addressBook->contacts[idx].name))
            printf(" Invalid Name!\n");

    } while (!isValidName(addressBook->contacts[idx].name));

    // ================= PHONE ================================================
    do
    {
        printf("Enter New Phone : ");
        scanf("%14s", addressBook->contacts[idx].phone);

        if (!isValidPhone(addressBook->contacts[idx].phone))
        {
            printf(" Invalid Phone! Enter 10 digits.\n");
        }
        else
        {
            int duplicate = 0;
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (i != idx &&
                    strcmp(addressBook->contacts[i].phone,
                           addressBook->contacts[idx].phone) == 0)
                {
                    duplicate = 1;
                    break;
                }
            }

            if (duplicate)
                printf(" Phone already exists!\n");
            else
                break;
        }

    } while (1);

    // ================= EMAIL ================================================
    do
    {
        printf("Enter New Email : ");
        scanf("%49s", addressBook->contacts[idx].email);

        if (!isValidEmail(addressBook->contacts[idx].email))
        {
            printf(" Invalid Email!\n");
        }
        else
        {
            int duplicate = 0;
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (i != idx &&
                    strcmp(addressBook->contacts[i].email,
                           addressBook->contacts[idx].email) == 0)
                {
                    duplicate = 1;
                    break;
                }
            }
            if (duplicate)
                printf(" Email already exists!\n");
            else
                break;
        }
    } while (1);
    printf("------------------------------------\n");
    printf("Contact updated successfully.\n");
    printf("------------------------------------\n");
}
// ================= DELETE =================
void delete_contact(struct AddressBook *addressBook)
{
    char name[50];
    int Index[MAX_CONTACTS];
    int count = 0;

    printf("\n====================================\n");
    printf("          DELETE CONTACT            \n");
    printf("====================================\n");
    printf("Enter Name to delete: ");
    scanf(" %[^\n]", name);

    //Find matches detailss
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].name, name) != NULL)
        {
            Index[count++] = i;
        }
    }

    //No match with data
    if (count == 0)
    {
        printf("\n No matching contacts found!\n");
        return;
    }

    // Show matching contactss
    printf("\n====================================\n");
    printf("         MATCHING CONTACTS          \n");
    printf("====================================\n");
    printf("No   %-20s %-15s\n", "Name", "Phone");
    printf("------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        int idx = Index[i];
        printf("%-4d %-20s %-15s\n", i + 1,
               addressBook->contacts[idx].name,
               addressBook->contacts[idx].phone);
    }

    // Select which to delete  the contact
    int select;
    printf("------------------------------------\n");
    printf("Enter number to delete: ");
    scanf("%d", &select);

    if (select < 1 || select > count)
    {
        printf(" Invalid selection!\n");
        return;
    }

    int delIndex = Index[select - 1];

    //Show selected contact
    printf("\n====================================\n");
    printf("        SELECTED CONTACT            \n");
    printf("====================================\n");
    printf("Name  : %s\n", addressBook->contacts[delIndex].name);
    printf("Phone : %s\n", addressBook->contacts[delIndex].phone);
    printf("------------------------------------\n");

    // CONFIRMATION  this add new for ensure the delete or not
    char confirm;
    printf("Are you sure for delete? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y')
    {
        printf(" Deletion cancelled.\n");
        return;
    }

    // Shift elements  for re indexing
    for (int i = delIndex; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("------------------------------------\n");
    printf("Contact deleted successfully.\n");
    printf("------------------------------------\n");
}


// ================= LIST =================
void list_contacts(struct AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("\n====================================\n");
        printf("         NO CONTACTS FOUND          \n");
        printf("====================================\n");
        return;
    }

    printf("\n==============================================\n");
    printf("              CONTACT LIST                    \n");
    printf("==============================================\n");
    printf("No   %-20s %-15s %-25s\n", "Name", "Phone", "Email");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-4d %-20s %-15s %-25s\n", i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    printf("==============================================\n");
}