# Décompilateur C

Ce projet explore la décompilation en lisant un exécutable ELF64 octet par octet. Le lecteur affiche en hexadécimal les 64 octets de l’en-tête et le contenu de la section `.rodata`. Pour l’instant, sa position et sa taille sont fixées pour le binaire fourni.

Avec Make et un compilateur C, lancer depuis la racine du projet :

```sh
make
./a.out example/exemple
```

## Analyse de l’exemple

**`.rodata` contient les données en lecture seule.** Dans `example/exemple`, elle commence à la position `0x2000` et occupe 10 octets. Voici la ligne affichée par le lecteur :

```text
2000  01 00 02 00 68 65 6C 6C 6F 00
```

À partir de `0x2004`, les octets `68 65 6C 6C 6F` donnent les lettres `hello` en ASCII. Le dernier `00` termine la chaîne C.

**`.text` contient les instructions machine.** Dans cet exemple, elle commence à `0x1060` et occupe 268 octets. Le désassemblage de `main` montre comment le programme utilise la chaîne :

| Adresse | Instruction | Effet |
| --- | --- | --- |
| `0x1151` | `lea rax, [rip+0xeac]` | Calcule l’adresse `0x2004` où commence `hello`. |
| `0x1158` | `mov rdi, rax` | Place cette adresse dans le registre du premier argument. |
| `0x1160` | `call printf@plt` | Appelle `printf` avec la chaîne. |
| `0x1165` | `mov eax, 0` | Prépare la valeur de retour de `main`. |

Cela correspond en C à `printf("hello");` suivi de `return 0;`.

**Le fichier texte `example/test`** contient cinq octets : `61 62 63 64 65`, soit `abcde` en ASCII, sans saut de ligne final.

[Notes sur l’en-tête ELF](explication_elf_header.txt) · [Prochaines étapes](TODO.md)
