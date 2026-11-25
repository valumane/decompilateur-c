#include "rodata.hpp"

#include "objdump.hpp"

#include <iomanip>
#include <sstream>

using namespace std;

optional<Octets> chargerDonnees(const char* fichier)
{
    string texte;
    if (!objdump({"-s", "-j", ".rodata", "--", fichier}, texte)) return nullopt;
    Octets octets;
    istringstream lignes(texte);
    string ligne;
    while (getline(lignes, ligne) && ligne != "Contents of section .rodata:") {}
    while (getline(lignes, ligne)) {
        istringstream champs(ligne);
        unsigned long long adresse;
        if (!(champs >> hex >> adresse) || champs.get() != ' ') continue;
        // Les groupes hexadécimaux et l’aperçu ASCII sont séparés par deux espaces.
        string reste;
        getline(champs, reste);
        istringstream groupes(reste.substr(0, reste.find("  ")));
        string groupe;
        while (groupes >> groupe) {
            for (size_t i = 0; i + 1 < groupe.size(); i += 2)
                octets[adresse++] = stoul(groupe.substr(i, 2), nullptr, 16);
        }
    }
    return octets;
}

optional<string> chaineC(const Octets& octets, unsigned long long adresse)
{
    ostringstream literal;
    literal << '"';
    for (auto it = octets.find(adresse); it != octets.end() && it->first == adresse; ++it, ++adresse) {
        unsigned char c = it->second;
        if (c == 0) return literal.str() + '"';
        if (c == '"' || c == '\\') literal << '\\' << c;
        else if (c == '\n') literal << "\\n";
        else if (c >= 32 && c <= 126) literal << c;
        else literal << '\\' << oct << setw(3) << setfill('0') << unsigned(c);
    }
    return nullopt;
}
