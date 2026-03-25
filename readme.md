# Handmade Shell

Projet visant a recreer un shell minimaliste en C afin d'approfondir mes acquis en bas niveau et de decouvrir de nouvelles logiques.

Au depart, je suis parti d'un projet educatif GitHub, Build_your_own_shell. Je l'ai trouve peu guide et trop complexe pour un debutant. J'en ai conserve les fichiers dans le depot au cas ou.

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

Commande speciale :

- `ping` : ce n'est pas un vrai builtin. La commande est lancee via `fork` + `execvp` (appel d'un programme externe), donc c'est volontairement un peu de la "triche" et non une implementation interne complete de `ping`.