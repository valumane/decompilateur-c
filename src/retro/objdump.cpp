#include "objdump.hpp"

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

bool objdump(vector<string> arguments, string& sortie)
{
    arguments.insert(arguments.begin(), "objdump");
    vector<char*> commande;
    for (auto& argument : arguments) commande.push_back(argument.data());
    commande.push_back(nullptr);
    int canal[2];
    if (pipe(canal) < 0) { perror("pipe"); return false; }
    pid_t enfant = fork();
    if (enfant == 0) {
        close(canal[0]);
        if (dup2(canal[1], STDOUT_FILENO) < 0) { perror("dup2"); _exit(1); }
        if (canal[1] != STDOUT_FILENO) close(canal[1]);
        setenv("LC_ALL", "C", 1);
        execvp(commande[0], commande.data());
        perror("objdump");
        _exit(127);
    }
    close(canal[1]);
    if (enfant < 0) { perror("fork"); close(canal[0]); return false; }
    char tampon[4096];
    ssize_t n;
    while ((n = read(canal[0], tampon, sizeof tampon)) != 0) {
        if (n > 0) sortie.append(tampon, n);
        else if (errno != EINTR) { perror("read"); break; }
    }
    close(canal[0]);
    int statut;
    while (waitpid(enfant, &statut, 0) < 0) {
        if (errno != EINTR) { perror("waitpid"); return false; }
    }
    return n == 0 && WIFEXITED(statut) && WEXITSTATUS(statut) == 0;
}
