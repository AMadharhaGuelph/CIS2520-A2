/*
Name: Ankush Madharha
ID: 1172859
Date: 2022-10-22
Assignment Name: Assignment 2 - Stacks (Reverse Polish notation (RPN): Lukasiewicz notation)
*/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Struct declaration and definition
typedef struct car {
    char plateNumber[9];
    int milage;
    int expectedReturnDate;
    struct car *next;
}car;

// Function declarations
void loadListsFromFile(car **avilable, car **rented, car **repair, char *textfile);
void addNewCarToAvailableForRentList(car **availableForRentList);
void moveRepairToAvailable(car **inRepairList, car **availableForRentList);
void moveCar(car **source, car **dest);
void rentFirstCar(car **availableForRentList, car **rentedList);
void addToEnd(car* newCar, car **list);
void deleteCar(car**list, int position);
float calculateCharge(int initialMilage, int newMilage);
int countCars(car *list);
void printAvailableForRentList(car *list);
void printRentedList(car *list);
void printInRepairList(car *list);
void exportListsToFiles(car **avilable, car **rented, car **repair);
void freeList(car *list);
void sortByMilage(car **head);
void sortByReturnDates(car **head);
car *swap(car *p1, car *p2);

// Global Variable
float totalIncome = 0.0;

int main(int argc, char *argv[]) {
    // Declare/Initialize variables
    int transactionCode;
    car *availableForRentList = NULL;
    car *rentedList = NULL;
    car *inRepairList = NULL;
    char *textfile = malloc(sizeof(char) * strlen(argv[1]));
    strcpy(textfile, argv[1]);

    // Load initial lists from file passed
    loadListsFromFile(&availableForRentList, &rentedList, &inRepairList, textfile);

    while(true) {
        // Output transaction code options
        printf("\n1: Add a new car to the available-for-rent list,\n"
                 "2: Add a returned car to the available-for-rent list,\n"
                 "3: Add a returned car to the repair list,\n"
                 "4: Transfer a car from the repair list to the available-for-rent list,\n"
                 "5: Rent the first available car,\n"
                 "6: Print all the lists,\n"
                 "7: quit.\n\n");

        // Prompt user for transaction code 
        printf("Enter a transaction code: ");
        do { 
            scanf("%d", &transactionCode);
            if(transactionCode < 1 || transactionCode > 7) {
                printf("Invalid transaction code. Value must be between 0-7: ");
            }
        }while(transactionCode < 1 || transactionCode > 7);

        // Flush input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }

        // Sort lists
        sortByMilage(&availableForRentList);
        sortByReturnDates(&rentedList);

        // Execute respective transaction code action
        printf("\n");
        switch(transactionCode) {
            case 1:
                addNewCarToAvailableForRentList(&availableForRentList);
                break;
            case 2:
                moveCar(&rentedList, &availableForRentList);
                break;
            case 3:
                moveCar(&rentedList, &inRepairList);
                break;  
            case 4:
                moveRepairToAvailable(&inRepairList, &availableForRentList);
                break;  
            case 5:
                rentFirstCar(&availableForRentList, &rentedList);
                break;  
            case 6:
                printAvailableForRentList(availableForRentList);
                printf("\n");
                printRentedList(rentedList);
                printf("\n");
                printInRepairList(inRepairList);
                printf("\n");
                break;  
            default:
                exportListsToFiles(&availableForRentList, &rentedList, &inRepairList);
                printf("Total Income: $%.2f\n", totalIncome);
                exit(0);
        }
    }
    
    // Free lists
    freeList(availableForRentList);
    freeList(rentedList);
    freeList(inRepairList);

    return 0;
}

// Load initial lists from file passed
void loadListsFromFile(car **avilable, car **rented, car **repair, char *textfile) {
    // Declare/Initialize variables
    FILE *loadFile;
    char str[250];
    
    loadFile = fopen(textfile, "r");

    for(int i = 0; i < 15; i++) {
        // Store 5 cars in each list
        fgets(str, 250, loadFile);
        str[strlen(str)] = '\0';
        car *newCar = malloc(sizeof(car));
        sscanf(str, "%s %d %d", newCar->plateNumber, &newCar->milage, &newCar->expectedReturnDate);
        if(i < 5) 
            addToEnd(newCar, avilable);
        else if(i < 10)
            addToEnd(newCar, rented);
        else
            addToEnd(newCar, repair);
    }
    fclose(loadFile);
}

// Add a new car to the available for rent list
void addNewCarToAvailableForRentList(car **availableForRentList) {
    car *newCar = malloc(sizeof(car));

    // Prompt user for plate number
    printf("Enter Plate Number: ");
    scanf("%s", newCar->plateNumber);

    // Flush input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    // Prompt user for milage
    printf("Enter Milage: ");
    scanf("%d", &newCar->milage);

    newCar->expectedReturnDate = -1;

    printf("Added car %s to available-for-rent list.\n", newCar->plateNumber);

    addToEnd(newCar, availableForRentList);
}

// Move car from source list to destination list
void moveCar(car **source, car **dest) {
    // Check if rented list is empty
    if(*source == NULL) {
        printf("There are no cars that are currently rented out.\n");
        return;
    }

    // Declare/Initialize Variables
    car *current = *source;
    char returnedPlateNumber[9];
    int returnedMilage = 0;
    int position = 1;
    float charge = 0;
    bool found = false;

    // Prompt user for plate number
    printf("Enter Plate Number: ");
    fgets(returnedPlateNumber, 9, stdin);
    returnedPlateNumber[strlen(returnedPlateNumber)] = '\0';

    // Flush input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    // Prompt user for milage
    printf("Enter Milage: ");
    scanf("%d", &returnedMilage);
    
    // iterate through source list to find car with specified plate number
    while(current != NULL) {
        if(strcmp(current->plateNumber, returnedPlateNumber) == 0) {
            found = true;
            charge = calculateCharge(current->milage, returnedMilage);
            if(charge < 0) {
                printf("This is not a valid milage.\n");
                return;
            }
            totalIncome += charge;
            car *temp = malloc(sizeof(car));
            strcpy(temp->plateNumber, current->plateNumber);
            temp->milage = returnedMilage;
            temp->expectedReturnDate = -1;
            printf("Returned rented car %s. Milage cost $%.2f\n",temp->plateNumber, charge);
            addToEnd(temp, dest);
            deleteCar(source, position);
            break;
        }
        position++;
        current = current->next;
    }

    if(found == false) {
        printf("Car not found in rented list.\n");
    }
}

// Calculate the charge for a returned car
float calculateCharge(int initialMilage, int newMilage) {
    int difference = newMilage - initialMilage;

    // Flat rate calculation
    int flatRate = (difference/200) * 80;

    // Additional
    int extraKM = difference - ((difference/200) * 200);
    float additional = extraKM * 0.15;

    return (flatRate + additional);
}

// Move a car in the repair list to the available list
void moveRepairToAvailable(car **inRepairList, car **availableForRentList) {
    // Check if rented list is empty
    if(*inRepairList == NULL) {
        printf("There are no cars in repair.\n");
        return;
    }

    car *current = *inRepairList;
    char returnedPlateNumber[9];
    int position = 1;
    bool found = false;

    // Prompt user for plate number
    printf("Enter Plate Number: ");
    fgets(returnedPlateNumber, 9, stdin);
    returnedPlateNumber[strlen(returnedPlateNumber)] = '\0';

    // Flush input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    // Iterate through repair list to find car with specified plate number
    while(current != NULL) {
        if(strcmp(current->plateNumber, returnedPlateNumber) == 0) {
            found = true;
            car *temp = malloc(sizeof(car));
            strcpy(temp->plateNumber, current->plateNumber);
            temp->milage = current->milage;
            temp->expectedReturnDate = -1;
            printf("Moved car %s from repair list to avilable-for-rent list.\n", temp->plateNumber);
            addToEnd(temp, availableForRentList);
            deleteCar(inRepairList, position);
            break;
        }
        position++;
        current = current->next;
    }    

    if(found == false) {
        printf("Car not found in repair list.\n");
    }
}

// Rent the first car in the available list
void rentFirstCar(car **availableForRentList, car **rentedList) {
    int expectedReturnDate = 0;

    // Prompt user for return date
    printf("Enter Expected Return Date: ");
    scanf("%d", &expectedReturnDate);

    car *rented = *availableForRentList;
    car* temp = malloc(sizeof(car));

    // update the return date and move to the rented list
    strcpy(temp->plateNumber, rented->plateNumber);
    temp->milage = rented->milage;
    temp->expectedReturnDate = expectedReturnDate;
    printf("Rented First Available Car: %s\n", temp->plateNumber);
    addToEnd(temp, rentedList);

    deleteCar(availableForRentList, 1);

}

// Append a car to the end of a specified list
void addToEnd(car* newCar, car **list) {
    car *tail = *list;
    newCar->next = NULL;

    // If list is empty, set the head to the new node
    if(*list == NULL) {
        *list = newCar;
    }
    else {
        // Iterate to end of list
        while(tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = newCar;
    }
}

// Delete a car from a specified list given a specified position
void deleteCar(car **list, int position) {
    int numCars = countCars(*list);

    // If we want to delte the first car in the specified list
    if(position == 1) {
        car *temp = *list;
        *list = (*list)->next;
        free(temp);
    }
    // If we want to delete the last car in the specified list
    else if (numCars == position) {
        car *secondLastCar, *carToDelete;
        secondLastCar = *list;
        carToDelete = *list;

        while(carToDelete->next != NULL) {
            secondLastCar = carToDelete;
            carToDelete = carToDelete->next;
        }

        secondLastCar->next = NULL;

        free(carToDelete);
    }
    // Otherwise, we want to delete a car somewhere in the middle of the list
    else {
        car *curr, *prev;

        curr = *list;

        for(int i = 0; i < position-1; i++) {
            prev = curr;
            curr = curr->next;
        }

        prev->next = curr->next;
        free(curr);
    }
}

// Count the cars of a specified list
int countCars(car *list) {
    int count = 0;
    car *temp = list;

    // Iterate through the specified list and count cars
    while(temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}
   
// Print all the cars in the available for rent list
void printAvailableForRentList(car *list) {
    // Check if the list is empty
    if(list == NULL) {
        printf("No cars to display.\n");
        return;
    }
    
    car *temp = list;

    printf("Cars Available For Rent:\n");

    // Iterate through the linked list
    while(temp != NULL) {
        // Output the current node's members
        printf("Plate Number: %s | Milage: %d\n", temp->plateNumber, temp->milage);
        temp = temp->next;
    }
}

// Print all the cars in the rented list
void printRentedList(car *list) {
    // Check if the list is empty
    if(list == NULL) {
        printf("No cars to display.\n");
        return;
    }

    car *temp = list;

    printf("Cars Rented:\n");

    // Iterate through the linked list
    while(temp != NULL) {
        // Output the current node's members
        printf("Plate Number: %s | Milage: %d | Expected Return Date: %d\n", temp->plateNumber, temp->milage, temp->expectedReturnDate);
        temp = temp->next;
    }
}

// Print all the cars in the in repair list
void printInRepairList(car *list) {
    // Check if the list is empty
    if(list == NULL) {
        printf("No cars to display.\n");
        return;
    }

    car *temp = list;

    printf("Cars in Repair:\n");

    // Iterate through the linked list
    while(temp != NULL) {
        // Output the current node's members
        printf("Plate Number: %s | Milage: %d\n", temp->plateNumber, temp->milage);
        temp = temp->next;
    }
}

// Export all the lists to a file
void exportListsToFiles(car **avilable, car **rented, car **repair) {
    FILE *exportFile;

    exportFile = fopen("endCars.txt", "w");

    // Export available list
    car *temp = *avilable;
    fprintf(exportFile, "Available:\n");
    while(temp != NULL) {
        fprintf(exportFile, "%s %d %d\n", temp->plateNumber, temp->milage, temp->expectedReturnDate);
        temp = temp->next;
    }

    // Export rented list
    car *temp2 = *rented;
    fprintf(exportFile, "Rented:\n");
    while(temp2 != NULL) {
        fprintf(exportFile, "%s %d %d\n", temp2->plateNumber, temp2->milage, temp2->expectedReturnDate);
        temp2 = temp2->next;
    }

    // Export repair list
    car *temp3 = *repair;
    fprintf(exportFile, "For Repair:\n");
    while(temp3 != NULL) {
        fprintf(exportFile, "%s %d %d\n", temp3->plateNumber, temp3->milage, temp3->expectedReturnDate);
        temp3 = temp3->next;
    }

    fclose(exportFile);
}

// Free a specified list
void freeList(car *list) {
    // Declare variable
    car *temp = list;

    // Iterate through the linked list
    while(list != NULL) {
        // Free each node
        temp = list;
        list = list->next;
        free(temp);
    }
}

// Sort a list by milage
void sortByMilage(car **head) {
    // Declare variables
    int numCars = countCars(*head);
    car **h;
    int i, j, swapped = 0;

    // Check if the list is empty
    if(*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    // Bubble sort implementation to sort the linked list
    for(i = 0; i <= numCars; i++) {
        h = head;
        swapped = 0;
        for(j = 0; j < numCars - i - 1; j++) {
            car *p1 = *h;
            car *p2 = p1->next;
            if(p1->milage > p2->milage) {
                *h = swap(p1, p2);
                swapped = 1;
            }
            h = &(*h)->next;
        } 
        if(swapped == 0) {
            break;
        }
    }
}

// Sort a list by return date
void sortByReturnDates(car **head) {
    // Declare variables
    int numCars = countCars(*head);
    car **h;
    int i, j, swapped = 0;

    // Check if the list is empty
    if(*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    // Bubble sort implementation to sort the linked list
    for(i = 0; i <= numCars; i++) {
        h = head;
        swapped = 0;
        for(j = 0; j < numCars - i - 1; j++) {
            car *p1 = *h;
            car *p2 = p1->next;
            if(p1->expectedReturnDate > p2->expectedReturnDate) {
                *h = swap(p1, p2);
                swapped = 1;
            }
            h = &(*h)->next;
        } 
        if(swapped == 0) {
            break;
        }
    }
}

// Swap two nodes
car *swap(car *p1, car *p2) {
    // Swap two nodes using a temp variable
    car *temp = p2->next;
    p2->next = p1;
    p1->next = temp;
    return p2;
}