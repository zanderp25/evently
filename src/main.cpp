#include <iostream>
#include <array>
#include <iomanip>
// #include "event.h"
#include "calendar.h"
using namespace std;

int main(){
    Month m(1, 2023);
    cout << m;

    std::string party_name = "Party time ツ";
    Event party(2023, 11, 16, 20, 30, party_name, "test", "test");
    cout << party << endl;
    cout << party.getEventDate() << endl;
    cout << party.getEventTime() << endl;
    return 0;
}
