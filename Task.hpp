#ifndef TASK
#define TASK

#include <string>
using namespace std;

class Task{
    /* Classe représentant une tâche.
    La tâche possède les attributs suivants obligatoires lors de sa fabrication:
    - id : entier de type int comportant le numéro d'identification de la tâche en cours. Ce numéro est unique pour toute les taches,
    mais la vérification de cette unicité n'est pas gérée par les tâches en elle même.
    - title : chaîne de caractères de type string qui contient le nom de la tâche.

    Attributs non obligatoires lors de la construction :
    - description : Contient une description succinte de la tâche. Si non spécifiée, la description est vide
    - starting_date : Objet de type Date contenant la date de création de la tâche. Si non spécifiée, la date est celle d'aujourd'hui.

    Attributs 

    */

   private:
   //Obligatoires lors de la construction
   int id;
   string title;

   //attributs non obligatoires
   string description;
   

   public:
   Task();

};

#endif