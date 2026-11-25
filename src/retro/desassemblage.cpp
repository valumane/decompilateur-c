#include "desassemblage.hpp"

#include "objdump.hpp"

#include <iostream>
#include <regex>
#include <sstream>

using namespace std;

optional<vector<string>> desassemblerMain(const char* fichier)
{
    string texte;
    if (!objdump({"-d", "-M", "intel", "--no-show-raw-insn", "--disassemble=main", "--", fichier}, texte)) return nullopt;
    if (texte.find("file format elf64-x86-64\n") == string::npos) {
        cerr << "Format attendu : ELF x86-64.\n"; return nullopt;
    }
    istringstream lignes(texte);
    string ligne;
    while (getline(lignes, ligne) && ligne.find(" <main>:") == string::npos) {}
    if (!lignes) { cerr << "Symbole main introuvable.\n"; return nullopt; }
    vector<string> instructions;
    const regex instruction(R"(^\s*[[:xdigit:]]+:\s+(.+?)\s*$)");
    while (getline(lignes, ligne) && !ligne.empty()) {
        smatch m;
        if (!regex_match(ligne, m, instruction)) break;
        instructions.push_back(m[1]);
    }
    return instructions;
}
