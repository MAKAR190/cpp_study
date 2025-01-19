#include <iostream>
#include <queue>

using namespace std;

int main() {
    queue <int> q1;
    q1.push( 10 );
    q1.push( 20 );
    q1.push( 30 );
    queue <int>::size_type i;
    i = q1.size( );
    cout << "Długość kolejki wynosi " << i << "." << endl;
    int& ii = q1.back( ); // odczyt najnowszego elementu w kolejce
    int& iii = q1.front( ); // odczyt najstarszego elementu w kolejce
    cout << "Liczba z tyłu kolejki q1 to " << ii << "." << endl;
    cout << "Liczba stojąca na czele kolejki q1 to " << iii << "." << endl;
    q1.pop();
    i = q1.size();
    cout << "Po zdjęciu elementu długość kolejki wynosi " << i << "." << endl;
}