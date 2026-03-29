
Name: Pankaj Uday Joshi
ID 25031_001 


# ADDRESS BOOK PROJECT (C LANGUAGE)

## Main File (main.c)

The main.c file is the entry point of the Address Book project and controls 
the overall flow of the program. It initializes the address book structure 
and loads previously saved contacts from the file at the start of execution. 
The program then runs in a continuous loop, displaying a menu to the user 
with options such as adding, searching, editing, deleting, listing contacts, 
and saving data.

Based on the user’s input, the main function calls the respective functions 
to perform the required operations. It also includes input validation to ensure 
that the user enters valid choices and prevents the program from crashing due 
to invalid input. When the user selects the exit option, the program saves all 
contact data into a file to ensure persistence and then terminates.

In the main function, a switch-case is used to select which operation to perform 
in the address book. If the input is invalid, the program shows an error message 
and asks the user to enter the choice again.

At the beginning, `stdio.h` is used for standard input/output functions.  
`MAX_CONTACTS` is defined as 100 to limit the number of contacts stored.

The `Contact` structure is created to store name, phone, and email.  
The `AddressBook` structure manages multiple contacts using an array and a 
variable `contactCount` to track how many contacts are stored.

There is also a variable `ir_size`, but it is not used in this project.  
Instead, `contactCount` along with loops is used to manage and access contacts efficiently.

Function declarations are used to define all operations of the system.  
They allow modular programming and make the code organized and easy to manage.

---

## AddressBook File (addressbook.c)

### Libraries Used

- `stdio.h` → for input-output functions  
- `string.h` → for string handling functions  
- `ctype.h` → for character validation (digit, alphabet, etc.)

The addressbook.c file contains all core functionalities of the Address Book system.  
It includes operations like adding, searching, editing, deleting, and displaying contacts.  
It also handles validation, duplicate checking, and file operations like loading and saving data.

---

## Function Descriptions

### initialize()
- Initializes the address book  
- Sets contact count to zero  
- Prepares system to store contacts  

### load_contacts()
- Loads contacts from file  
- Reads data from `database.csv`  
- Stores data into array  

### save_contact()
- Saves all contacts to file  
- Writes data into `database.csv`  
- Ensures data persistence  

### isValidName()
- Checks if name is valid  
- Allows alphabets and some special characters  
- Prevents invalid input  

### isValidPhone()
- Validates phone number  
- Ensures exactly 10 digits  
- Maintains correct format  

### isValidEmail()
- Validates email format  
- Checks `@`, `.`, and `.com`  
- Ensures basic correctness  

### isDuplicatePhone()
- Checks for duplicate phone numbers  
- Compares with existing data  
- Prevents repetition  

### isDuplicateEmail()
- Checks for duplicate emails  
- Compares with stored emails  
- Avoids duplicate entries  

### add_contact()
- Adds new contact  
- Takes input and validates  
- Stores contact in array  

### search_contact()
- Searches contacts  
- Supports name, phone, and email  
- Displays matching results  

### edit_contact()
- Edits existing contact  
- Updates name, phone, email  
- Applies validation and checks  

### delete_contact()
- Deletes a contact  
- Removes selected entry  
- Shifts remaining data  

### list_contacts()
- Displays all contacts  
- Shows structured output  
- Improves readability  

---

## Project Conclusion

This project successfully demonstrates how basic C programming concepts 
can be used to build a practical application. It covers structures, file 
handling, and validation in a simple and effective way.

The system provides a user-friendly command-line interface to manage 
contacts efficiently. It ensures data accuracy through validation and 
prevents duplicate entries.

Overall, this project helps in understanding real-world application 
development using C and can be extended with advanced features.

---

## Note

The variable `ir_size` is declared in the AddressBook structure but is not 
used in this project. Instead, the program uses `contactCount` along with 
loops to manage and access contacts efficiently. Therefore, `ir_size` is 
not required for the current implementation.