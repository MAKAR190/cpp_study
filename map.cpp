#include <iostream>
#include <fstream>
#include <map>
using namespace std;

typedef map<string, int> WMap;
WMap words;
void wordMap(const char* fileName) {
    ifstream source(fileName);
    string word;
    while(source >> word)
        words[word]++; // (!)
};
int main(int argc, char* argv[]) {
    if(argc > 1)
        wordMap(argv[1]);
    else
        wordMap("WordMap.cpp");
    for (WMap::iterator w = words.begin(); w!=words.end(); w++)
        cout << w->first << ":" << w->second << endl;
    cout << "Liczba różnych słów w tekście:" << words.size() << endl;
}