#include "affichage.hpp"

#include <array>
#include <cctype>
#include <cstdint>
#include <iomanip>
#include <istream>
#include <ostream>

void afficherHexadecimal(std::istream& fichier, std::ostream& sortie)
{
    std::array<unsigned char, 16> octets{};
    std::uint64_t adresse = 0;

    while (fichier) {
        fichier.read(reinterpret_cast<char*>(octets.data()), octets.size());
        const auto taille = fichier.gcount();
        if (taille <= 0) break;

        sortie << std::hex << std::uppercase << std::setfill('0')
                  << std::setw(8) << adresse << "  ";
        for (std::streamsize i = 0; i < 16; ++i) {
            if (i < taille)
                sortie << std::setw(2) << static_cast<unsigned>(octets[i]) << ' ';
            else
                sortie << "   ";
            if (i == 7) sortie << ' ';
        }
        sortie << " |";
        for (std::streamsize i = 0; i < taille; ++i) {
            const unsigned char c = octets[i];
            sortie << (std::isprint(c) ? static_cast<char>(c) : '.');
        }
        sortie << "|\n";
        adresse += static_cast<std::uint64_t>(taille);
    }
}
