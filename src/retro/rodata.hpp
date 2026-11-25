#pragma once

#include <map>
#include <optional>
#include <string>

using Octets = std::map<unsigned long long, unsigned char>;

std::optional<Octets> chargerDonnees(const char* fichier);
std::optional<std::string> chaineC(const Octets& octets, unsigned long long adresse);
