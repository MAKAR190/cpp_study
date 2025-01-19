#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main () {
    stack < string , vector <string > > str_stack ;
    // albo np.: stack <string, list<string> > str_stack;
    // albo też po prostu: stack <string> str_stack;
    string quote [3] = {" Ala \n", "ma\n", " kota \n"};
    for ( int i = 0; i < 3; ++i)
        str_stack.push(quote[i]); // umieszcza kopię na szczycie stosu
    while (!str_stack.empty()) {
        cout << str_stack.top(); // zwraca referencję do elementu na szczycie
        str_stack.pop(); // zdejmuje szczytowy element ze stosu
    }
}
