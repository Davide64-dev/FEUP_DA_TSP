#include <iostream>
#include "data_structures/GraphConstructor.h"

int main() {
    auto graphConstructor = GraphConstructor("shipping");
    Graph<int> graph = graphConstructor.createGraph();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
