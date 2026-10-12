#include <stdio.h>
#include<errno.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp = fopen("contacts.csv", "w+");//Opening file stream
    if(fp == NULL)
    {
        perror("File not found!");
        return;
    }

    //Saving contact data into "contacts.csv" file.
    for(int i = 0; i < addressBook->contactCount; ++i)
    {
        fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    
    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp = fopen("contacts.csv", "r");//opening file stream.
    if(fp == NULL)
    {
        if(errno == ENOENT)
        {
            printf("No existing contacts, starting fresh!\n");
            return;
        }
        perror("File not found!\n");
        return;
    }
    int x = 3, i = addressBook->contactCount;
    //Loading contacts from "contacts.csv" file.
    while(i < MAX_CONTACTS)
    {
        x = fscanf(fp, " %49[^,],%19[^,],%49[^\n]", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        
        if(x!= 3)
            break;
        
        i++;
    }
    addressBook->contactCount = i;
    fclose(fp);    
}
