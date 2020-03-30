#ifndef MAIN
#define MAIN

int main(int argc, char *argv[]);
void Args(int argc, char* argv[], string* r);

void Set(string* args, Task* t);;
void Extraire(string* args, TasksManager* T );


//CONSTANTES
#define _ID_ 0
#define _TITLE_ 1
#define _DESCRIPTION_ 2
#define _DATE_ 3
#define _PRIORITY_ 4
#define _STATUS_ 5
#define _POURCENTAGE_ 6
#define _HELP_ 7
#define N 8
#define DEFAULT ((string)"__null__")


#endif