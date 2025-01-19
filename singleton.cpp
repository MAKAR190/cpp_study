#include <iostream>
#include <sstream>
using namespace std;

class Singleton {
    static Singleton s;
    int i;
    Singleton(int x=0) : i(x) { } // konstr. domyślny - prywatny
    Singleton(const Singleton&); // konstr. kopiujący - prywatny
    Singleton& operator=(Singleton&); // operator przypisania - prywatny
public:
    static Singleton& instance() { return s; }
    int getValue() { return i; }
    void setValue(int x) { i = x; }
};
Singleton Singleton::s(47); // inicjalizacja składowej statycznej
int main() {
    Singleton& s = Singleton::instance();
    cout << s.getValue() << endl;
    Singleton& s2 = Singleton::instance();
    s2.setValue(9);
    cout << s.getValue() << endl;
}
