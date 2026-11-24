#include <array>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

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

    std::array<unsigned char, 16> octets{};
    std::uint64_t adresse = 0;

    while (fichier) {
        fichier.read(reinterpret_cast<char*>(octets.data()), octets.size());
        const auto taille = fichier.gcount();
        if (taille <= 0) break;

        std::cout << std::hex << std::uppercase << std::setfill('0')
                  << std::setw(8) << adresse << "  ";
        for (std::streamsize i = 0; i < 16; ++i) {
            if (i < taille)
                std::cout << std::setw(2) << static_cast<unsigned>(octets[i]) << ' ';
            else
                std::cout << "   ";
            if (i == 7) std::cout << ' ';
        }
        std::cout << " |";
        for (std::streamsize i = 0; i < taille; ++i) {
            const unsigned char c = octets[i];
            std::cout << (std::isprint(c) ? static_cast<char>(c) : '.');
        }
        std::cout << "|\n";
        adresse += static_cast<std::uint64_t>(taille);
    }

    if (fichier.bad()) {
        std::cerr << "Erreur pendant la lecture du fichier.\n";
        return 1;
    }
}
