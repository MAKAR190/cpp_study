#include <iostream>
#include <fstream>
#include <map>
using namespace std;

int main() {
    multimap<string, string> directory;
    directory.insert(pair<string, string>("T","555-4533"));
    directory.insert(pair<string, string>("T","555-9999"));
    directory.insert(pair<string, string>("C","555-9678"));
    string str;
    cout << "Podaj imię: ";
    cin >> str;
    multimap<string, string>::iterator p = directory.find(str);
    if(p != directory.end()) {
        do {
            cout << "Numer telefonu: " << p->second << endl;
            p++;
        } while(p != directory.upper_bound(str)); // pierwszy element,
        // którego klucz jest większy
    }
    else
        cout << "Nie ma takiego użytkownika telefonu.\n";
}
