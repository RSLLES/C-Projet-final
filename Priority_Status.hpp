#ifndef PRIORITYSTATUS
#define PRIORITYSTATUS

#include <string>
#include <iostream>
using namespace std;

class ListeDETats{
    /*
    Class définissant une liste d'état, qui nous servira pour créer à la fois l'objet priorité et l'objet status.
    Attributs :
    - n:        nombre d'état possible, qui correspond donc également à la longeur du tableau.
    - list:     un tableau d'une taille fixe prédéfinie contenant toutes les possibilités d'états.
    - index:    un entier comportant l'index de l'état en cours.

    Méthodes :
    - Set:  Permet de changer l'état en cours à l'aide de l'index ou par du texte.
            Si jamais une erreur est faites sur le texte ou bien sur l'index, ce dernier prend la valeur -1, signe d'une erreur.
    - Get:  Getretourne simplement une chaine de caractères comportant le nom de l'état en cours, extrait de liste.

    Constructeurs :
    Le constructeurs n'est rien de plus qu'un appel à Set, il peut donc prendre en entré un string ou l'index.
    Par défaut, le constructeur attribut l'index 0 comme état. Dans la liste, l'état voulu par défaut doit donc avoir comme indice 0.
    */
    protected:
    int n;
    string *list;
    int index;

    public:
    ListeDETats();
    ListeDETats(int _n, string*_list, int _index);
    ListeDETats(int _n, string*_list, string _etat);

    string Get();
    void Set(int _index);
    void Set(string _etat);
};



class Priority : public ListeDETats
{
    /*
    Classe déinissant une priorité, qui n'est rien d'autre qu'une liste d'état particulière.
    */
   public:
   Priority();
   Priority(string);
   Priority(int);
};


#endif