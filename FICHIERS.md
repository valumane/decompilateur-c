# Quel fichier fait quoi ?

| Fichier | Rôle |
| --- | --- |
| [src/retro/main.cpp](src/retro/main.cpp) | Lit les arguments de `retro` et choisit entre le pseudo-C et le mode `--asm`. |
| [src/retro/objdump.cpp](src/retro/objdump.cpp) | Lance `objdump` et récupère sa sortie. |
| [src/retro/desassemblage.cpp](src/retro/desassemblage.cpp) | Vérifie le format ELF x86-64 et extrait les instructions de la fonction `main`. |
| [src/retro/rodata.cpp](src/retro/rodata.cpp) | Lit les octets de la section `.rodata` et retrouve une chaîne à partir de son adresse. |
| [src/retro/traduction.cpp](src/retro/traduction.cpp) | Traduit les instructions reconnues en pseudo-C. C’est ici qu’on ajoute une règle de traduction. |
| [src/hexa/main.cpp](src/hexa/main.cpp) | Lit les arguments de `hexa` et ouvre le fichier à afficher. |
| [src/hexa/affichage.cpp](src/hexa/affichage.cpp) | Affiche les octets par lignes de 16, en hexadécimal et en ASCII. |
| [exemples/exemple.c](exemples/exemple.c) | Petit programme qui affiche `hello` et sert à essayer le décompilateur. |
| [Makefile](Makefile) | Compile `retro`, `hexa` et `exemple` dans `build/`. |

Les fichiers `.hpp` déclarent les fonctions que les autres fichiers peuvent appeler. Leur implémentation se trouve dans le `.cpp` du même nom.

Le [README](README.md) explique comment lancer le projet, le [guide du désassemblage](explication_retro.txt) commente un exemple d’assembleur et le [TODO](TODO.md) liste les tâches. Le fichier [.gitignore](.gitignore) exclut `build/` du suivi Git. Les fichiers `retro`, `hexa`, `exemple` et `a.out` à la racine sont des binaires déjà compilés.
