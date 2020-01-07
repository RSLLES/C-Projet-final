#include "Priority_Status.hpp"
#include <string>
using namespace std;

int main(){
    Priority p;
    cout << p.Get() << endl;
    p.Set(1);
    cout << p.Get() << endl;
    p.Set("Low");
    cout << p.Get() << endl;
    p.Set(4);
    cout << p.Get() << endl;
};