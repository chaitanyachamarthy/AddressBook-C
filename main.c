/*
Name            :   Chamarthy L Veera Venkata Satya Chaitanya.
Batch id        :   26018F
Project Name    :   AddressBook Management System.
Description     :
    * Address Book is a C-based application used to manage contact information.
    * It allows users to add, search, edit, delete, and display contacts.
    * Contact details such as name, phone number, and email are stored and managed efficiently.
    * File handling is used to save and retrieve contacts for persistent storage.
*/
#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\n==============================\n");
        printf("         Address Book         \n");
        printf("==============================\n");
        printf("1. Create Contact\n");
        printf("2. Search Contacts\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. List All Contacts\n");
        printf("6. Save & Exit\n");
        menu:
        printf("------------------------------\n");
        printf("Enter your choice: ");
        choice = readChoice();
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveAndExit(&addressBook);
                break;
            default:
                printf("Invalid choice.please try again.\n");
                goto menu;
        }
    } while (choice != 6);
    
       return 0;
}
