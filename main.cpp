#include "Task.hpp"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){
    //Traitement de la ligne de commande
    //Le premier arguments est forcement un des mots clefs d'actions
    
    //1) Mot clee create -> Creation d'une tâche
    if (((string)argv[1]) == "create"){
        //ARGUMENTS OBLIGATOIRES A CHERCHER
        string *title = nullptr;
        string *description = nullptr;
        bool help = true;
        
        //On cherche --title qui doit exister apres create et avant le derneir element (qui si il existe, est le nom du titre)
        //On cherche egalement la mention d'aide
        for (int i = 2; i < argc-1; i++){
            if (((string)argv[i]) == "--title"){
                title = new string(argv[i+1]);
                i++; //Ca ne sert à rien de retraiter le caractere precedent
            }
            if (((string)argv[i]) == "--description"){
                description = new string(argv[i+1]);
                i++; //Ca ne sert à rien de retraiter le caractere precedent
            }
        }

        //Si l'on a trouve un titre, alors on peut creer la tache
        if (title != nullptr){
            //On charge le TaskManager
            TasksManager T("Data.txt");
            //On créer et ajoute notre Tache
            Task *t = new Task(T.GetNewID(), *title);
            //On ajoute la description si nécessaire
            if (description != nullptr)
                t->SetDescription(*description);
            T.Add(t);
            //On enregistre
            T.SaveToFile("Data.txt");
            //On désactive l'aide
            help = false;
            //On affiche un retour
            t->Print();
            cout << endl << "Tache ajoutee." << endl;
        }
        //Sinon, il y a une erreur et l'on affiche l'aide
        else
        {
            cout << "Erreur : le parametre '--title' est indispensable dans la creation d'une liste" << endl;
        }

        //On detruit les pointeurs utilisés
        delete title;
        delete description;


        //Enfin, on affiche l'aide si necessaire
        if (help){
            cout << "'create' permet de creer une nouvelle tache et de l'ajouter a la liste." << endl;
            cout << "Parametres obligatoires : " << endl;
            cout << "   --title <titre> : permet de specifier le titre de la tache." << endl;
            cout << "Parametres optionnelles : " << endl;
            cout << "   --description <description> : donne une description du travail de la tache." << endl;
        }

    }


    //?) Sans mot clefs : explications
    else{
        cout << "Logiciel de 'todo-list' permettant de gerer un ensmemble de taches." << endl;
        cout << "Fonctionnalites : " << endl;
        cout << "   create : Permet de creer une nouvelle tache." << endl;
        cout << "Pour plus de precision sur chaque commande, utiliser '<commande> --help'" << endl;
    }


    return 0;
}