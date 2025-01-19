#include <iostream>
#include <fstream>
#include <set>
using namespace std;

void wordSet(const char* fileName) {
    ifstream source(fileName);
    string word;
    set<string> words;
    while(source >> word)
        words.insert(word);
    cout << "Liczba różnych słów w tekście:" << words.size() <<
    endl;
};
int main(int argc, char* argv[]) {
    if(argc > 1)
        wordSet(argv[1]);
    else
        wordSet("WordSet.cpp");
}