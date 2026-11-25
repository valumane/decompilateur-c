# TODO

- [ ] Vérifier la signature ELF, la classe 64 bits et l’ordre des octets avant la lecture. Tester le refus du fichier texte `example/test` et d’un en-tête tronqué.
- [ ] Lire la position de la table des sections, le nombre d’entrées et leur taille dans l’en-tête ELF.
- [ ] Retrouver `.rodata` et `.text` par leur nom, puis utiliser la position et la taille de chaque section pour en afficher les octets.
- [ ] Retrouver `main` dans la table des symboles et relier son appel à `printf` à la chaîne `hello` de `.rodata`.
