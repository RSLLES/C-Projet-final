#include "Priority_Status.hpp"
#include <string>
using namespace std;

int main(){
    Priority p;
    cout << p.Get() << endl;
    p.Set("Hight");
    cout << p.Get() << endl;
    p.Set(2);
    cout << p.Get() << endl;
    p.Set(3);
    cout << p.Get() << endl;
};