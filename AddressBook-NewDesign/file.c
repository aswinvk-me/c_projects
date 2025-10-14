#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.csv", "w");          //save contacts to contacts.csv file
    fprintf(fp, "%d\n", addressBook->contactCount);
    fprintf(fp, "%s,%s,%s\n", "Name", "Phone", "Email");
    for(int i = 0; i < addressBook->contactCount;i++)
    {
        if (fprintf(fp, "%s,%s,%s\n",  
            addressBook->contacts[i].name, 
            addressBook->contacts[i].phone, 
            addressBook->contacts[i].email) < 0) {
            printf("Error writing to file!\n");
            break;
        }
    }
    fclose(fp);
    printf("Contacts saved successfully!\n");
    
}
void loadContactsFromFile(AddressBook *addressBook)     //load contacts from contacts.csv
{
    FILE *fp = fopen("contacts.csv", "r");
    if(fp == NULL)
    {
        printf("File doesnot exist!!\n");
        return; 
    }
    fscanf(fp, "%d\n", &addressBook->contactCount);
    fscanf(fp, "%*[^\n]\n");
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fp, "%[^,],%[^,],%[^\n]\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    fclose(fp);
}
    

