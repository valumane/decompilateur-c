#include "traduction.hpp"

#include "rodata.hpp"

#include <regex>
#include <sstream>

using namespace std;

optional<string> traduire(const vector<string>& instructions, const char* fichier)
{
    const regex charger(R"(lea\s+(rax|rdi),\[rip[^\]]*\]\s*#\s*([[:xdigit:]]+).*)");
    const regex constante(R"(mov\s+eax,(0x[[:xdigit:]]{1,8}|0))");
    const regex appel(R"(call\s+[[:xdigit:]]+ <(puts|printf)@plt>)");
    const regex cadre(R"((endbr64|push\s+rbp|mov\s+rbp,rsp|pop\s+rbp|nop))");
    optional<Octets> donnees;
    optional<string> rax, rdi;
    optional<long long> retour;
    ostringstream code;
    bool affiche = false;
    for (size_t i = 0; i < instructions.size(); ++i) {
        const string& op = instructions[i];
        smatch m;
        if (regex_match(op, cadre)) continue;
        if (regex_match(op, m, charger)) {
            if (!donnees) {
                donnees = chargerDonnees(fichier);
                if (!donnees) return nullopt;
            }
            auto valeur = chaineC(*donnees, stoull(m[2], nullptr, 16));
            if (m[1] == "rax") { rax = valeur; retour.reset(); }
            else rdi = valeur;
        } else if (regex_match(op, regex(R"(mov\s+rdi,rax)"))) {
            rdi = rax;
        } else if (regex_match(op, m, constante)) {
            auto valeur = stoll(m[1], nullptr, 0);
            retour = valeur >= 0x80000000LL ? valeur - 0x100000000LL : valeur;
            rax.reset();
        } else if (regex_match(op, regex(R"(xor\s+eax,eax)"))) {
            retour = 0;
            rax.reset();
        } else if (regex_match(op, m, appel) && rdi) {
            // Un format avec arguments demande aussi de reconstruire ces arguments.
            if (m[1] == "printf" && rdi->find('%') != string::npos) return nullopt;
            code << "    " << m[1] << '(' << *rdi << ");\n";
            affiche = true;
            retour.reset(); rax.reset(); rdi.reset();
        } else if (op == "ret" && retour && i + 1 == instructions.size()) {
            code << "    return " << *retour << ";\n}\n";
            return (affiche ? string("#include <stdio.h>\n\n") : string())
                + "int main(void) {\n" + code.str();
        } else return nullopt;
    }
    return nullopt;
}
