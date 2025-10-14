#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
	printf("======================================================================================\n");
	printf(" | %-5s| %-20s| %-20s| %-30s|\n","S.No", "Name", "Phone", "Email");
	printf("--------------------------------------------------------------------------------------\n");
	for(int i = 0 ; i < addressBook->contactCount; i++)
	{
		printf(" | %-5d| %-20s| %-20s| %-30s|\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
	}
	printf("======================================================================================\n");   
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

//function to validate number
int validate_number(char *numb, AddressBook *addressBook)
{
//check for 10 digits	
	if(strlen(numb)!= 10)			
	{
		printf("Invalid number!!(must be 10 digits)\n");
		printf("--------------------------------------------------------------------------------------\n");
		return 0;
	}
	for(int i = 0; i < strlen(numb); i++)
	{
//check for digits		
		if(isdigit(numb[i]) == 0)				
		{
			printf("Invalid number!!(must be a digit)\n");
			printf("--------------------------------------------------------------------------------------\n");
			return 0;
		}
	}
	for(int i = 0; i < addressBook->contactCount; i++)		
//check for duplicates		
	{
	
		if(strcmp(numb, addressBook->contacts[i].phone) == 0)
		{
			printf("The number already exist in other contact\n");
			printf("--------------------------------------------------------------------------------------\n");
			return 0;
		}
	}
	return 1;

}

int validate_email(char *email, AddressBook *addressBook)
{
//check if @ is present in the email
	char *at = strchr(email, '@');
	if(!at)
	{
		return 0;
	}
//check atleast one character is present before @
	if (email[0] == '@')
	{
		printf("invalid email!(@ not found)!\n");
		printf("--------------------------------------------------------------------------------------\n");
		return 0;
	}	
//check if .com is present
	char *dotcom = strstr(email, ".com");
	if(dotcom == NULL)
	{
		printf("invalid email! (.com not present)\n");
		printf("--------------------------------------------------------------------------------------\n");
		return 0;
	}
//check if .com is at last	
	if(strcmp(dotcom , ".com") != 0)
	{
		printf(".com must be at the last of the email!\n");
		printf("--------------------------------------------------------------------------------------\n");
		return 0;
	}
//check if lower case letters only
	for(int i = 0; email[i]!= '@'; i++)
	{
		if(isupper(email[i]))
		{
			printf("email should contain only lower case letters!\n");
			printf("--------------------------------------------------------------------------------------\n");
			return 0;
		}
	}
//check for duplicates
	for(int i = 0; i < addressBook->contactCount; i++)	
	{
		if(strcmp(email, addressBook->contacts[i].email) == 0)
		{
			printf("The email already exist in other contact\n");
			printf("--------------------------------------------------------------------------------------\n");
			return 0;
		}
	}
	return 1;	
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
		//save name
		char Name[50];
		printf("Enter the name: ");
		scanf(" %[^\n]", Name);
		printf("--------------------------------------------------------------------------------------\n");
		strcpy(addressBook->contacts[addressBook->contactCount].name, Name);
		//save number
		char numb[20];
		int valn = 0;
		do
		{
			printf("Enter phone number: ");
			scanf("%s", numb);
			printf("--------------------------------------------------------------------------------------\n");
			//number validation
			if(validate_number(numb, addressBook))
			{
				strcpy(addressBook->contacts[addressBook->contactCount].phone, numb);
				valn = 1;
			}
		}
		while(valn == 0);
		//save email
		char mail[50];
		int vale = 0;
		do
		{
			printf("Enter email address: ");
			scanf("%s", mail);
			printf("--------------------------------------------------------------------------------------\n");
			//email validation
			if(validate_email(mail, addressBook))
			{
				strcpy(addressBook->contacts[addressBook->contactCount].email, mail);
				vale = 1;
			}
		}
		while(vale == 0);
		addressBook->contactCount++;
		printf("The contact saved successfully!!\n");
		printf("======================================================================================\n");
}

//function to search contacts
int searchContact(AddressBook *addressBook, int where, int serial_no[]) 
{
	int choice;
	do
	{     
		int flag = 0, s = 0;
		search:printf("SEARCH\n");
		printf("--------------------------------------------------------------------------------------\n");
		printf("[1] -> Search by name\n[2] -> Search by number\n[3] -> Search by email\n[4] -> Back\n");
		printf("--------------------------------------------------------------------------------------\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		printf("--------------------------------------------------------------------------------------\n");
		switch(choice)
		{
	//to search by name		
			case 1: char sname[50];
					printf("Enter the name to search: ");
					scanf(" %[^\n]", sname);
					printf("======================================================================================\n");
					for(int i = 0; i < addressBook->contactCount; i++)
					{
						
						if(strcasestr(addressBook->contacts[i].name, sname) != NULL)
						{
							if(!where)
							{
								serial_no[s] = i;
							}
							printf(" | %-5d| %-20s| %-20s| %-30s|\n", ++s, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
							flag = 1;
						}
					}
					printf("======================================================================================\n");
					break;
	//to search by phone				
			case 2: char sphone[20];
					printf("Enter the phone to search: ");
					scanf("%s", sphone);
					printf("======================================================================================\n");
					for(int i = 0; i < addressBook->contactCount; i++)
					{
						if(strstr(addressBook->contacts[i].phone, sphone) != NULL)
						{
							if(!where)
							{
								serial_no[s] = i;
							}
							printf("%-5d|%-20s|%-20s|%-30s|\n", ++s, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
							flag = 1;
						}
					}
					printf("======================================================================================\n");
					break;
	//to search by email				
			case 3: char semail[50];
					printf("Enter the email to search: ");
					scanf("%s", semail);
					printf("======================================================================================\n");
					for(int i = 0; i < addressBook->contactCount; i++)
					{
						if(strstr(addressBook->contacts[i].email, semail) != NULL)
						{
							if(!where)
							{
								serial_no[s] = i;
							}
							printf("%-5d|%-20s|%-20s|%-30s|\n", ++s, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
							flag = 1;
						}	
					}
					printf("======================================================================================\n");
					break;
			case 4:return 1;		
			default:printf("Not a valid choice\n");
					printf("--------------------------------------------------------------------------------------\n");
					goto search;
		}
	//if contact not present	
		if(flag == 0)
		{
			printf("The contact not found!!\n");
			printf("--------------------------------------------------------------------------------------\n");
		}
		else if(!where)
		{
			return 0;
		}
	} while (1);	
	
}
void editContact(AddressBook *addressBook)
{
		int serial_no[addressBook->contactCount];
		//serial_no[0] == 999;
		int S = searchContact(addressBook, 0, serial_no);
		/*if(serial_no[0] == 999)
		{
			return;
		}
			*/
		if(S)
		{
			return;
		}
		printf("Enter the Sl no of the contact to edit: ");
		int sl;
		scanf("%d", &sl);
		printf("--------------------------------------------------------------------------------------\n");
		if(serial_no[sl-1] <= addressBook->contactCount)
		do
		{
			printf("[1] -> Edit Name\n[2] -> Edit Phone\n[3] -> Edit Email\n[4] -> exit\n");
			printf("--------------------------------------------------------------------------------------\n");
			printf("Enter your choice: ");
			int option;
			scanf("%d", &option);
			printf("--------------------------------------------------------------------------------------\n");
			switch(option)
			{
				case 1 :char ename[50];
						printf("Enter the new name: ");
						scanf(" %[^\n]", ename);
						printf("--------------------------------------------------------------------------------------\n");
						strcpy(addressBook -> contacts[serial_no[sl-1]].name, ename);
						printf("Name Edited successfully!!\n");
						printf("--------------------------------------------------------------------------------------\n");
						break;
				case 2 :char ephone[20];
						do
						{
							printf("Enter the new phone: ");
							scanf("%s", ephone);
							printf("--------------------------------------------------------------------------------------\n");
							if(validate_number(ephone, addressBook))
							{
								strcpy(addressBook -> contacts[serial_no[sl-1]].phone, ephone);
								printf("Phone Edited successfully!!\n");
								printf("--------------------------------------------------------------------------------------\n");
								break;
							}
						} while (1);
						break;
				case 3 :char eemail[50];
						do
						{
							printf("Enter the new email: ");
							scanf("%s", eemail);
							printf("--------------------------------------------------------------------------------------\n");
							if(validate_email(eemail, addressBook))
							{
								strcpy(addressBook -> contacts[serial_no[sl-1]].email, eemail);
								printf("Email Edited successfully!!\n");
								printf("--------------------------------------------------------------------------------------\n");
								break;
							}

						} while (1);
						break;
				case 4 : return;		
				default:printf("Invalid option!!\n");
						printf("--------------------------------------------------------------------------------------\n");
			}
		}while(1); 
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   int serial_no[addressBook->contactCount];
		//serial_no[0] = 999;
		int S = searchContact(addressBook, 0, serial_no);
		/*if(serial_no[0] == 999)
		{
			return;
		}
			*/
select:	printf("Enter the Sl no of the contact to delete: ");
		if(S)
		{
			return;
		}
		
		int sl;
		scanf("%d", &sl);
		printf("--------------------------------------------------------------------------------------\n");
		if(serial_no[sl - 1] <= addressBook->contactCount)
		{
			int conf;
		del:	printf("Are you sure delete %s\n", addressBook->contacts[serial_no[sl - 1]].name);
				printf("--------------------------------------------------------------------------------------\n");
				printf("[1] -> Yes\n[2] -> No\n");
				printf("--------------------------------------------------------------------------------------\n");
				printf("Enter your choice: ");
				scanf("%d", &conf);
				printf("--------------------------------------------------------------------------------------\n");
				switch(conf)
				{
					case 1 :for(int i = serial_no[sl - 1]; i < addressBook->contactCount - 1;i++)
							{
								addressBook->contacts[i] = addressBook->contacts[i + 1];
						    }
							addressBook->contactCount--;
							printf("Deleted succesfully!!\n");
							printf("--------------------------------------------------------------------------------------\n");
							break;
					case 2 :break;
					default:printf("Enter a valid option!!\n");
							printf("--------------------------------------------------------------------------------------\n");
					goto del;
				}
		}
		else
		{
			printf("Enter a valid choice!!\n");
			printf("--------------------------------------------------------------------------------------\n");
			goto select;
		}
}
