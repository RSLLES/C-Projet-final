#include "Task.hpp"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;


Task::Task(int _id, string _title) : id(_id), title(_title), description(), pourcentage(0), priority(), status()
{
    //On créer une priorité, qui est donc par défaut sur Normale
    

}

Task::Task(int _id, string _title)
{Task(_id, _title, "");}