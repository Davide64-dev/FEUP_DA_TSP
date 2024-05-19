#include <iostream>
#include "data_structures/GraphConstructor.h"
#include "Manager.h"
#include "Menu.h"

int main() {
    Manager manager = Manager("Toy Graph Stadiums", "stadiums");

    Menu menu = Menu(manager);

    menu.start();

    return 0;
}
