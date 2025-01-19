#include <iostream>
#include <vector>
using namespace std;

class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() {};
};
class Circle : public Shape {
public:
    void draw(){ cout <<"C::draw"<< endl;};
    ~Circle(){ cout <<"~Circle"<< endl;};
};
class Square : public Shape {
public:
    void draw(){ cout << "Square::draw" <<
    endl; };
    ~Square(){ cout << "~Square" << endl;
    };
};
int main() {
    typedef std::vector<Shape*> C1;
    typedef C1::iterator I;
    C1 F;
    // dodajemy wskaźniki na obiekty
    F.push_back(new Circle);
    F.push_back(new Square);
    // wywołujemy polimorficzną metodę draw
    for(I j = F.begin(); j != F.end(); j++)
        (*j)->draw();
    // ...
    for(I k = F.begin(); k != F.end(); k++)
        delete *k;
}