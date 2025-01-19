#include <iostream>
#include <string>

class LoggerMixin {
public:
    void log(const std::string& message) {
        std::cout << "Log: " << message << std::endl;
    }
};

class Application : public LoggerMixin {
public:
    void run() {
        log("Application is running");
    }
};

int main() {
    Application app;
    app.run();
    return 0;
}
