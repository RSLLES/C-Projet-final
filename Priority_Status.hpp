#ifndef PRIORITYSTATUS
#define PRIORITYSTATUS

//Constante donnant le nombre de possibilités possible pour la priorité
#define NB_PRIORITY 3
//Constante donnant l'index de la priorité "normale" utilisée par défaut
#define NORMAL 1

#include <string>
#include <iostream>
using namespace std;

class Priority{
    /*
    Class définissant une priorité. Cet objet est formé d'un tableau de taille fixe prédéfinie contenant toutes les possibilités
    de priorités aux nombres de NB_PRIORITY, et d'un entier comportant l'index de la priorité utilisée.
    La fonction SetPriority permet de changer la priorité en cours. Une surcharge de cette fonction permet de définir une nouvelle priorité
    à la fois par du texte mais aussi en utilisant l'index. 
    Si jamais une erreur est faites sur le texte ou bien sur l'index, ce dernier prend la valeur -1, signe d'une erreur.
    Les constructeurs se basent sur la fonction SetPriority.
    La fonction GetPriority retourne simplement une chaine de caractères comportant le nom de la priorité en cours.
    */
    string list[NB_PRIORITY] = {"Hight", "Normal", "Low"};
    int index;

    public:
    Priority();
    Priority(int _index);
    Priority(string _priority);

    string GetPriority();
    void SetPriority(int _index);
    void SetPriority(string _priority);
};

#endif