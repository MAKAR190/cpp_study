#include <iostream>
#include <string>

class Printable {
public:
    virtual void print() const = 0; // czysto wirtualna metoda
    virtual ~Printable() = default; // wirtualny destruktor
};

class Document : public Printable {
private:
    std::string content;
public:
    Document(const std::string& text) : content(text) {}
    void print() const override {
        std::cout << "Document content: " << content << std::endl;
    }
};

int main() {
    Document doc("Hello, world!");
    doc.print();
    return 0;
}
