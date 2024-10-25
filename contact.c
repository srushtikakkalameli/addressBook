#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

/* Function to display the list of all contacts in the Address Book */
void listContacts(AddressBook *addressBook) {
    printf("\033[1;33m");  // Set yellow color for display
    printf("All contacts information:\n\n");

    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("%-20s\t%-15s\t%-30s\n", addressBook->contacts[i].name,
                                          addressBook->contacts[i].phone,
                                          addressBook->contacts[i].email);
    }
    printf("\033[0m");  // Reset color
}

/* Function to initialize the Address Book and load contacts from file */
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);  // Load user-entered contacts from file
}

/* Function to save contacts to file and exit the program */
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);  // Save user contacts to file
    exit(EXIT_SUCCESS);  // Exit the program
}

/* Function to create a new contact and add it to the Address Book */
void createContact(AddressBook *addressBook) {
    char nameInput[50], phoneInput[20], emailInput[50];
    
    printf("Enter the name:\n");
    getchar();
    scanf("%[^\n]", nameInput);
    getchar();
    printf("Enter the phone number:\n");
    scanf("%s", phoneInput);
    getchar();
    printf("Enter the email:\n");
    scanf("%s", emailInput);
    getchar();

    /* Validate if name already exists */
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, nameInput) == 0) {
            printf("Name already exists.\n");
            return;
        }
    }

    /* Validate if the phone number is 10 digits and unique */
    if (strlen(phoneInput) != 10) {
        printf("Phone number must be exactly 10 digits.\n");
        return;
    }
    for (int i = 0; i < 10; i++) {
        if (phoneInput[i] < '0' || phoneInput[i] > '9') {
            printf("Phone number must contain only digits.\n");
            return;
        }
    }
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, phoneInput) == 0) {
            printf("Phone number already exists.\n");
            return;
        }
    }

    /* Validate if the email contains ".com" and "@" */
    if (strstr(emailInput, ".com") == NULL || strchr(emailInput, '@') == NULL) {
        printf("Invalid email format.\n");
        return;
    }
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, emailInput) == 0) {
            printf("Email already exists.\n");
            return;
        }
    }

    /* Add the new contact to the Address Book */
    strcpy(addressBook->contacts[addressBook->contactCount].name, nameInput);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phoneInput);
    strcpy(addressBook->contacts[addressBook->contactCount].email, emailInput);
    addressBook->contactCount++;

    printf("Contact saved successfully.\n");
    saveContactsToFile(addressBook);  // Save to file
}

/* Function to search for a contact based on name, phone, or email */
void searchContact(AddressBook *addressBook) {
    int option;
    char searchInput[50];
    int found = 0;

    printf("Select an option to search contact:\n");
    printf("1. By Name\n2. By Phone\n3. By Email\nOption: ");
    scanf("%d", &option);

    if (option == 1) {
        printf("Enter the name:\n");
        getchar();
        scanf("%[^\n]", searchInput);
        getchar();

        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strstr(addressBook->contacts[i].name, searchInput) != NULL) {
                printf("%s %s %s\n", addressBook->contacts[i].name,
                                       addressBook->contacts[i].phone,
                                       addressBook->contacts[i].email);
                found = 1;
            }
        }
    } else if (option == 2) {
        printf("Enter the phone number:\n");
        scanf("%s", searchInput);

        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strstr(addressBook->contacts[i].phone, searchInput) != NULL) {
                printf("%s %s %s\n", addressBook->contacts[i].name,
                                       addressBook->contacts[i].phone,
                                       addressBook->contacts[i].email);
                found = 1;
            }
        }
    } else if (option == 3) {
        printf("Enter the email ID:\n");
        scanf("%s", searchInput);

        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strstr(addressBook->contacts[i].email, searchInput) != NULL) {
                printf("%s %s %s\n", addressBook->contacts[i].name,
                                       addressBook->contacts[i].phone,
                                       addressBook->contacts[i].email);
                found = 1;
            }
        }
    } else {
        printf("Invalid option.\n");
        return;
    }

    if (!found) {
        printf("Contact not found.\n");
    }
}

/* Function to edit a contact */
void editContact(AddressBook *addressBook) {
    int option, found = 0, choice;
    int matchIndexes[addressBook->contactCount];
    char searchInput[50];

    printf("Select an option to edit contact:\n");
    printf("1. Edit Name\n2. Edit Phone\n3. Edit Email\nOption: ");
    scanf("%d", &option);

    if (option == 1) {
        printf("Enter the name to search:\n");
        getchar();
        scanf("%[^\n]", searchInput);

        int matchCount = 0;
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strstr(addressBook->contacts[i].name, searchInput)) {
                printf("%d. %s\n", matchCount + 1, addressBook->contacts[i].name);
                matchIndexes[matchCount] = i;
                matchCount++;
            }
        }
        if (matchCount == 0) {
            printf("No matches found.\n");
            return;
        }

        printf("Select the contact to edit: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > matchCount) {
            printf("Invalid selection.\n");
            return;
        }

        printf("Enter the new name:\n");
        getchar();
        scanf("%[^\n]", addressBook->contacts[matchIndexes[choice - 1]].name);
        printf("Name edited successfully.\n");

    } else if (option == 2) {
        printf("Enter the phone number to search:\n");
        getchar();
        scanf("%s", searchInput);

        int matchCount = 0;
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strstr(addressBook->contacts[i].phone, searchInput)) {
                printf("%d. %s\n", matchCount + 1, addressBook->contacts[i].phone);
                matchIndexes[matchCount] = i;
                matchCount++;
            }
        }
        if (matchCount == 0) {
            printf("No matches found.\n");
            return;
        }

        printf("Select the contact to edit: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > matchCount) {
            printf("Invalid selection.\n");
            return;
        }

        printf("Enter the new phone number:\n");
        getchar();
        scanf("%s", searchInput);

        /* Validate new phone number */
        if (strlen(searchInput) != 10) {
            printf("Phone number must be exactly 10 digits.\n");
            return;
        }
        for (int i = 0; i < 10; i++) {
            if (searchInput[i] < '0' || searchInput[i] > '9') {
                printf("Phone number must contain only digits.\n");
                return;
            }
        }

        strcpy(addressBook->contacts[matchIndexes[choice - 1]].phone, searchInput);
        printf("Phone edited successfully.\n");

    } else if (option == 3) {
        printf("Enter the email to search:\n");
        getchar();
        scanf("%[^\n]", searchInput);

        int matchCount = 0;
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strstr(addressBook->contacts[i].email, searchInput)) {
                printf("%d. %s\n", matchCount + 1, addressBook->contacts[i].email);
                matchIndexes[matchCount] = i;
                matchCount++;
            }
        }
        if (matchCount == 0) {
            printf("No matches found.\n");
            return;
        }

        printf("Select the contact to edit: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > matchCount) {
            printf("Invalid selection.\n");
            return;
        }

        printf("Enter the new email:\n");
        getchar();
        scanf("%[^\n]", searchInput);

        /* Validate new email format */
        if (strstr(searchInput, ".com") == NULL || strchr(searchInput, '@') == NULL) {
            printf("Invalid email format.\n");
            return;
        }

        strcpy(addressBook->contacts[matchIndexes[choice - 1]].email, searchInput);
        printf("Email edited successfully.\n");

    } else {
        printf("Invalid option.\n");
    }

    saveContactsToFile(addressBook);  // Save to file after editing
}

/* Function to delete a contact */
void deleteContact(AddressBook *addressBook) {
    int found = 0, choice;
    char searchInput[50];
    int matchIndexes[addressBook->contactCount];

    printf("Enter the name or email to search for deletion:\n");
    getchar();
    scanf("%[^\n]", searchInput);

    int matchCount = 0;
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strstr(addressBook->contacts[i].name, searchInput) || strstr(addressBook->contacts[i].email, searchInput)) {
            printf("%d. %s\n", matchCount + 1, addressBook->contacts[i].name);
            matchIndexes[matchCount] = i;
            matchCount++;
        }
    }
    if (matchCount == 0) {
        printf("No matches found.\n");
        return;
    }

    printf("Select the contact to delete: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > matchCount) {
        printf("Invalid selection.\n");
        return;
    }

    for (int i = matchIndexes[choice - 1]; i < addressBook->contactCount - 1; i++) {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;

    printf("Contact deleted successfully.\n");
    saveContactsToFile(addressBook);  // Save updated contacts to file
}
