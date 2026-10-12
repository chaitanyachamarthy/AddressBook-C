#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
//A static array to store the duplicate contact ID's.
int found, duplicateIndices[MAX_CONTACTS];

void listContacts(AddressBook *addressBook)
{
    int sortChoice;
    printf("------------------------------\n");
    printf("1. Sort By name\n");
    printf("2. Sort By phone\n");
    printf("3. Sort By email\n");
    printf("4. Main menu\n");
    printf("Enter your Choice: ");
    sortChoice = readChoice();
    int (*compare)(Contact *, Contact *);
    switch(sortChoice){
        case 1: compare = cmpName; break;
        case 2: compare = cmpPhone; break;
        case 3: compare = cmpEmail; break;
        case 4: return;
    }
    for(int i = 0; i < addressBook->contactCount-1; i++)
    {
        for(int j = 0; j < addressBook->contactCount-1-i; j++)
        {
            if(compare(&addressBook->contacts[j], &addressBook->contacts[j+1]) > 0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }
    // Printing Contacts in Tabular form.
    printf("                           Contacts List                                \n");
    printf("+-----+--------------------+---------------+---------------------------+\n");
    printf("|S.no |NAME                |PHONE          |EMAIL                      |\n");
    printf("+-----+--------------------+---------------+---------------------------+\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("|%-5d|%-20s|%-15s|%-27s|\n", i, addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    printf("+-----+--------------------+---------------+---------------------------+\n");
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    // Load contacts from file during initialization.
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS) {
        printf("Error: Contacts array is full. Cannot add new contact.\n");
        return;
    }
    char str[50];
    // Validate and Store Name in structure.
    while (1)
    {
        printf("Person name: ");
        getchar();
        if (scanf("%49[^\n]", str) != 1)
        {
            printf("Invalid input\n");
            continue;
        }

        // Store the valid name into structure, while invalid name gets appropriate prompts.
        if (!validName(str))
            continue;
        else
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name, str);
            break;
        }
    }

    // Validate and store phone number in structure.
    while (1)
    {
        phone:
        printf("Phone number: ");
        getchar();
        if (scanf("%49[^\n]", str) != 1)
        {
            printf("Invalid input\n");
            continue;
        }

        // Store the valid phone number into structure, while invalid no. gets appropriate prompts.
        if (!validPhone(str))
            continue;
        else
        {
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(str, addressBook->contacts[i].phone) == 0)
                {
                    printf("Duplicate phone number found!\n");
                    goto phone;
                }
            }
            strcpy(addressBook->contacts[addressBook->contactCount].phone, str);
            break;
        }
    }

    // Validate and store Email in structure.
    while (1)
    {
        email:
        printf("Enter email: ");
        getchar();
        if (scanf("%49[^\n]", str) != 1)
        {
            printf("Invalid input\n");
            continue;
        }

        // Store the valid email into structure, while invalid email gets appropriate prompts.
        if (!validEmail(str))
            continue;
        else
        {
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(str, addressBook->contacts[i].email) == 0)
                {
                    printf("Duplicate email found!\n");
                    goto email;
                }
            }
            strcpy(addressBook->contacts[addressBook->contactCount].email, str);
            break;
        }
    }
    // Increment contactCount for every succesful contact saved.
    addressBook->contactCount++;
    printf("Contact created successfully!\n");
}

int searchContact(AddressBook *addressBook)
{
    char str[50];
    int i, cmp;
    printf("------------------------------\n");
    printf("1. Search By name\n");
    printf("2. Search By phone\n");
    printf("3. Search By email\n");
    printf("4. Main menu\n");
    while (1)
    {
        int searchChoice;
        printf("Enter your choice: ");
        searchChoice = readChoice(); // To read integer data.
        Label:
        switch(searchChoice)
        {
            case 1: 
                printf("Enter name: "); 
                break;
            case 2: 
                printf("Enter phone number: "); 
                break;
            case 3: 
                printf("Enter email id: "); 
                break;
            case 4: 
                printf("Returning to main menu...\n"); 
                return 0;
            default: 
                printf("Invalid input\n"); 
                continue;
        }
        getchar();
        scanf("%[^\n]", str);

        // check the appropriate struct member based on the choice.
        for (i = 0; i < addressBook->contactCount; ++i)
        {
            if (searchChoice == 1)
                cmp = strcmp(addressBook->contacts[i].name, str);
            else if (searchChoice == 2)
                cmp = strcmp(addressBook->contacts[i].phone, str);
            else if (searchChoice == 3)
                cmp = strcmp(addressBook->contacts[i].email, str);
            // Print Duplicate Details and store their Indices.
            if (cmp == 0)
            {
                if (found == 0)
                {
                    printf("\nContacts found:\n\n");
                    printf("ID    Name                 Phone           Email                  \n");
                    printf("------------------------------------------------------------------\n");
                }
                printf("%-5d %-20s %-15s %-25s\n", i, addressBook->contacts[i].name,
                       addressBook->contacts[i].phone, addressBook->contacts[i].email);
                duplicateIndices[found++] = i;
            }
        }
        if (!found)
        {
            printf("Contact not found\n");
            goto Label;
        }
        return 1;
    }
}

void editContact(AddressBook *addressBook)
{
    char str[50];
    int valid = 0, index, choice;
    if( searchContact(addressBook) == 0)
        return;
index:
    printf("Enter the contact ID to edit: ");
    index = readChoice(); // To read integer data.
    for (int i = 0; i < found; i++)
    {
        if (index == duplicateIndices[i])
        {
            valid = 1;
            break;
        }
    }
    if (!valid)
    {
        printf("No contact found with ID %d.\n", index);
        goto index;
    }

    printf("What would you like to edit?\n1. Name\n2. Phone number\n3. Email address\n4. Back to main menu.\n");
read_Choice:
    printf("Enter your choice:");
    choice = readChoice(); // To read integer data.

    // Edit the appropriate struct member based on the choice.
    switch (choice)
    {
    case 1:
    name:
        printf("Enter the new name: ");
        getchar();
        scanf("%[^\n]", str);
        if (validName(str))
        {
            strcpy(addressBook->contacts[index].name, str);
            printf("Contact updated successfully!\n");
            return;
        }
        else
            goto name;
    case 2:
    phone:
        printf("Enter the new phone number: ");
        getchar();
        scanf("%[^\n]", str);
        if (validPhone(str))
        {
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(str, addressBook->contacts[i].phone) == 0)
                {
                    printf("Duplicate phone number found!\n");
                    goto phone;
                }
            }
            strcpy(addressBook->contacts[index].phone, str);
            printf("Contact updated successfully!\n");
            return;
        }
        else
            goto phone;
    case 3:
    email:
        printf("Enter the new email: ");
        getchar();
        scanf("%[^\n]", str);
        if (validName(str))
        {
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(str, addressBook->contacts[i].email) == 0)
                {
                    printf("Duplicate email found!\n");
                    goto email;
                }
            }
            strcpy(addressBook->contacts[index].email, str);
            printf("Contact updated successfully!\n");
            return;
        }
        else
            goto email;
    case 4:
        printf("Returning to Main menu...\n");
        return;
    default:
        printf("Invalid choice!\n");
        goto read_Choice;
    }
}

void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount <= 0) {
        printf("Error: Contacts array empty.\n");
        return;
    }
    int valid = 0, index;
    if( searchContact(addressBook) == 0)
        return;
index:
    printf("Enter the contact ID to delete: ");
    index = readChoice(); // To read integer data.

    // Check whether the index is valid to delete or not.
    for (int i = 0; i < found; i++)
    {
        if (index == duplicateIndices[i])
        {
            valid = 1;
            break;
        }
    }
    if (!valid)
    {
        printf("No contact found with ID %d.\n", index);
        goto index;
    }

    // Overwrite the current index with last struct members.
    strcpy(addressBook->contacts[index].name, addressBook->contacts[addressBook->contactCount - 1].name);
    strcpy(addressBook->contacts[index].phone, addressBook->contacts[addressBook->contactCount - 1].phone);
    strcpy(addressBook->contacts[index].email, addressBook->contacts[addressBook->contactCount - 1].email);
    addressBook->contactCount--;
    printf("Contact deleted succesfully\n");
    return;
}


int validName(char *name)
{
    int len = strlen(name);
    // validating whether name contains atleast 3 characters
    if (len < 3)
    {
        printf("ERROR: Name must contain atleast 3 characters!\n");
        return 0;
    }

    // validating whether name contains only spaces or alphabets
    for (int i = 0; i < len; i++)
    {
        if (!(isalpha(name[i]) || name[i] == ' '))
        {
            printf("ERROR: Name should only contain alphabets!\n");
            return 0;
        }
    }

    // validating space at start/end.
    if (name[0] == ' ' || name[len - 1] == ' ')
    {
        printf("ERROR: Name shouldn't start/end with space!\n");
        return 0;
    }

    // validating consecutive spaces and characters b\w words.
    for (int i = 1; i < len - 1; i++)
    {
        if ((name[i] == ' ' && name[i - 1] == ' ') || (name[i] != ' ' && name[i - 1] == ' ' && name[i + 1] == ' '))
        {
            printf("ERROR: Consecutive Spaces or characters b/w names not allowed.\n");
            return 0;
        }
    }


    return 1;
}

int validPhone(char *phone)
{
    int len = strlen(phone);
    // validating whether phone[] contains only digits.
    for (int i = 0; i < len; i++)
    {
        if (!isdigit(phone[i]))
        {
            printf("ERROR: Phone number should contain only digits.\n");
            return 0;
        }
    }

    // validating whether phone[] contains 10 digits.
    if (len != 10)
    {
        printf("ERROR: Phone number must only contain 10 digits!\n");
        return 0;
    }

    // validating whether a valid indian number.
    if (phone[0] < '6')
    {
        printf("ERROR: Not a valid Indian number!\n");
        return 0;
    }
    return 1;
}

int validEmail(char *email)
{
    int is_at = 0, is_dot = 0, last_dot, at_index, len = strlen(email);
    // check whether email start/end with valid characters
    if (email[0] == '.' || email[len - 1] == '.')
    {
        printf("Email shouldn't start/end with dot(s)\n");
        return 0;
    }

    // validate for spaces,only one @.
    for (int i = 0; i < len; i++)
    {
        if (email[i] == ' ')
        {
            printf("Email shouldn't contain spaces!\n");
            return 0;
        }
        if (email[i] == '@')
        {
            is_at++;
            at_index = i;
        }
        if (email[i] == '.')
        {
            if (email[i - 1] == '.')
            {
                printf("Consecutive dot(s) not allowed in email\n");
                return 0;
            }
            else
            {
                is_dot++;
                last_dot = i;
            }
        }
    }
    if (is_at != 1)
    {
        printf("Email must contain exactly one '@' symbol.\n");
        return 0;
    }
    if (at_index == 0)
    {
        printf("Local part shouldn't be empty\n");
        return 0;
    }
    if (email[at_index - 1] == '.' || email[at_index + 1] == '.')
    {
        printf("dot(s) nearby @ is not allowed\n");
        return 0;
    }
    if (is_dot == 0)
    {
        printf("Atleast one '.' should be there\n");
        return 0;
    }

    // To check whether the extension is valid.
    if ((strcmp(&email[last_dot], ".com") != 0 &&
         strcmp(&email[last_dot], ".in") != 0 &&
         strcmp(&email[last_dot], ".edu") != 0 &&
         strcmp(&email[last_dot], ".org") != 0))
    {
        printf("Invalid domain extension -> %s\n", &email[last_dot]);
        return 0;
    }

    // validate the Local part.
    int i;
    for (i = 0; email[i] != '@'; i++)
    {
        if(isupper(email[i]))
            email[i] = email[i] + 32;
        if (!isalnum(email[i]) && email[i] != '+' && email[i] != '-' && email[i] != '_' && email[i] != '.')
        {
            printf("Local part should only contain alpha/numeric/./+/-/_ charcaters only\n");
            return 0;
        }
    }

    // validate the domain part.
    for (i = at_index + 1; i < last_dot; i++)
    {
        if (!isalnum(email[i]) && email[i] != '-' && email[i] != '.')
        {
            printf("Domain part should only contain alpha/numeric/./- charcaters only\n");
            return 0;
        }
        if (email[at_index + 1] == '-' || ((email[i] == '-') && (email[i - 1] == '.' || email[i + 1] == '.')))
        {
            printf("Domain part shouldn't start/end with '-'\n");
            return 0;
        }
    }
    return 1;
}

int readChoice(void)
{
    int ch, choice;
    while (scanf("%d", &choice) != 1)
    {
        printf("Invalid input! please enter an integer\n");
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
        printf("Enter your choice: ");
    }
    return choice;
}

int cmpName(Contact *a, Contact *b)
{
    return strcmp(a->name,b->name);
}

int cmpPhone(Contact *a, Contact *b)
{
    return strcmp(a->phone,b->phone);
}

int cmpEmail(Contact *a, Contact *b)
{
    return strcmp(a->email,b->email); 
}