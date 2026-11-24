# decompilateur-c

Projet de décompilateur pour les exécutables Linux x86-64. L’objectif est de traduire la fonction `main` en pseudo-C lisible. Le prototype utilise `objdump` pour le désassemblage et fournit `hexa` pour lire les octets d’un fichier en hexadécimal et en ASCII.

## Compiler et essayer

Sous Linux x86-64, avec GCC, G++ et GNU binutils, lancer depuis la racine du projet :

```sh
gcc -O0 exemple.c -o exemple
g++ retro.cpp -o retro
g++ hexa.cpp -o hexa
```

La capture de la sortie d’`objdump` dans `retro` reste à corriger. Pour explorer l’exemple dès maintenant :

```sh
./hexa ./exemple | head -n 4                 # Premiers octets du fichier ELF
objdump -M intel --disassemble=main ./exemple  # Assembleur de main
```

[Guide de lecture du désassemblage](explication_retro.txt) · [Liste des tâches](TODO.md)
