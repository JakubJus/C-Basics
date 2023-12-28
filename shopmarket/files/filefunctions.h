#ifndef FILEFUNCTIONS_H
#define FILEFUNCTIONS_H
#include <stdio.h>
#include "header.h" 

void loadItems(Item **oldItems, int *pPlace, char file[]);
void saveItems(Item newItems[], int place, char file[]);

#endif