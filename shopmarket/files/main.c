
#include "header.h"
#include "filefunctions.h"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char cmd;
    int shelf = 0;
    Item *stock = malloc(SIZE * sizeof(Item)); //finding space for storage

    if (stock == NULL) {
        puts("Memory allocation failed");
        return EXIT_FAILURE;
    }

    printf("You have started the inventory program v.01\n");
    printf("Using File: %s\n", filename);

    loadItems(&stock, &shelf, filename);
    do {
        printf("\n(1) Register Items\n(2) Print Items\n(3) Search Items\n"
               "(4) Update Stock\n(5) Sort Items\n(6) Delete Items\n(7) Quit\n> ");

        cmd = getchar();
        discardInput();

        switch (cmd) {
            case '1':
                registerItem(&stock, &shelf);
                break;
            case '2':
                printItems(stock, shelf);
                break;
            case '3':
                searchItem(stock, shelf, 'a');
                break;
            case '4':
                updateStock(stock, &shelf);
                break;
            case '5':
                sortItems(stock, shelf);
                break;
            case '6':
                deleteItem(stock, &shelf);
                break;
            case '7':
                puts("\nQUITTING...");
                
            default:
                puts("Invalid option. Please enter a valid option.");
                break;
        }
    } while (cmd != '7');

    saveItems(stock, shelf, filename);
    free(stock); //removing the storage and saves as a file
    return 0;
}