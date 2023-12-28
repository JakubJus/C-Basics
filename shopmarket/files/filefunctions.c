#include "filefunctions.h"

void loadItems(Item **oldItems, int *pPlace, char file[]) {
    FILE *pBf;
    Item item;

    if ((pBf = fopen(file, "r")) != NULL) {
        printf("[Loading ");
        while (fscanf(pBf, "%d %19s %d", &item.itemNumber, item.name, &item.stock) == 3) {
            (*pPlace)++;
            *oldItems = realloc(*oldItems, (*pPlace) * sizeof(Item));
            if (*oldItems == NULL) {
                puts("Memory allocation failed");
                exit(EXIT_FAILURE);
            }

            // Adjusting the name reading and storing
            size_t len = strlen(item.name);
            (*oldItems)[(*pPlace) - 1].name = malloc(len + 1);
            if ((*oldItems)[(*pPlace) - 1].name == NULL) {
                puts("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            strcpy((*oldItems)[(*pPlace) - 1].name, item.name);
            (*oldItems)[(*pPlace) - 1].itemNumber = item.itemNumber;
            (*oldItems)[(*pPlace) - 1].stock = item.stock;

            printf(".");
        }
        fclose(pBf);
        puts("]\n");
    } else {
        perror("Unable to open file for reading");
    }
}

void saveItems(Item newItems[], int place, char file[]) {
    FILE *pBf;

    if ((pBf = fopen(file, "w")) != NULL) {
        printf("[Saving ");
        for (int k = 0; k < place; k++) {
            fprintf(pBf, "%d %s %d\n", newItems[k].itemNumber, newItems[k].name, newItems[k].stock);
            printf(".");
        }
        fclose(pBf);
        puts("]\n");  
    } else {
        perror("Unable to save");
    }
}
