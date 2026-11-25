#include "desassemblage.hpp"
#include "objdump.hpp"
#include "traduction.hpp"

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    string texte;
    if (argc == 3 && string(argv[1]) == "--asm") {
        if (!objdump({"-d", "-M", "intel", "--", argv[2]}, texte)) return 1;
        cout << texte;
        return 0;
    }
    if (argc != 2) { cerr << "Usage : retro [--asm] <executable>\n"; return 1; }
    auto instructions = desassemblerMain(argv[1]);
    if (!instructions) return 1;
    if (auto code = traduire(*instructions, argv[1])) { cout << *code; return 0; }
    cerr << "Traduction de main incomplète. Instructions observées :\n";
    for (const auto& op : *instructions) cerr << "    " << op << '\n';
    return 1;
}
