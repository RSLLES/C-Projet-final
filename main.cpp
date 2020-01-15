#include "Task.hpp"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){
    //Traitement de la ligne de commande
    //Le premier arguments est forcement un des mots clefs d'actions
    
    //1) Mot clee create -> Creation d'une tâche
    if (argc > 1 && ((string)argv[1]) == "create"){
        //ARGUMENTS A CHERCHER
        string *title = nullptr;
        string *description = nullptr;
        string *date = nullptr;
        string *priority = nullptr;
        string *status = nullptr;
        int *pourcentage = nullptr;
        bool help = true;
        
        //On cherche --title qui doit exister apres create et avant le derneir element (qui si il existe, est le nom du titre)
        //On cherche egalement la mention d'aide
        for (int i = 2; i < argc-1; i++){
            if (((string)argv[i]) == "--title"){
                title = new string(argv[i+1]);
                i++; //Ca ne sert à rien de retraiter le caractere precedent
            }
            else if (((string)argv[i]) == "--description"){
                description = new string(argv[i+1]);
                i++;
            }
            else if (((string)argv[i]) == "--date"){
                date = new string(argv[i+1]);
                i++;
            }
            else if (((string)argv[i]) == "--priority"){
                priority = new string(argv[i+1]);
                i++;
            }
            else if (((string)argv[i]) == "--status"){
                status = new string(argv[i+1]);
                i++;
            }
            else if (((string)argv[i]) == "--pourcentage"){
                pourcentage = new int(stoi(argv[i+1]));
                i++;
            }
        }

        //Si l'on a trouve un titre, alors on peut creer la tache
        if (title != nullptr){
            //On charge le TaskManager
            TasksManager T("Data.txt");
            //On créer et ajoute notre Tache
            Task *t = new Task(T.GetNewID(), *title);
            T.Add(t);
            
            //On ajoute ensuite les autres arguments si ils sont spécifiés
            //La Description
            if (description != nullptr){
                t->SetDescription(*description);
            }
            //La Date
            if (date != nullptr){
                t->SetStartingDate(*date);
            }
            //La priorité
            if (priority != nullptr){
                t->SetPriority(*priority);
            }
            //Le status
            if (status != nullptr){
                t->SetStatus(*status);
            }
            //Le pourcentage
            if (pourcentage != nullptr){
                t->SetPourcentage(*pourcentage);
            }

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
        delete date;
        delete priority;
        delete status;
        delete pourcentage;

        //Enfin, on affiche l'aide si necessaire
        if (help){
            cout << "'create' permet de creer une nouvelle tache et de l'ajouter a la liste." << endl;
            cout << "Parametres obligatoires : " << endl;
            cout << "   --title <titre> : permet de specifier le titre de la tache." << endl;
            cout << "Parametres optionnelles : " << endl;
            cout << "   --description <description> : donne une description du travail de la tache." << endl;
            cout << "   --date <day>/<month>/<year> : Definie une année sous le format suivant. Par defaut, la date est celle d'aujourd'hui." << endl;
            cout << "   --priority <priorite> : Donne une priorite a la tache. Les seules priorites autorisees sont 'High', 'Normal' et 'Low'. Tout autre entree donnera comme priorite 'ERREUR'." << endl;
            cout << "   --status <status> : Definie le status de la tache. Les status autorises sont 'Open', 'Close' et 'Progress'. Tout autre entree donnera comme priorite 'ERREUR'." << endl;
            cout << "   --pourcentage <ENTIER ENTRE 0 et 100> : Définie le taux d'avancement de la tâche. " << endl;
        }
    }

    //2) Mot clef list
    else if (argc > 1 && ((string)argv[1]) == "list"){
        //par défaut --liste affiche naturellement quelque chose, on désactive donc l'aide
        bool help = false;

        //On charge le TaskManager
        TasksManager T("Data.txt");
        //On va également créer un pointeur vide temporaire qui va nous permettre de
        //stocker le nouveau TaskManager retourné par les méthodes Search

        //On cherche à présent si des critères sont spécifiés, et si c'est le cas on supprime ceux n'y répondant pas.
        for (int i = 2; i < argc-1; i++){
            if (((string)argv[i]) == "--id"){
                int const id(stoi(argv[i+1])); //Je pose une variable ici pour plus de clarté, mais ce n'est pas nécessaire
                T.KeepOnlyID(id);
                i++;
            }
            else if (((string)argv[i]) == "--title"){
                string const title(argv[i+1]);
                T.KeepOnlyTitle(title);
                i++; 
            }
            else if (((string)argv[i]) == "--description"){
                string const description(argv[i+1]);
                T.KeepOnlyDescription(description);
                i++;
            }
            else if (((string)argv[i]) == "--date"){
                string const date(argv[i+1]);
                T.KeepOnlyStartingDate(date);
                i++;
            }
            else if (((string)argv[i]) == "--priority"){
                string const priority (argv[i+1]);
                T.KeepOnlyPriority(priority);
                i++;
            }
            else if (((string)argv[i]) == "--status"){
                string const status(argv[i+1]);
                T.KeepOnlyStatus(status);
                i++;
            }
            else if (((string)argv[i]) == "--help"){
                help = true;
            }
        }


        //On affiche le résultat
        T.Print();

        //Enfin, on affiche l'aide si necessaire
        if (help){
            cout << "'liste' permet de lister les différentes taches enregistres." << endl;
            cout << "Il est aussi possible de specifier certains criteres afin de reduire la liste." << endl;
            cout << "Parametres optionnelles : " << endl;
            cout << "   --id <ID> : Affiche la tache avec l'ID ci contre." << endl;
            cout << "   --title <titre> : Affiche les taches contenant <titre> dans leur titre (sensible à la casse). " << endl;
            cout << "   --description <description> : Affiche les taches contenant <description> dans leur description (sensible à la casse)." << endl;
            cout << "   --date <day>/<month>/<year> : Affiche les taches creee a la date indiquee." << endl;
            cout << "   --priority <priorite> : Affiche les tache de la priorite indiquee." << endl;
            cout << "   --status <status> : Affiche les tâche du status indique." << endl;
        }
    }

    //?) Sans mot clefs : explications
    else{
        cout << "Logiciel de 'todo-list' permettant de gerer un ensmemble de taches." << endl;
        cout << "Fonctionnalites : " << endl;
        cout << "   create : Permet de creer une nouvelle tache." << endl;
        cout << "   list : Permet de lister les taches répondant à certains critères." << endl;
        cout << "Pour plus de precision sur chaque commande, utiliser '<commande> --help'" << endl;
    }
    return 0;
}