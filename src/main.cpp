#include <iostream>
#include <array>
#include <iomanip>
#include "event.h"
#include "calendar.h"
using namespace std;

int main(){
    Month m(1, 2023); 
    cout << m;
    
    Event party(2023, 11, 16, 20, 30, 0.07, -500 , "party time! ツ", "test", "test");
    cout << party << endl;
    cout << party.getEventDate() << endl;
    cout << party.getEventTimeString() << endl;

    Event upsideDownParty(2023, 11, 16, 20, 30, 5.23, 930 , "(: ¡ǝɯıʇ ʎʇɹɐd", "ʇsǝʇ", "ʇsǝʇ");
    cout << "\n" << upsideDownParty << endl;
    return 0;
}
