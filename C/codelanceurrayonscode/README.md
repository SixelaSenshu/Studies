# Projet Raytracing : Alexis Bernard & Wybo Antoine

## 1.Architecture du project

L'architecture du project est constituée de la manière suivante :

Nous avons le dossier sources avec les fichiers sources, le dossier headers avec les prototypes de fonctions ainsi que le dossier obj qui contient les objets binaire.

Ces 3 dossiers contiennents différents sous-dossiers :
- comparator : Celui-ci contient le code pour créer une image de la différences entre deux autres images et les informations à propos de la différence
  On a égalelement le fichier main qui est relié au fichier compare.sh qui permet de lancer l'éxécutable.

- Raytrace : Celui-ci contient le main ainsi que un fichier contenant toutes les fonctions qui permettent de créer les images à partir des modules mathématiques permettants les calculs.

- Tools : Celui-ci contient toutes les fonctions en rapport avec les calculs de lumière, couleurs ,directions, triangles, ombre, ....

- ReaderScene : Celui-ci contient toutes les fonctions pour lire un fichier et générer tous les objects ainsi que le main et le checkscene.sh dédié pour les tests.
  
- triplets : Celui-ci contient le main pour les tests ainsi que la bibliotheque mathématiques des triplets. Le fichier checkTriplets.sh s'occupe de lancer l'exécutable.
  
- le main.c/.h/.o : Le main principal qui permet de mettre ce qu'on veut comme tests. Il est vide par défaut car les modules sont testés via d'autres main.
  
On a par la suite les fichiers TEST{N} qui contiennent l'ensembles des tests pour le projet 

On a les fichiers build.sh et tests.sh qui permet de lancer tous les tests et de générer tous les binaires & éxécutable pour le projet.

Les fichiers sonar-project.properties, .gitattributes et .gitlab-ci.yml contiennent les informations pour sonar , git et les tests d'intégration continue.

Les différents makefile et doxyfiles permettent de créer la doc et les fichiers binaires.

Lib contient les dépéndences , contents les consignes et executables les éxécutables.

## 2.Commandes du project

On a donc différents commandes et un ordre pour tous lancer et compiler.

- Tous d'abord on doit créer les éxécutables via make et définir le choix avec la macro CHOICE .Un exemple de choix serait ```make CHOICE=raytrace``` .Celui-ci va s'occuper du main pour le raytrace et permettre de faire les tests. Make va uniquement créer les binaires et le main qui est vide par défauts. On va donc lancer la commande build.sh pour créer tous les tests nécéssaires.
  
- Une fois tous les tests on lance la commande ./tests.sh pour faire les tests (j'ai par défault fais la suppression des images crées ).

- Pour générer la doc, on utilise la commande doxygen Doxyfile déja configuré pour récupérer les headers uniquements.
  
- Pour le nettoyage on à plusieurs commande : mrproper et clean pour chaque choix de makefile.

Sur git, les tests sont déja créer et tous est déja mis en place donc on peut voir un exemple de tous les tests sur la commande.
