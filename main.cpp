#include <iostream>
#include "src/LoadData.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    LoadData data;
    data.displayStops();
    data.displayLines();
    return 0;
}
