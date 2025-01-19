#include <iostream>
#include <vector>
#include <deque>

int main(int argc, char* argv[]) {
    using namespace std;
    int size = 25;
    deque<int> d;
    // tutaj wypełnienie kontenera określoną liczba obiektów typu int
    cout << "\n Konwersja do wektora (1)" << endl;
    vector<int> v1(d.begin(), d.end());
    cout << "\n Konwersja do wektora (2)" << endl;
    vector<int> v2;
    v2.reserve(d.size());
    v2.assign(d.begin(), d.end());
}