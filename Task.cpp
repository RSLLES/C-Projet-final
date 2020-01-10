#include "Task.hpp"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;


Task::Task(int _id, string _title) : id(_id), title(_title), description(), pourcentage(0), priority(), status()
{
    //On intialise la date de départ
    starting_date = new Date();
}

Task::~Task(){delete starting_date; delete ending_date;}

void Task::Print(){
    cout << "[" << id << "] " << title << " : " << description << endl;
    cout << "Demarre le ";
    starting_date->Print();
    cout << endl << "Status : " << status.Get() << " | Progression : " << pourcentage << "/100"
    << " | Priorite : " << priority.Get();
}