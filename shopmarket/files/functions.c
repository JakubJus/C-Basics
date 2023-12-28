#include "header.h"

void printItems(Item itemsInStock[], int shelf) {
    if (shelf == 0) {
        printf("No registered items\n");
        return;
    }

    printf("%-15s%-20s%s\n", "Item Number", "Name", "Stock");
    for (int i = 0; i < shelf; i++) {
        printf("%-15d%-20s%d\n", itemsInStock[i].itemNumber, itemsInStock[i].name, itemsInStock[i].stock);
    }
}

void registerItem(Item **newItems, int *pShelf) {
    Item newItem;
    int check, i = 0;

    printf("Enter item number (0 to exit): ");
    scanf("%d", &check);
    discardInput();

    if (check == 0) {
        return;
    }

    for (int j = 0; j < *pShelf; j++) {
        if (check == (*newItems)[j].itemNumber) {
            puts("Non-unique item number");
            registerItem(newItems, pShelf);
            return;
        }
    }

    newItem.itemNumber = check;

    printf("Enter name: ");
    newItem.name = malloc(MAX_NAME_SIZE);
    fgets(newItem.name, MAX_NAME_SIZE, stdin);
    newItem.name[strcspn(newItem.name, "\n")] = 0;

    while (newItem.name[i] != '\0') {
        newItem.name[i] = tolower(newItem.name[i]);
        i++;
    }

    printf("Enter stock: ");
    scanf("%d", &newItem.stock);
    discardInput();

    (*pShelf)++;
    *newItems = realloc(*newItems, (*pShelf) * sizeof(Item));
    if (*newItems == NULL) {
        puts("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    (*newItems)[(*pShelf) - 1] = newItem;

    printf("Item registered successfully\n");
}



void searchItem(Item itemsInStock[], int shelf, char quit) {
    int choice;
    printf("\nSearch by:\n");
    printf("(1) Item Number\n");
    printf("(2) Name\n");
    printf("(3) Stock\n");
    printf("(4) Quit\n");
    printf("> ");

    scanf("%d", &choice);
    discardInput();

    switch (choice) {
        case 1:
            searchByItemNumber(itemsInStock, shelf);
            break;
        case 2:
            searchByName(itemsInStock, shelf);
            break;
        case 3:
            searchByStock(itemsInStock, shelf);
            break;
        case 4:
            if (quit == 'q') {
                return;
            } else {
                searchItem(itemsInStock, shelf, quit);
                break;
            }
        default:
            printf("Invalid choice\n");
            searchItem(itemsInStock, shelf, quit);
            break;
    }
}

void searchByItemNumber(Item itemsInStock[], int shelf) {
    int num;
    printf("Enter item number to search: ");
    scanf("%d", &num);
    discardInput();

    for (int i = 0; i < shelf; i++) {
        if (itemsInStock[i].itemNumber == num) {
            printf("Item found:\n");
            printf("%-15s%-20s%s\n", "Item Number", "Name", "Stock");
            printf("%-15d%-20s%d\n", itemsInStock[i].itemNumber, itemsInStock[i].name, itemsInStock[i].stock);
            return;
        }
    }

    printf("No item found with item number %d.\n", num);
}

void searchByName(Item itemsInStock[], int shelf) {
    char searchName[MAX_NAME_SIZE];
    printf("Enter name to search: ");
    fgets(searchName, MAX_NAME_SIZE, stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    for (int i = 0; i < shelf; i++) {
        if (strcasecmp(itemsInStock[i].name, searchName) == 0) {
            printf("Item found:\n");
            printf("%-15s%-20s%s\n", "Item Number", "Name", "Stock");
            printf("%-15d%-20s%d\n", itemsInStock[i].itemNumber, itemsInStock[i].name, itemsInStock[i].stock);
            return;
        }
    }

    printf("No item found with the name %s.\n", searchName);
}

void searchByStock(Item itemsInStock[], int shelf) {
    int stock;
    printf("Enter stock to search: ");
    scanf("%d", &stock);
    discardInput();

    for (int i = 0; i < shelf; i++) {
        if (itemsInStock[i].stock == stock) {
            printf("Item found:\n");
            printf("%-15s%-20s%s\n", "Item Number", "Name", "Stock");
            printf("%-15d%-20s%d\n", itemsInStock[i].itemNumber, itemsInStock[i].name, itemsInStock[i].stock);
            return;
        }
    }

    printf("No item found with stock %d.\n", stock);
}

int compareItemNumber(const void *a, const void *b) {
    return ((Item *)a)->itemNumber - ((Item *)b)->itemNumber;
}

int compareStock(const void *a, const void *b) {
    return ((Item *)a)->stock - ((Item *)b)->stock;
}

int compareName(const void *a, const void *b) {
    return strcmp(((Item *)a)->name, ((Item *)b)->name);
}

void sortItems(Item itemsExistingInStock[], int shelf) {
    char cmd;

    printf("Sort items by item number (1)\nSort items by name (2)\nSort items by stock (3)\n> ");
    scanf(" %c", &cmd);
    discardInput();

    switch (cmd) {
        case '1':
            qsort(itemsExistingInStock, shelf, sizeof(Item), compareItemNumber);
            printf("\nItems sorted by item number\n");
            break;
        case '2':
            qsort(itemsExistingInStock, shelf, sizeof(Item), compareName);
            printf("\nItems sorted by name\n");
            break;
        case '3':
            qsort(itemsExistingInStock, shelf, sizeof(Item), compareStock);
            printf("\nItems sorted by stock\n");
            break;
        default:
            printf("Invalid input\n");
            sortItems(itemsExistingInStock, shelf);
            return;
    }
}

void updateStock(Item itemsInStock[], int *pPlace) {
    int number, quantity;
    char quit = 'a'; 

    searchItem(itemsInStock, *pPlace, quit); 

    printf("Enter item number: ");
    scanf("%d", &number);
    discardInput();

    for (int k = 0; k < *pPlace; k++) {
        if (itemsInStock[k].itemNumber == number) {
            printf("Enter the quantity to update (use '-' to decrease): ");
            scanf("%d", &quantity);
            discardInput();

            itemsInStock[k].stock += quantity;
            printf("Stock for %s has been updated to %d.\n", itemsInStock[k].name, itemsInStock[k].stock);
            return;
        }
    }

    printf("No item found with item number %d.\n", number);
}

void deleteItem(Item itemsInStock[], int *pShelf) {
    int num;

    if (*pShelf == 0) {
        printf("No registered items\n");
        return;
    }

    searchItem(itemsInStock, *pShelf, 'a');

    printf("Enter item number (or 0 to cancel): ");
    scanf("%d", &num);
    discardInput();

    if (num == 0) {
        printf("Deletion canceled\n");
        return;
    }

    for (int i = 0; i < *pShelf; i++) {
        if (itemsInStock[i].itemNumber == num) {
            free(itemsInStock[i].name);  

            
            for (int j = i; j < *pShelf - 1; j++) {
                itemsInStock[j] = itemsInStock[j + 1];
            }
            (*pShelf)--;
            
            printf("Item with item number %d has been deleted.\n", num);
            return;
        }
    }

    printf("No item found with item number %d.\n", num);
}

void discardInput() {
    char cmd;
    cmd = getchar();
    if (cmd != '\n') {
        discardInput();
    }
}