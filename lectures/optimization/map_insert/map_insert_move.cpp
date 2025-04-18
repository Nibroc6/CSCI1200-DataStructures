#include <iostream>
#include <map>
#include <vector>
#include <string>

class LargeClass {
public:
    std::vector<int> data;
    std::string name;

    LargeClass(int size, const std::string& n) : data(size), name(n) {
        // simulate work in the constructor
        for (int i = 0; i < size; ++i) {
            data[i] = i;
        }
    }

    // define a copy constructor for demonstration purposes
    LargeClass(const LargeClass& other) : data(other.data), name(other.name) {
        // std::cout << "Copy constructor called\n";
    }

    // define a move constructor
    LargeClass(LargeClass&& other) noexcept : data(std::move(other.data)), name(std::move(other.name)) {
        // std::cout << "Move constructor called\n";
    }

    // for demonstration, printing the object contents
    void print() const {
        std::cout << name << ": " << data[0] << "..." << data[data.size() - 1] << std::endl;
    }
};

int main() {
    const int num_elements = 10000000;
    const int map_size = 10;

    std::map<int, LargeClass> map_insert;

    for (int i = 0; i < map_size; ++i) {
        map_insert.insert({i, LargeClass(num_elements, "Insert_" + std::to_string(i))});
    }

    return 0;
}

