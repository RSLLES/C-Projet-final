#ifndef TASK
#define TASK

#include <string>
#include <iostream>
#include <ctime>
#include "Priority_Status.hpp"
#include "Date.hpp"
using namespace std;

class Task{
    /* Classe représentant une tâche.
    Une tâche possède les attributs suivants obligatoires lors de sa fabrication:
    - id : entier de type int comportant le numéro d'identification de la tâche en cours. Ce numéro est unique pour toute les taches,
    mais la vérification de cette unicité n'est pas gérée par les tâches en elle même.
    - title : chaîne de caractères de type string qui contient le nom de la tâche.

    Attributs non obligatoires lors de la construction modifiable par la suite :
    - description : Contient une description succinte de la tâche. Si non spécifiée, la description est vide
    - status : Objet de type Status, indique le status en l'etat actuel. A la création, il est sur ouvert.
    - starting_date : Objet de type Date contenant la date de création de la tâche. Si non spécifiée, la date est celle d'aujourd'hui.
    - ending_date : Objet de type Date, existant si et seulement si le status de la tache est sur fermé.
    - priority : Objet de type priority, indiquant la priorité de la tache. Par défaut, il est sur Normal.

    Attributs 

    */

   private:
   int id;
   string title;
   string description;
   float pourcentage;
   Date *starting_date;
   Date *ending_date;
   Priority priority;
   Status status;

   public:
   Task(int _id, string _title);
   ~Task(); //Un destructeur est obligatoire comme les dates sont des pointeurs

   void Print();
};



class TasksManager{
    /* C'est une sorte de liste de Taches, mais avec plusieurs fonctions pratique pour travailler specifiquement avec ces objets.
    Constructeur :
    - Par défaut, la liste est vide
    - On peut également la charger depuis un fichier
    - On peut égalment lui fournir directement une liste avec laquelle travailler

    Attributs:
    liste : C'est une liste de pointeurs vers des objets Taches. C'est eux que l'on manipule par toutes les fonctions

    Méthodes principales:
    - Add : Ajoute la tache donné dans la liste. Une vérification de l'unicité de l'ID est faites
    - Delete : Supprime la tache en question de la liste
    
    Méthode de recherches :
    - FindByPriority : 

    Méthode utilitaires :
    - GetNewID : Renvoie un ID non utilisé pour la suivante
    - CheckIfIDIsAlreadyUsed : Assez explicite
     */

    public:
    TasksManager();
    TasksManager(string filePath);


};

#endif