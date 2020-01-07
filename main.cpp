#include "Priority_Status.hpp"
#include <string>
using namespace std;

int main(){
    Priority p;
    cout << p.GetPriority() << endl;
    p.SetPriority("Hight");
    cout << p.GetPriority() << endl;
    p.SetPriority(2);
    cout << p.GetPriority() << endl;
    p.SetPriority(3);
    cout << p.GetPriority() << endl;
};