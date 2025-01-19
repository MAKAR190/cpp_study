#include <iostream>
#include <vector>
#include <queue>
using namespace std;


int main() {
    priority_queue<int, vector<int>, greater<int>> pqi;
    srand(time(0)); // uruchamiamy generator liczb losowych
    for(int i = 0; i < 100; i++)
        pqi.push(rand() % 25);
    while(!pqi.empty()) {
        cout << pqi.top() << ' ';
        pqi.pop();
    }
}