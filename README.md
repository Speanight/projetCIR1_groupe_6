# projetCIR1_groupe_6
### Mise en contexte, objectif du projet
Ce github est un projet de fin d'année exécuté en groupes de trois élèves choisis aléatoirement.

L'objectif était de réaliser une filmothèque, et consistait alors à la réalisation d'un site web en HTML, CSS et JS pour le front-end, ainsi qu'une lecture d'une base de données en C pour le back-end.

### Comment exécuter le fichier
Le github est constitué d'un dossier C ainsi qu'un dossier "htmlweb".
- Dans le dossier C, executez le "main.c".
  - Notez qu'il est possible de modifier l'emplacement des fichiers tels que la base de données, l'export et la lecture des fichiers renvoyés par la page web grâce aux variables se situant au début de la fonction main, lisez les commentaires pour trouver quels fichiers modifier !
- Démarrez la page "accueil.html". Celle-ci possède notre page d'accueil pour la filmothèque.
- En cliquant sur "Aller à la filmothèque", ou sur "filmothèque" dans le header, vous vous dirigerez sur la partie de recherche de la filmothèque.
  - 3 types de recherche vous serons alors proposés ainsi que 2 boutons. Ecrivez un réalisateur avec des lettres, une durée en nombre entier, ou un intervalle sous la forme "nombre entier;nombre entier" (sans les guillemets).
  - L'exécution d'une des fonctions entraînera le chargement des résultats sur le C, puis l'affichage sous la page web après quelques secondes.
    - Le temps d'exécution s'exécutera peu de temps après.

### Mode admin
- Le mode "admin" peut être accedé grâce au symbole figurant en bas à droite de la page.
  - Un mot de passe vous sera alors demandé, entrez "motdepasse".
- Vous aurez alors la possibilité de fermer le serveur. Cela alors pour effet de libérer la mémoire liée à l'entière base de données, ainsi que d'arrêter le code C.
- Vous aurez également la possibilité d'ajouter un film à la base de données.
  - 📌️ Une fois tout les champs correctement remplis (titre, realisateur, duree, genre), il vous sera demandé si vous souhaitez écrire le nouveau film dans la base de données.
    - Ecrire "Y" entraînera l'ajout du film dans la base de données.
    - Ecrire "N" entraînera l'ajout temporaire du film : autrement dit, il figurera dans la base de données en C, mais sera **définitivement supprimé** une fois le serveur fermé !

### Limitations et informations
- 🔎 Assurez-vous que votre base de données respecte la forme suivante : realisateur;titre;duree;genre, avec "duree" étant un entier entre 0 et 1200.
  - ✔️  Si vous souhaitez ajouter des films d'une durée supérieure à 1200, il vous est possible de modifier la valeur max. dans database.h, tout en haut du fichier, à *"#define DUREE_MAX 1200"*.
  - ⚠️ Notez que plus la valeur sera grande, plus la base de données risque de mettre de temps à se créer, et risque de prendre plus de mémoire !
- 📖 Il vous est possible de suivre l'ensemble des requêtes dans la console C.
- ☝️ L'exécution a été optimisée pour l'optimisation de CLion. Pensez à modifier le chemin de lecture de la base de données si nécessaire ! Celui-ci peut se trouver en haut du fichier "main.c", lisez les commentaires !
- 💥 L'affichage de la base de données dans le site est limité à quelques centaines de milliers de films. Après cela, le site risque de ne pas répondre. Cependant, l'ensemble des résultats pourra être trouvé dans le fichier "result.txt".
  - 💡 Quand cela arrive, il vous est possible de redémarrer le site web. Il vous faut simplement le refermer, puis le rouvrir *(avec l'aide de Ctrl+Shift+T si vous êtes toujours sur votre navigateur, ou en ouvrant le fichier normalement)*.
- 💾 L'utilisation du navigateur Edge est recommandée pour sa capacité à rapidement pouvoir télécharger des fichiers. En effet, cela peut être modifié dans paramètres, téléchargement, location.
  - ☝️ Notez qu'il est également possible de télécharger automatiquement les fichiers, sans vous demander la permission !
    - ⚠️Pensez à retirer ce paramètre après pour raisons de sécurité !
    - ❗ Notez également que l'utilisation de ce paramètre risque de vous afficher des "download errors" dans l'onglet téléchargement *(Ctrl+J)*. Ceci est dû au fait que le programme C supprime le fichier juste après sa création, mais n'a aucun impact sur l'exécution du programme.