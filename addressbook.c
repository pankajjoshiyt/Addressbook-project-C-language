#include <stdio.h>   // using printf then add this stdio.h stdout
#include <string.h>  
#include <ctype.h>   // use to ensure the input is what (digit, alphabate etc)

#define MAX_CONTACTS 100

struct Contact
{
    char name[50];
    char phone[15];
    char email[50];
};

struct AddressBook
{
    struct Contact contacts[MAX_CONTACTS];
    int contactCount;
    int ir_size;
};

// ================= Validattion =================
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
            // allowing special characters
            continue;
        }
        else
        {
            return 0; // invalid character
        }
    }
    return letter; 
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

    // check if ends with ".com"
    if (len < 4)  // this is for minimum 4 letter 
        return 0;  

    if (strcmp(&email[len - 4], ".com") != 0)  // end with the .com
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

// ================= INITIALIZE =================
void initialize(struct AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    addressBook->ir_size = 0;
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
        printf("Error saving file\n");
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
        printf("Address Book Full\n");
        return;
    }

    struct Contact *c = &addressBook->contacts[addressBook->contactCount];

    // Name validation
    do
    {
        printf("Enter Name: ");
        scanf(" %[^\n]", c->name);

        if (!isValidName(c->name))
            printf("Invalid Name! Only letters allowed.\n");

    } while (!isValidName(c->name));
    // Phone validation and  duplicate check
    do
{
    printf("Enter Phone: ");
    scanf("%14s", c->phone);   

    if (!isValidPhone(c->phone))
        printf("Invalid Phone! Enter exactly 10 digits.\n");
    else if (isDuplicatePhone(addressBook, c->phone))
        printf("Phone already exists\n");

} while (!isValidPhone(c->phone) || isDuplicatePhone(addressBook, c->phone));
    // Email validation and duplicate check
    do
    {
        printf("Enter Email: ");
        scanf("%s", c->email);

        if (!isValidEmail(c->email))
            printf("Invalid Email\n");
        else if (isDuplicateEmail(addressBook, c->email))
            printf("Email already exists\n");

    } while (!isValidEmail(c->email) || isDuplicateEmail(addressBook, c->email));

    addressBook->contactCount++;

    printf("Contact added successfully\n");
}

// ================= SEARCH =================
void search_contact(struct AddressBook *addressBook)
{
    int choice;
    printf("\nSearch By:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int foundIndexes[MAX_CONTACTS];
    int count = 0;

    if (choice == 1)
    {
        char name[50];
        printf("Enter name: ");  // (matching word allowed):
        scanf(" %[^\n]", name);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].name, name) != NULL)
            {
                foundIndexes[count++] = i;
            }
        }
    }
    else if (choice == 2)
    {
        char phone[15];
        printf("Enter phone: ");
        scanf("%s", phone);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, phone) == 0)
            {
                foundIndexes[count++] = i;
            }
        }
    }
    else if (choice == 3)
    {
        char email[50];
        printf("Enter email: ");
        scanf("%s", email);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, email) == 0)
            {
                foundIndexes[count++] = i;
            }
        }
    }
    else
    {
        printf("Invalid choice\n");
        return;
    }
    if (count == 0)
    {
        printf("No matching contacts found\n");
        return;
    }
    //  Show only basic info like name and phone number
    printf("\nMatching Contacts:\n");
    for (int i = 0; i < count; i++)
    {
        int idx = foundIndexes[i];
        printf("%d. %s | %s\n", i + 1,
               addressBook->contacts[idx].name,
               addressBook->contacts[idx].phone);
    }

    // select the contact
    int select;
    printf("\nEnter number to view full details: ");
    scanf("%d", &select);

    if (select < 1 || select > count)
    {
        printf("Invalid selection\n");
        return;
    }

    int idx = foundIndexes[select - 1];  // idx is just varibble that denote the index value 

    // Now showing full details
    printf("\nContact Details:\n");
    printf("Name: %s\n", addressBook->contacts[idx].name);
    printf("Phone: %s\n", addressBook->contacts[idx].phone);
    printf("Email: %s\n", addressBook->contacts[idx].email);
}
// ================= EDIT =================
void edit_contact(struct AddressBook *addressBook)
{
    char name[50];
    int foundIndexes[MAX_CONTACTS];
    int count = 0;
    printf("Enter name to edit: ");
    scanf(" %[^\n]", name);
    //Find match
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].name, name) != NULL)
        {
            foundIndexes[count++] = i;
        }
    }
    if (count == 0)
    {
        printf("No matching contacts found\n");
        return;
    }
    // Show match
    printf("\nMatching Contacts:\n");
    for (int i = 0; i < count; i++)
    {
        int idx = foundIndexes[i];
        printf("%d. %s | %s\n", i + 1,
               addressBook->contacts[idx].name,
               addressBook->contacts[idx].phone);
    }

    int select;
    printf("\nEnter number to edit: ");
    scanf("%d", &select);

    if (select < 1 || select > count)
    {
        printf("Invalid selection\n");
        return;
    }
    int idx = foundIndexes[select - 1];
    printf("\nEditing Contact:\n");

    // ================= NAME =================
    do
    {
        printf("Enter new Name: ");
        scanf(" %[^\n]", addressBook->contacts[idx].name);
        if (!isValidName(addressBook->contacts[idx].name))
            printf("Invalid Name\n");
    } while (!isValidName(addressBook->contacts[idx].name));

    // ================= PHONE =================
    do
    {
        printf("Enter new Phone: ");
        scanf("%14s", addressBook->contacts[idx].phone);
        if (!isValidPhone(addressBook->contacts[idx].phone))
        {
            printf("Invalid Phone Enter 10 digits.\n");
        }
        else
        {
            // check duplicate 
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
                printf("Phone already exists\n");
            else
                break;
        }

    } while (1);
    // ================= EMAIL =================
    do
    {
        printf("Enter new Email: ");
        scanf("%49s", addressBook->contacts[idx].email);

        if (!isValidEmail(addressBook->contacts[idx].email))
        {
            printf("Invalid Email\n");
        }
        else
        {
            // check duplicate
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
                printf("Email already exists\n");
            else
                break;
        }

    } while (1);

    printf("Contact updated successfully\n");
}
// ================= DELETE =================
void delete_contact(struct AddressBook *addressBook)
{
    char name[50];
    int foundIndexes[MAX_CONTACTS];
    int count = 0;

    printf("Enter name to delete: ");
    scanf(" %[^\n]", name);

    //  Find matche contact list 
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].name, name) != NULL)
        {
            foundIndexes[count++] = i;
        }
    }

    // No match
    if (count == 0)
    {
        printf("No matching contacts found\n");
        return;
    }

    //  Show matching contacts
    printf("\nMatching Contacts:\n");
    for (int i = 0; i < count; i++)
    {
        int idx = foundIndexes[i];
        printf("%d. %s | %s\n", i + 1,
               addressBook->contacts[idx].name,
               addressBook->contacts[idx].phone);
    }

    //  Select which to delete
    int select;
    printf("\nEnter number to delete: ");
    scanf("%d", &select);

    if (select < 1 || select > count)
    {
        printf("Invalid selection\n");
        return;
    }

    int delIndex = foundIndexes[select - 1];
    //  Showing selected contact
    printf("\nSelected Contact:\n");
    printf("Name: %s\n", addressBook->contacts[delIndex].name);
    printf("Phone: %s\n", addressBook->contacts[delIndex].phone);

    //  Confermation for deleting  it
    char confirm;
    printf("\nAre you sure for delete (y/n): ");
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y')
    {
        printf("Deletion cancelled.\n");
        return;
    }

    //  Shift elements  for re indexing
    for (int i = delIndex; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("Contact deleted successfully\n");
}

// ================= LIST =================
void list_contacts(struct AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available\n");
        return;
    }

    printf("\nNo   %-20s %-15s %-25s\n","Name","Phone","Email");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("\nContact %d\n", i + 1);
        printf("Name: %s\n", addressBook->contacts[i].name);
        printf("Phone: %s\n", addressBook->contacts[i].phone);
        printf("Email: %s\n", addressBook->contacts[i].email);
    }
}