#include "Task.hpp"
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

//###########################
//Task
//###########################

Task::Task(int _id, string _title) : id(_id), title(_title), description(), pourcentage(0), priority(), status(), starting_date(new Date()), ending_date(nullptr) {}

vector<string> split(const string& s, char delimiter)
//Fonction retournant un vector<string> a partir d'un string en spératant a chaque caractère delimiter
{
   vector<string> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

Task::Task(string line) : id(-1), title("ERROR"), description(), pourcentage(0), priority(), status(), starting_date(new Date()), ending_date(nullptr) {
    //Au cas ou le ficheir serait illisible, on créer une tache de type ERREUR
    //On créer la tache à partir de ce qui est noté dans la ligne.
    //On utilise pour cela la fonction split qui coupe au niveau des ; en renvoyant un vector<string>
    vector<string> elements(split(line, ';'));
    if (elements.size() != 12 && elements.size() != 9){ //Si jamais il n'y a pas le bon nombre d'éléments
        cout << "Impossible de construire la tache a partir de : " << line << endl;
    }
    else
    {
        id = stoi(elements[0]);
        title = elements[1];
        description = elements[2];
        
        starting_date->SetDay(stoi(elements[3]));
        starting_date->SetMonth(stoi(elements[4]));
        starting_date->SetYear(stoi(elements[5]));

        //On ne créer la date de fin que si elle existe
        if (elements.size() == 12){
            ending_date = new Date(stoi(elements[6]),stoi(elements[7]),stoi(elements[8]));
            status.Set(elements[9]);
            pourcentage = stoi(elements[10]);
            priority.Set(elements[11]);
        }
        else
        {
            status.Set(elements[6]);
            pourcentage = stoi(elements[7]);
            priority.Set(elements[8]);
        }
        
    }
}

Task::~Task(){delete starting_date; delete ending_date;}

void Task::Print(){
    cout << "[" << id << "] " << title << " : " << description << endl;
    cout << "Demarre le ";
    starting_date->Print();
    cout << endl << "Status : " << status.Get() << " | Progression : " << pourcentage << "/100"
    << " | Priorite : " << priority.Get();
}

string Task::StringToExport(){
    //On utilise le point-virgule comme symbole séparateur
    string s;
    s = to_string(id) + ";" + title  + ";" + description  + ";" + 
    to_string(starting_date->GetDay()) + ";" + to_string(starting_date->GetMonth()) + ";" + to_string(starting_date->GetYear()) + ";";
    if (ending_date != nullptr)
    {
        s+= to_string(ending_date->GetDay()) + ";" + to_string(ending_date->GetMonth()) + ";" + to_string(ending_date->GetYear()) + ";";
    }
    s+= status.Get() + ";" + to_string(pourcentage) + ";" + priority.Get();
    return s;
}

int Task::GetID(){return id;}
string Task::GetTitle(){return title;}
string Task::GetDescription(){return description;}
string Task::GetStartingDate(){return (to_string(starting_date->GetDay()) + "/" 
                                        + to_string(starting_date->GetMonth()) + "/" 
                                        + to_string(starting_date->GetYear()));}
string Task::GetPriority(){return priority.Get();}
string Task::GetStatus(){return status.Get();}

void Task::SetDescription(string _description){description = _description;}
void Task::SetStartingDate(int _day, int _month, int _year) {delete starting_date; starting_date = new Date(_day, _month, _year);}
void Task::SetStartingDate(string line) {
    vector<string> s(split(line, '/'));
    if (s.size() != 3){
        cout << "ERREUR : Impossible de convertir '" << line << "' en une Date" << endl;
        return;
    }
    delete starting_date;
    starting_date = new Date(stoi(s[0]),stoi(s[1]),stoi(s[2]));
}
void Task::SetPriority(string line){priority.Set(line);}
void Task::SetStatus(string line){status.Set(line);}
void Task::SetPourcentage(int _pourcentage){
    if (pourcentage >= 0 && pourcentage <= 100){
        pourcentage = _pourcentage;
    }
    else{
        cout << "ERREUR : Impossible de mettre " << pourcentage << " comme pourcentage : celui ci doit être compris entre 0 et 100 inclus." << endl;
    }
}



//##########################
//TasksManager
//##########################

TasksManager::TasksManager() : liste() {}
TasksManager::TasksManager(vector<Task*> _liste) : liste(_liste) {}
TasksManager::TasksManager(string filePath): liste() {
    //On ouvre le fichier
    string line;
    ifstream myfile (filePath);
    if (myfile.is_open())
    {
        while (getline(myfile,line))
        {
            liste.push_back(new Task(line));
        }
        myfile.close();
    }
    else
    {
        cout << "Impossible d'ouvrir " << filePath << " dans le constructeur de TasksManager";
    }
    
}
TasksManager::~TasksManager(){
        for (vector<Task*>::iterator it(liste.begin()); it != liste.end(); it++){
        delete (*it);
    }
}

//Retourne le nombre de tache dans notre TaskManager
int TasksManager::Count(){return liste.size();}


bool TasksManager::SaveToFile(string filePath){
    //Ouverture du fichier
    ofstream myfile (filePath);
    if (myfile.is_open())
    {
        for(int i(0); i < liste.size(); ++i)
        {
            myfile << liste[i]->StringToExport() << endl;
        }
        return true;
    }
    cout << "Unable to open file " << filePath << endl;
    return false;
}


void TasksManager::Add(Task* task)
{
    liste.push_back(task);
}

bool TasksManager::Delete(int _id){
    for (vector<Task*>::iterator it(liste.begin()); it != liste.end(); it++){
        if ((*it)->GetID() == _id){
            Task* t = (*it); //On note le pointeur
            liste.erase(it); //On l'enleve de la liste
            delete t; //On le retire de la mémoire
            return true; //Car l'élément est unique
        }
    }
    return false;
}

int TasksManager::GetNewID() {
    //On trouve simplement le plus grand ID, et l'on renvoie l'entier naturel suivant
    int max = 0;
    for (int i(0); i < liste.size(); i++){
        if (liste[i]->GetID() > max){
            max = liste[i]->GetID();
        }
    }
    return max+1;
}

vector<int> TasksManager::GetAllIDs()
//Retourne un tableau contenant les IDs de toutes les taches existante
{
    vector<int> ids;
    for (vector<Task*>::iterator it(liste.begin()); it != liste.end(); it++)
        ids.push_back((*it)->GetID());
    return ids;
}


void TasksManager::KeepOnlyID(int _id){
    for (vector<Task*>::iterator it(liste.begin()); it != liste.end(); it++){
        if ((*it)->GetID() != _id){ //Si jamais la tache considérée ne respecte pas le critère
            Task* t = (*it); //On note le pointeur
            liste.erase(it); //On l'enleve de la liste
            delete t; //On le retire de la mémoire
            it--; //Car on ne veut pas sauter un élément
        }
    }
}

void TasksManager::KeepOnlyTitle(string _title){
    cout << "DANS LA PLACE BB" << endl;
    for (vector<Task*>::iterator it(liste.begin()); it != liste.end(); it++){
        if ((*it)->GetTitle().find(_title) == string::npos){ //Si jamais la tache considérée ne respecte pas le critère
            Task* t = (*it); //On note le pointeur
            liste.erase(it); //On l'enleve de la liste
            delete t; //On le retire de la mémoire
            it--; //Et on revient en arrière pour pas sauter un élément
        }
    }
}

void TasksManager::KeepOnlyDescription(string _description){
    for (vector<Task*>::iterator it(liste.begin()); it != liste.end(); it++){
        if ((*it)->GetDescription().find(_description) == string::npos){ //Si jamais la tache considérée ne respecte pas le critère
            Task* t = (*it); //On note le pointeur
            liste.erase(it); //On l'enleve de la liste
            delete t; //On le retire de la mémoire
            it--; //Et on revient en arrière pour pas sauter un élément
        }
    }
}

void TasksManager::KeepOnlyStartingDate(string _date){
    for (vector<Task*>::iterator it(liste.begin()); it != liste.end(); it++){
        if ((*it)->GetStartingDate().find(_date) == string::npos){ //Si jamais la tache considérée ne respecte pas le critère
            Task* t = (*it); //On note le pointeur
            liste.erase(it); //On l'enleve de la liste
            delete t; //On le retire de la mémoire
            it--; //Et on revient en arrière pour pas sauter un élément
        }
    }
}

void TasksManager::KeepOnlyPriority(string _prio){
    for (vector<Task*>::iterator it(liste.begin()); it != liste.end(); it++){
        if ((*it)->GetPriority().find(_prio) == string::npos){ //Si jamais la tache considérée ne respecte pas le critère
            Task* t = (*it); //On note le pointeur
            liste.erase(it); //On l'enleve de la liste
            delete t; //On le retire de la mémoire
            it--; //Et on revient en arrière pour pas sauter un élément
        }
    }
}

void TasksManager::KeepOnlyStatus(string _status){
    //On itère pour tous les éléments de la liste
    for (vector<Task*>::iterator it(liste.begin()); it != liste.end(); it++){
        if ((*it)->GetStatus().find(_status) == string::npos){ //Si jamais la tache considérée ne respecte pas le critère
            Task* t = (*it); //On note le pointeur
            liste.erase(it); //On l'enleve de la liste
            delete t; //On le retire de la mémoire
            it--; //Et on revient en arrière pour pas sauter un élément
        }
    }
}



void TasksManager::Print(){
    for (vector<Task*>::iterator it(liste.begin()); it != liste.end(); it++){
        (*it)->Print(); cout << endl << endl;
    }
}