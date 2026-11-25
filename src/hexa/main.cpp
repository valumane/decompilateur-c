#include "affichage.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage : " << argv[0] << " <fichier>\n";
        return 1;
    }

    std::ifstream fichier(argv[1], std::ios::binary);
    if (!fichier) {
        std::cerr << "Impossible d'ouvrir le fichier : " << argv[1] << '\n';
        return 1;
    }

    afficherHexadecimal(fichier, std::cout);
    if (fichier.bad()) {
        std::cerr << "Erreur pendant la lecture du fichier.\n";
        return 1;
    }
}
