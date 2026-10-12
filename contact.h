#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveAndExit(AddressBook *AddressBook);
void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);

int validName(char *name);
int validPhone(char *phone);
int validEmail(char *email);
int readChoice(void);

int cmpName(Contact *, Contact *);
int cmpPhone(Contact *, Contact *);
int cmpEmail(Contact *, Contact *);

#endif
