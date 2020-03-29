#ifndef TASK
#define TASK

#include <string>
#include <iostream>
#include <vector>
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
   int pourcentage;
   Date *starting_date;
   Date *ending_date;
   Priority priority;
   Status status;

   public:
   Task(int _id, string _title);
   Task(string text); //Recréer la tache a partir de sa forme exportée, lisibile dans un fichier
   ~Task(); //Un destructeur est obligatoire comme les dates sont des pointeurs

   void Print();
   string StringToExport(); //Retourne une chaine de caractère transcrivant les attributs de la tache, afin de l'exporter dans un fichier
   
   int GetID(); //Retourne ID
   string GetTitle();
   string GetDescription();
   string GetStartingDate();
   string GetEndingDate();
   string GetPriority();
   string GetStatus();

   void SetDescription(string); //Permet de modifier la description
   void SetStartingDate(int _day, int _month, int _year); //Modifie la date de début
   void SetStartingDate(string line); //Modifie la date de début a partir d'une chaien de caractère de la forme day/month/year
   void SetPriority(string line); //Modifie la priorité
   void SetStatus(string line); //Modifie le status 
   void SetPourcentage(int); //Modifie le pourcentage
   };



class TasksManager{
    /* C'est une sorte de liste de Taches, mais avec plusieurs fonctions pratique pour travailler specifiquement avec ces objets.
    Constructeur :
    - Par défaut, la liste est vide
    - On peut également la charger depuis un fichier
    - On peut égalment lui fournir directement une liste avec laquelle travailler

    Attributs:
    - liste : C'est une liste de pointeurs vers des objets Taches. C'est cette liste qui est manipulé par toutes
    les autres fonctions

    Méthodes principales:
    - Add : Ajoute la tache donné dans la liste. Une vérification de l'unicité de l'ID est faites
    - Delete : Supprime la tache en question de la liste.
    
    Méthode de recherches :
    - FindByPriority : 

    Méthode utilitaires :
    - GetNewID : Renvoie un ID non utilisé pour la suivante
    - CheckIfIDIsAlreadyUsed : Assez explicite
    - SaveToFile : Enregistre l'état actuel dans un fichier, qui pourra être importé pour recharger l'objet TaskManager.
    La convention utilisé pour enregistrer le fichier est expliquer dans la définition de la fonction, dans Task.cpp
     */

    private:
    vector<Task*> liste;

    public:
    TasksManager();
    TasksManager(string filePath);
    TasksManager(vector<Task*> _liste);
    ~TasksManager();

    void Add(Task* task);
    bool Delete(int _id);

    int GetNewID();
    vector<int> GetAllIDs();
    int Count();
    bool SaveToFile(string filePath);

    void KeepOnly(string);
    void KeepOnlyID(int);
    void KeepOnlyTitle(string);
    void KeepOnlyDescription(string);
    void KeepOnlyStartingDate(string);
    void KeepOnlyPriority(string);
    void KeepOnlyStatus(string);
    void Print();
};

#endif