#include <iostream>
#include "data_structures/GraphConstructor.h"

int main() {
    auto graphConstructor = GraphConstructor("graph1");
    Graph<int> graph = graphConstructor.createGraph();
    return 0;
}
