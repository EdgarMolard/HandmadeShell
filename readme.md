# Handmade Shell

Projet visant a recreer un shell minimaliste en C afin d'approfondir mes acquis en bas niveau et de decouvrir de nouvelles logiques.

## Compilation

Le projet est desormais decoupe en plusieurs fichiers C.

- Construire l'executable : `make`
- Nettoyer les fichiers objets et l'executable : `make clean`

## Structure du projet

- `include/shell.h` : constantes et prototypes partages.
- `src/main.c` : boucle principale du shell (prompt, lecture, sortie).
- `src/parser.c` : decoupage de la ligne en tokens.
- `src/execute.c` : execution simple + gestion des operateurs `&&` et `||`.
- `src/builtins/` : un fichier C par builtin (`run_cd.c`, `run_ls.c`, etc.).

Au depart, je suis parti d'un projet educatif GitHub, Build_your_own_shell. Je l'ai trouve peu guide et trop complexe pour un debutant. Lien vers le projet initial : [BUILD_YOUR_OWN_SHELL](https://github.com/tokenrove/build-your-own-shell).

A la place, je m'appuie sur l'IA avec le processus suivant :

1. Je precise a l'IA la commande que je souhaite integrer.
2. Je lui demande d'expliquer la logique de fonctionnement, ainsi que le nom des fonctions utiles et leurs prototypes pour comprendre leur utilisation.
3. Je fais un ou deux premiers jets sans aide supplementaire.
4. Si cela ne fonctionne pas, je demande ce qui bloque et la logique a suivre pour corriger moi-meme.

## Commandes presentes

Commandes actuellement disponibles dans le shell :

- `exit` : quitte le shell.
- `cd` : change le repertoire courant.
- `pwd` : affiche le repertoire courant.
- `ls` : liste le contenu d'un repertoire (implementation simplifiee).
- `echo` : affiche les arguments.
- `cat` : affiche le contenu d'un fichier (version simple).
- `clear` : efface le contenu du terminal + remet le curseur en haut à gauche
- `true` : retourne un succes (code de sortie `0`).
- `false` : retourne un echec (code de sortie `1`).

## Operateurs logiques

Le shell gere les operateurs suivants :

- `&&` : execute la commande de droite seulement si la commande de gauche reussit (code `0`).
- `||` : execute la commande de droite seulement si la commande de gauche echoue (code non nul).

Exemples :

- `true && echo ok`
- `false || echo ok`
- `true && false || echo fallback`

Commande speciale :

- `ping` : ce n'est pas un vrai builtin. La commande est lancee via `fork` + `execvp` (appel d'un programme externe), donc c'est volontairement un peu de la "triche" et non une implementation interne complete de `ping`.