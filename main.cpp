#include <iostream>
#include "data_structures/GraphConstructor.h"
#include "Manager.h"
#include "Menu.h"

int main() {
    Manager manager = Manager("temp", "graph1");

    Menu menu = Menu(manager);

    menu.start();

    return 0;
}
