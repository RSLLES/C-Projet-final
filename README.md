# C-Projet-final : Task Manager
Projet final du cours de C++ - Mines ParisTech 1A

## Présentation
Task Manager est un petit gestionnaire de tâche en ligne de commande permettant de consigner dans une base de données un ensemble de tâche et de les gérer.
Exemple :

## Utilisation
### Commande create : créer une nouvelle tâche
Initialement, la base de donnée est vide. Pour construire une tâche, on utilise le mot-clef `create`.
Il est possible de se réferer à l'aide concernant cette commande avec le paramètre `--help`.
```
taskmgr.exe create --help
Erreur : le parametre '--title' est indispensable dans la creation d'une liste
'create' permet de creer une nouvelle tache et de l'ajouter a la liste.
Parametres obligatoires :
   --title <titre> : Permet de specifier le titre de la tache.
Parametres optionnels :
   --description <description> : Donne une description du travail de la tache.
   --date <day>/<month>/<year> : Definie une annee sous le format suivant. Par defaut, la date est celle d'aujourd'hui.
   --priority [High,Normal (Default),Low] : Donne une priorite a la tache parmi les trois disponibles. Tout autre entree donnera comme priorite 'ERREUR'.
   --status [Open (Default),Progress,Close] : Definie le status de la tache. Tout autre entree donnera comme priorite 'ERREUR'.
   --pourcentage <ENTIER ENTRE 0 et 100> : Definie le taux d'avancement de la tache.
```

Le plus simple pour créer une tache est de ne spécifier que le titre :
```
>taskmgr.exe create --title "Preparer le dejeuner"
Preparer le dejeuner
[3] Preparer le dejeuner :
Demarre le 31/3/2020
Status : Open | Progression : 0/100 | Priorite : Normal
Tache ajoutee.
```

### Commande list : lister les tâches existantes, et faire des recherches plus précises

### Commande change : modifie une tâche


### Commande delete : supprime les tâches répondant à des critères possibles
