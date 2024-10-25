#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *file = fopen("contacts.txt", "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }
    fclose(file);
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    addressBook->contactCount = 0;  // Initialize contact count
    while (fscanf(file, "%49[^,],%19[^,],%49[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3) {
        addressBook->contactCount++;
        if (addressBook->contactCount >= MAX_CONTACTS) {
            printf("Address book is full\n");
            break;
        }
    }
    fclose(file);
}

