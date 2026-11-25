#ifndef LIB_H
#define LIB_H

#include <stdio.h>

FILE *openFile(const char *chemin);
int closeFile(FILE *f);

void printEntete(FILE *f);
void printOffsetTable(FILE *f);
void printRodata(FILE *f);

#endif
