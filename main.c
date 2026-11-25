#include "lib.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage : %s <fichier>\n", argv[0]);
        return 1;
    }

    FILE *f = openFile(argv[1]);
    if (f == NULL)
    {
        perror(argv[1]);
        return 1;
    }

    printEntete(f);
    //printOffsetTable(f);
    printRodata(f);
    closeFile(f);
    return 0;
}
