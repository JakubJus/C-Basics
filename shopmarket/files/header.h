
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100 + 1
#define MAX_NAME_SIZE 20 + 1

typedef struct {
    int itemNumber;
    char *name; 
    int stock;
} Item;

void printItems(Item itemsInStock[], int shelf);
void registerItem(Item **newItems, int *pShelf);
void searchItem(Item itemsInStock[], int shelf, char quit);
void searchByItemNumber(Item itemsInStock[], int shelf);
void searchByName(Item itemsInStock[], int shelf);
void searchByStock(Item itemsInStock[], int shelf);
int compareItemNumber(const void *a, const void *b);
int compareStock(const void *a, const void *b);
int compareName(const void *a, const void *b);
void sortItems(Item itemsExistingInStock[], int shelf);
void updateStock(Item itemsInStock[], int *pPlace);
void deleteItem(Item itemsInStock[], int *pShelf);
void discardInput();

#endif