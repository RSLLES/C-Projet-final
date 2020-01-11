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


//##########################
//TasksManager
//##########################

TasksManager::TasksManager() : liste() {}
TasksManager::TasksManager(vector<Task> _liste) : liste(_liste) {}
TasksManager::TasksManager(string filePath) {
    //On ouvre le fichier
}


bool TasksManager::SaveToFile(string filePath){
    //Ouverture du fichier
    ofstream myfile (filePath);
    if (myfile.is_open())
    {
        for(int i(0); i < liste.size(); ++i)
        {
            myfile << liste[i].StringToExport() << endl;
        }
        return true;
    }
    cout << "Unable to open file " << filePath << endl;
    return false;
}