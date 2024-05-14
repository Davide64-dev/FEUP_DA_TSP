#include <iostream>
#include "data_structures/GraphConstructor.h"
#include "Manager.h"

int main() {
    auto manager = Manager("temp", "graph1");
    auto x = manager.prim();

    for (auto v : x.getVertexSet()){
        for (auto e : v->getAdj()){
            std::cout << "Just adding" << std::endl;
            x.addBidirectionalEdge(v->getInfo(), e->getDest()->getInfo(), e->getDest()->getDist());
        }
    }
    return 0;
}
