# C-Projet-final : Task Manager
Projet final du cours de C++ - Mines ParisTech 1A

## Présentation
Task Manager est un petit gestionnaire de tâche en ligne de commande permettant de consigner dans une base de données un ensemble de tâche et de les gérer.
Exemple :

## Utilisation
### Commande `create` : créer une nouvelle tâche
Initialement, la base de donnée est vide. Pour construire une tâche, on utilise le mot-clef `create`.
Il est possible de se réferer à l'aide concernant cette commande avec le paramètre `--help`.
```
>> taskmgr.exe create --help
'create' permet de creer une nouvelle tache et de l'ajouter a la liste.
Parametres obligatoires :
   --title <titre> : Permet de specifier le titre de la tache.
Parametres optionnels :
   --description <description> : Donne une description du travail de la tache.
   --date <day>/<month>/<year> : Definie une annee sous le format suivant. Par defaut, la date est celle d'aujourd'hui.
   --priority [High,Normal (Default),Low] : Donne une priorite a la tache parmi les trois disponibles. Tout autre entree donnera comme priorite 'ERREUR'.
   --status [Open (Default),In Progress,Close] : Definie le status de la tache. Tout autre entree donnera comme priorite 'ERREUR'.
   --pourcentage <ENTIER ENTRE 0 et 100> : Definie le taux d'avancement de la tache.
```

Le plus simple pour créer une tache est de ne spécifier que le titre :
```
>> taskmgr.exe create --title "Preparer le dejeuner"
[3] Preparer le dejeuner :
Demarre le 31/3/2020
Status : Open | Progression : 0/100 | Priorite : Normal
Tache ajoutee.
```
On peut également ajouter les autres paramètres optionnels, l'ordre n'a aucune importance.
```
>> taskmgr.exe create --title "Dessin industriel" --status "In Progress" --pourcentage 25 --priority High
[4] Dessin industriel :
Demarre le 31/3/2020
Status : In Progress | Progression : 25/100 | Priorite : High
Tache ajoutee.
```
Ou encore en planifiant la date :
```
>> taskmgr.exe create --date 17/05/2020 --priority Low --title "Meeting avec Sarah" --description "Verifier la progression du projet + bilan reunion du 12"
[5] Meeting avec Sarah : Verifier la progression du projet + bilan reunion du 12
Demarre le 17/5/2020
Status : Open | Progression : 0/100 | Priorite : Low
Tache ajoutee.
```

Si jamais celui `--title` est oublié, le programme ne créer aucune tâche et affiche l'aide
```
>> taskmgr.exe create --description "Une tache sans titre" --date 12/12/2012
Erreur : le parametre '--title' est indispensable dans la creation d'une liste
'create' permet de creer une nouvelle tache et de l'ajouter a la liste.
[...]
```

Les exceptions sont gérées soit par l'indication ERREUR. Le logiciel est sensible à la case.
```
>> taskmgr.exe create --title "Crash test" --status Entamé --priority HiGh
[6] Crash test :
Demarre le 31/3/2020
Status : ERREUR | Progression : 0/100 | Priorite : ERREUR
Tache ajoutee.
```

La progression et la date prennent leur valeur par defaut.
```
>> taskmgr.exe create --title "Crash test" --date "N'importe quoi" --progression Cinq
ERREUR : Impossible de convertir 'N'importe quoi' en une Date
[9] Crash test :
Demarre le 31/3/2020
Status : Open | Progression : 0/100 | Priorite : Normal
Tache ajoutee.
```

### Commande `list` : lister les tâches existantes, et faire des recherches plus précises
Utiliser seul, ce mot-clef permet de voir toute les tâches existantes.
```
>> taskmgr.exe list
4 tache(s) correspondant au(x) critere(s) demmande(s) trouvee(s).
[1] Preparer le dejeuner :
Demarre le 31/3/2020
Status : Open | Progression : 0/100 | Priorite : Normal

[2] Dessin industriel :
Demarre le 31/3/2020
Status : In Progress | Progression : 25/100 | Priorite : High

[3] Meeting avec Sarah : Verifier la progression du projet + bilan reunion du 12
Demarre le 17/5/2020
Status : Open | Progression : 0/100 | Priorite : Low

[4] Crash test :
Demarre le 31/3/2020
Status : ERREUR | Progression : 0/100 | Priorite : ERREUR
```

Les mêmes paramètres que pour le mot-clef `create`peuvent être utilisés pour affiner la recherche aux taches répondant à tous les critères demandés. Les parametres `--titre` et `--description` vérifient si le text dspécifié apparrait dans le titre et respectivement la description des tâches.
Quelques exemples :
```
>> taskmgr.exe list --status Open
2 tache(s) correspondant au(x) critere(s) demmande(s) trouvee(s).
[1] Preparer le dejeuner :
Demarre le 31/3/2020
Status : Open | Progression : 0/100 | Priorite : Normal

[3] Meeting avec Sarah : Verifier la progression du projet + bilan reunion du 12
Demarre le 17/5/2020
Status : Open | Progression : 0/100 | Priorite : Low
```

```
```

```
```

```
```

```
```

### Commande change : modifie une tâche


### Commande delete : supprime les tâches répondant à des critères possibles
