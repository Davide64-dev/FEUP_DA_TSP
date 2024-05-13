#include <iostream>
#include "data_structures/GraphConstructor.h"
#include "Manager.h"

int main() {
    auto manager = Manager("temp", "graph1");
    manager.prim();
    return 0;
}
