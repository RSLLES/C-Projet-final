#include "Task.hpp"
#include "main.hpp"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){
    //Traitement de la ligne de commande
    string args[N] = {DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT};
    Args(argc, argv, args);


    //Le premier arguments est forcement un des mots clefs d'actions

    //1) Mot clee create -> Creation d'une tâche
    if (argc > 1 && ((string)argv[1]) == "create"){
        bool reussi = false;

        //Si l'on a trouve un titre  alors on peut creer la tache
        if (args[_TITLE_] != DEFAULT){
            //On charge le TaskManager
            TasksManager T("Data.txt");
            //On créer et ajoute notre Tache
            Task *t = new Task(T.GetNewID(), args[_TITLE_]);
            T.Add(t);
            
            //On ajoute ensuite les autres arguments si ils sont spécifiés à la tache
            Set(args, t);

            //On enregistre
            T.SaveToFile("Data.txt");
            //On a reussi
            reussi = true;
            //On affiche un retour
            t->Print();
            cout << endl << "Tache ajoutee." << endl;
        }
        //Sinon, il y a une erreur et l'on affiche l'aide (sauf si afficher l'aide était le but intial)
        else if (args[_HELP_] != DEFAULT)
        {
            cout << "Erreur : le parametre '--title' est indispensable dans la creation d'une liste" << endl;
        }

        //Enfin, on affiche l'aide si necessaire, c'est à dire si demandé ou bien si l'utilisateur a raté qquechose
        if (args[_HELP_] != DEFAULT || !reussi){
            cout << "'create' permet de creer une nouvelle tache et de l'ajouter a la liste." << endl;
            cout << "Parametres obligatoires : " << endl;
            cout << "   --title <titre> : Permet de specifier le titre de la tache." << endl;
            cout << "Parametres optionnels : " << endl;
            cout << "   --description <description> : Donne une description du travail de la tache." << endl;
            cout << "   --date <day>/<month>/<year> : Definie une annee sous le format suivant. Par defaut, la date est celle d'aujourd'hui." << endl;
            cout << "   --priority [High,Normal,Low] : Donne une priorite a la tache parmi les trois disponibles. Tout autre entree donnera comme priorite 'ERREUR'." << endl;
            cout << "   --status [Open,In Progress,Close] : Definie le status de la tache. Tout autre entree donnera comme priorite 'ERREUR'." << endl;
            cout << "   --pourcentage <ENTIER ENTRE 0 et 100> : Definie le taux d'avancement de la tache. " << endl;
        }
    }

    //2) Mot clef list
    else if (argc > 1 && ((string)argv[1]) == "list"){
        //On charge le TaskManager
        TasksManager* T = new TasksManager("Data.txt");

        //On y retire tout ce qui ne rentre pas dans les criteres
        Extraire(args, T);

        //On affiche le résultat si l'aide n'est pas demandée
        if (args[_HELP_] == DEFAULT)
        {
            if (T->Count() == 0)
                cout << "Aucune tache ne satisfait tous les criteres de la recherche." << endl;
            else
                cout << T->Count() << " tache(s) correspondant au(x) critere(s) demmande(s) trouvee(s)." << endl;
            T->Print();
        }

        //Enfin, on affiche l'aide si necessaire
        else{
            cout << "'liste' permet de lister les différentes taches enregistrees." << endl;
            cout << "Il est aussi possible de specifier certains criteres afin de reduire la liste." << endl;
            cout << "Parametres optionnels : " << endl;
            cout << "   --id <ID> : Affiche la tache avec l'ID ci contre." << endl;
            cout << "   --title <titre> : Affiche les taches contenant <titre> dans leur titre (sensible à la casse). " << endl;
            cout << "   --description <description> : Affiche les taches contenant <description> dans leur description (sensible à la casse)." << endl;
            cout << "   --date <day>/<month>/<year> : Affiche les taches creee a la date indiquee." << endl;
            cout << "   --priority <priorite> : Affiche les tache de la priorite indiquee." << endl;
            cout << "   --status <status> : Affiche les tâche du status indique." << endl;
        }
    }


    //3 ) Mot cle delete -> Supprime toutes les taches qui répondent aux critères imposés
    else if (argc > 1 && ((string)argv[1]) == "delete"){
        //On utilise ce qui a été coinstruit pour le mot cle list pour extraire ce qui correspond au critères indiqués
        bool reussi = false;

        //On charge le TaskManager
        TasksManager* TASuppr = new TasksManager("Data.txt");
        TasksManager T = TasksManager("Data.txt");
        Extraire(args, TASuppr);

        if (TASuppr->Count() > 0)
        {
            //On affiche un avertissement si il y a plus d'un tache, qui est vrai par defaut
            string reponse("o");
            if (TASuppr->Count() > 1)
            {
                TASuppr->Print();
                cout << "ATTENTION : l'operation delete va supprimer les " << TASuppr->Count() << " taches affichees ci dessus." << endl;
                cout << "Confirmer ? ('o' pour oui) : ";
                cin >> reponse;
                cout << endl;
            }
            
            if (reponse == "o")
            {
                //Suppression
                //On extrait l'ID de chacune des taches présente dans dans TASuppr et on les enlevent de T
                vector<int>* ids = TASuppr->GetAllIDs();
                for (vector<int>::iterator it(ids->begin()); it != ids->end(); it++)
                    T.Delete((*it));

                T.SaveToFile("Data.txt");

                cout << TASuppr->Count() << " tache(s) supprimee(s)." << endl;
                reussi = true;
            }
            else
            {
                cout << "Annule." << endl;
                reussi = true;
            }
        }
        else
        {
            cout << "Erreur : Aucune entree ne satisfait aux criteres donnes. Operation annulee. " << endl;
        }
        

        if(args[_HELP_] != DEFAULT || !reussi){
            cout << "'delete' permet de supprimer toutes les taches repondant a des criteres precis." << endl;
            cout << "Parametres de recherches : " << endl;
            cout << "   --id <ID> : Affiche la tache avec l'ID ci contre." << endl;
            cout << "   --title <titre> : Affiche les taches contenant <titre> dans leur titre (sensible à la casse). " << endl;
            cout << "   --description <description> : Affiche les taches contenant <description> dans leur description (sensible à la casse)." << endl;
            cout << "   --date <day>/<month>/<year> : Affiche les taches creee a la date indiquee." << endl;
            cout << "   --priority <priorite> : Affiche les tache de la priorite indiquee." << endl;
            cout << "   --status <status> : Affiche les tâche du status indique." << endl;
            cout << "ATTENTION : Sans criteres, delete supprimera toutes les taches existantes" << endl;
        }
    }

    //4) Mot clef change
    else if (argc > 1 && ((string)argv[1]) == "change"){
        bool reussi = false;

        //On repère la tache que l'on souhaite modifier, en cherchant son id
        //On vérifie que l'on a bien trouvé l'ID, sinon on ne sait pas quelle tache modifier
        if (args[_ID_] != DEFAULT)
        {
            //On vérifie que l'ID exist
            TasksManager T = TasksManager("Data.txt");
            Task* t = T.GetTask(stoi(args[_ID_]));
            if (t != nullptr)
            {
                //On l'affiche
                cout << "Tache avant modification: " << endl;
                t->Print();
                cout << endl << "########" << endl << endl;

                //On modifie à présent ce qu'il faut modifier
                Set(args, t);

                //On réaffiche
                cout << "Tache modifiee : " << endl;
                t->Print();

                //On enregistre
                T.SaveToFile("Data.txt");
            }
            else{
                cout << "Aucune tache de trouvee pour l'ID [" << args[_ID_] << "]. Merci de verifier avec 'list'." << endl; 
            }

        }
        else
        {
            cout << "Pour utiliser 'change', l'argument --id est indispensable pour identifier de maniere unique la tache a modifier" << endl;
        }
        

        if(args[_HELP_] != DEFAULT){
            cout << "'change' permet de modifier les caracteristiques d'une tache en particulier." << endl;
            cout << "Parametre obligatoire : " << endl;
            cout << "   --id <ID> : Pour identifier de maniere unique la tache a modifier." << endl;
            cout << "Parametres a modifier : " << endl;
            cout << "   --title <titre> : Affiche les taches contenant <titre> dans leur titre (sensible à la casse). " << endl;
            cout << "   --description <description> : Affiche les taches contenant <description> dans leur description (sensible à la casse)." << endl;
            cout << "   --date <day>/<month>/<year> : Affiche les taches creee a la date indiquee." << endl;
            cout << "   --priority <priorite> : Affiche les tache de la priorite indiquee." << endl;
            cout << "   --status <status> : Change le status de la tache." << endl;
            cout << "   --pourcentage <Nombre 1 a 100> : Changer le pourcentage d'avancement de la tache" << endl;
            cout << "ATTENTION : Sans criteres, delete supprimera toutes les taches existantes" << endl;
        }
        
    }

    //?) Sans mot clefs : explications
    else{
        cout << "Logiciel de 'todo-list' permettant de gerer un ensmemble de taches." << endl;
        cout << "Fonctionnalites : " << endl;
        cout << "   create : Permet de creer une nouvelle tache." << endl;
        cout << "   list : Permet de lister les taches repondant à certains criteres." << endl;
        cout << "   delete : Permet de supprimer TOUTES les taches repondant aux criteres specifies." << endl;
        cout << "Pour plus de precision sur chaque commande, utiliser '<commande> --help'" << endl;
    }
    return 0;
}

void Args(int argc, char* argv[], string* r)
/*
Fonction qui regarde tous les arguments possible et stock tout dans un grand tableau de int dans un ordre fixe.
Les différentes constantes sont définies dans main.hpp
*/
{
    for (int i = 2; i < argc; i++){
        if (((string)argv[i]) == "--id"){
            r[_ID_] = ((string)argv[i+1]);
            i++;
        }
        else if (((string)argv[i]) == "--title"){
            r[_TITLE_] = ((string)argv[i+1]);
            i++; 
        }
        else if (((string)argv[i]) == "--description"){
            r[_DESCRIPTION_] = ((string)argv[i+1]);
            i++;
        }
        else if (((string)argv[i]) == "--date"){
            r[_DATE_] = ((string)argv[i+1]);
            i++;
        }
        else if (((string)argv[i]) == "--priority"){
            r[_PRIORITY_] = ((string)argv[i+1]);
            i++;
        }
        else if (((string)argv[i]) == "--status"){
            r[_STATUS_] = ((string)argv[i+1]);
            i++;
        }
        else if (((string)argv[i]) == "--pourcentage"){
            r[_POURCENTAGE_] = ((string)argv[i+1]);
            i++;
        }
        else if (((string)argv[i]) == "--help"){
            r[_HELP_] = "true";
        }
        else
        {
            cout << "Parametre '" << argv[i] <<"' inconnu." << endl;
        }
        
    }
}

void Set(string* args, Task* t)
{
    if (args[_DESCRIPTION_] != DEFAULT)
        t->SetDescription(args[_DESCRIPTION_]);
    if (args[_DATE_] != DEFAULT)
        t->SetStartingDate(args[_DATE_]);
    if (args[_PRIORITY_] != DEFAULT)
        t->SetPriority(args[_PRIORITY_]);
    if (args[_STATUS_] != DEFAULT)
        t->SetStatus(args[_STATUS_]);
    if (args[_POURCENTAGE_] != DEFAULT)
        t->SetPourcentage(stoi(args[_POURCENTAGE_]));
}


void Extraire(string* args, TasksManager* T )
/*
Méthode qui extrait d'un TaskManager les critères demandés.
C'est le coeur de la méthode list
*/
{
    if (args[_ID_] != DEFAULT)
        T->KeepOnlyID(stoi(args[_ID_]));
    if (args[_TITLE_] != DEFAULT)
        T->KeepOnlyTitle(args[_TITLE_]);
    if (args[_DESCRIPTION_] != DEFAULT)
        T->KeepOnlyDescription(args[_DESCRIPTION_]);
    if (args[_DATE_] != DEFAULT)
        T->KeepOnlyStartingDate(args[_DATE_]);
    if (args[_PRIORITY_] != DEFAULT)
        T->KeepOnlyPriority(args[_PRIORITY_]);
    if (args[_STATUS_] != DEFAULT)
        T->KeepOnlyStatus(args[_STATUS_]);
    if (args[_POURCENTAGE_] != DEFAULT)
        T->KeepOnlyTitle(args[_POURCENTAGE_]);
}