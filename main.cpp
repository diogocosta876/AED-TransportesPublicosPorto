#include <iostream>
#include "src/LoadData.h"
#include "src/AdminMenu.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    LoadData data;
    //data.debug_displayEdges();
    AdminMenu menu = AdminMenu(data);
    menu.mainMenu();
    return 0;
}
