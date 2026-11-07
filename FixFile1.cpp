#include <windows.h>
#include <iostream>
#include <memory>
#include <string>

struct FileDeleter {
    void operator()(FILE* f) const {
        if (f != nullptr) fclose(f);
    }
};

int ParseValue(const std::string& token) {
    // looks innocent, but throws on non-numeric input
    return std::stoi(token);
}

void DoSomething(FILE* f) {
    char buf[256];
    while (fgets(buf, sizeof(buf), f)) {
        std::string line(buf);
        // strip newline
        line.erase(line.find_last_not_of("\n\r") + 1);

        int val = ParseValue(line); // throws if file has a bad line // lower case p in function name
        std::cout << "Value: " << val << "\n";
    }
}

void ProcessFile(const std::string& path)
{
    std::unique_ptr<FILE, FileDeleter> f(fopen(path.c_str(), "r"));
    if (!f) return;
    DoSomething(f.get()); // if DoSmoething throws error fclose() is never called, causing a leak
}