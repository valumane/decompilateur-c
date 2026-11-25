# decompilateur-c

Projet de décompilateur pour les exécutables Linux x86-64. L’objectif est de traduire la fonction `main` en pseudo-C lisible. Le prototype utilise `objdump` pour le désassemblage et fournit `hexa` pour lire les octets d’un fichier en hexadécimal et en ASCII.

## Compiler et essayer

Sous Linux x86-64, avec Make, GCC, G++ et GNU binutils, lancer depuis la racine du projet :

```sh
make
```

Pour reconstruire le `main` du programme compilé :

```sh
./build/retro ./build/exemple
```

Avec l’exemple recompilé ci-dessus, la sortie contient `printf("hello");` et `return 0;`. Le prototype reconnaît les chaînes constantes de `.rodata`, les appels simples à `printf` et `puts`, et les retours entiers constants. Il faut un binaire ELF x86-64 avec le symbole `main`. Si la traduction est incomplète, `retro` affiche les instructions observées et renvoie un code d’échec.

Pour consulter tout le désassemblage, utiliser `./build/retro --asm ./build/exemple`.

## Organisation

- `src/retro/` contient la commande, l’appel à `objdump`, l’extraction des instructions de `main`, la lecture de `.rodata` et la traduction en pseudo-C.
- `src/hexa/` contient la commande de lecture hexadécimale et le formatage de sa sortie.
- `exemples/exemple.c` sert de programme d’essai.
- `build/` reçoit les trois exécutables produits par `make`.

[Rôle de chaque fichier](FICHIERS.md) · [Guide de lecture du désassemblage](explication_retro.txt) · [Liste des tâches](TODO.md)
