# TODO du décompilateur C

Premier jalon : compiler `exemple.c`, lancer `./retro ./exemple` et obtenir un pseudo-C qui montre l’affichage de `hello` et le `return 0`. Pour ce jalon, cibler les exécutables Linux ELF x86-64 qui conservent le symbole `main`.

- [ ] **Corriger la capture de la sortie d’`objdump` dans `retro.cpp`.** Créer le tube avec `pipe(sortie)` avant `fork()`, vérifier les erreurs et transmettre un code d’échec si `objdump` échoue.
- [ ] **Rendre l’exemple reproductible.** Ajouter un `Makefile` pour compiler `retro`, `hexa` et `exemple`. Mettre à jour `explication_retro.txt` avec le désassemblage obtenu à partir de l’actuel `exemple.c`, qui affiche `hello`.
- [ ] **Isoler la fonction `main`.** Utiliser `objdump --disassemble=main`, puis extraire l’adresse, le nom et les opérandes de chaque instruction. Signaler l’absence du symbole `main`.
- [ ] **Traduire le premier exemple en pseudo-C.** Retrouver la chaîne `hello` dans `.rodata`, suivre son adresse jusqu’à l’appel d’affichage et reconnaître la valeur de retour. Conserver les instructions encore inconnues sous forme de commentaires assembleur.
- [ ] **Vérifier le résultat avec `make test`.** Recompiler l’exemple et vérifier que le pseudo-C contient l’appel d’affichage avec `hello` et l’instruction `return 0`. Vérifier aussi que `retro` renvoie un code d’échec pour un fichier absent ou invalide.
- [ ] **Étendre la traduction.** Prendre en charge successivement une addition de deux arguments, un `if/else` et une boucle. Ajouter pour chaque cas un petit programme C et le pseudo-C attendu.
