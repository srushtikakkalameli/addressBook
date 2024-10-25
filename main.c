#include <stdio.h>
#include "contact.h"

int main() 
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\033[1;32m");
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\033[0m");
        
        switch (choice) {
            case 1:
                createContact(&addressBook); //function call
                break;
            case 2:
                searchContact(&addressBook);  //function call
                break;
            case 3:
                editContact(&addressBook);  //function call
                break;
            case 4:
                deleteContact(&addressBook);  //function call
                break;
            case 5:          
                listContacts(&addressBook);  //function call
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    /*if the choice is not equal to 7 then it goes to default */
     while (choice != 7);
    
       return 0;
}