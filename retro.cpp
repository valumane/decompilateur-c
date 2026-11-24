#include <cerrno>
#include <cstring>
#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage : " << argv[0] << " <executable>\n";
        return 1;
    }

    int sortie[2];


    const pid_t enfant = fork();


    if (enfant == 0)
    {
        close(sortie[0]);
        dup2(sortie[1], STDOUT_FILENO);
        close(sortie[1]);
        execlp("objdump", "objdump", "-d", "-M", "intel", "--", argv[1],
               static_cast<char *>(nullptr));
        _exit(127);
    }

    close(sortie[1]);
    char tampon[4096];
    ssize_t lus;
    while ((lus = read(sortie[0], tampon, sizeof(tampon))) > 0)
        std::cout.write(tampon, lus);
    close(sortie[0]);

    int statut = 0;
    waitpid(enfant, &statut, 0);

    std::cerr << "\nCes instructions assembleur ne permettent pas de retrouver exactement le code C d'origine.\n";
    return 0;
}
