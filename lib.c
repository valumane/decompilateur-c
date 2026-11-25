#include "lib.h"

FILE *openFile(const char *chemin)
{
    return fopen(chemin, "rb");
}

int closeFile(FILE *f)
{
    return fclose(f);
}

void printEntete(FILE *f)
{
    printf("----------------\n");
    // L’en-tête ELF64 occupe les octets 0x00 à 0x3F inclus.
    for (unsigned pos = 0; pos < 0x40; pos++)
    {
        int octet = fgetc(f);

        if (pos % 16 == 0)
        {
            printf("%04X  ", pos);
        }

        printf("%02X%c", (unsigned)octet, pos % 16 == 15 ? '\n' : ' ');
    }
    printf("----------------\n");
}

void printOffsetTable(FILE *f)
{
    const long debut = 0x36A0;
    const int taille = 31 * 64;

    fseek(f, debut, SEEK_SET);
    printf("---------offset table----\n");

    for (int pos = 0; pos < taille; pos++)
    {
        int octet = fgetc(f);

        if (pos % 16 == 0)
            printf("%04lX  ", (unsigned long)(debut + pos));

        printf("%02X%c", (unsigned)octet, pos % 16 == 15 ? '\n' : ' ');
    }
    printf("----------------\n");
}

void printRodata(FILE *f)
{
    const long debut = 0x2000;
    const int taille = 10;

    fseek(f, debut, SEEK_SET);

    printf(".rodata\n%04lX ", (unsigned long)debut);
    for (int i = 0; i < taille; i++)
    {
        int octet = fgetc(f);

        printf(" %02X", (unsigned)octet);
    }
    putchar('\n');
}
