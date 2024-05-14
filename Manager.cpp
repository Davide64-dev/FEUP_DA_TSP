//
// Created by Davide Teixeira on 12/05/2024.
//

#include <unordered_set>
#include "Manager.h"

double Manager::haversine(double latitudeFirst, double longitudeFirst, double latitudeSecond, double longitudeSecond){
    // Transformation into radians
    double rad_lat1 = latitudeFirst * M_PI / 180;
    double rad_lon1 = longitudeFirst * M_PI / 180;
    double rad_lat2 = latitudeSecond * M_PI / 180;
    double rad_lon2 = longitudeSecond * M_PI / 180;

    // latitude and longitude variance
    double delta_lat = rad_lat2 - rad_lat1;
    double delta_lon = rad_lon2 - rad_lon1;

    // distance computation
    double aux = pow(sin(delta_lat / 2), 2) +
               pow(sin(delta_lon / 2), 2) * cos(rad_lat1) * cos(rad_lat2);

    double c = 2.0 * atan2(sqrt(aux), sqrt(1.0-aux));

    double earthradius = 6371000.0;

    return earthradius * c;
}

Manager::Manager(std::string name, std::string dataset) : name(name) {
    constructor = GraphConstructor(dataset);
    network = constructor.createGraph();
    coordinates = constructor.getCoordinates();
}

Graph<int> Manager::prim() {
    Graph<int> minSpanningTree;

    minSpanningTree.addVertex(0);

    std::unordered_set<int> already_in;

    already_in.insert(0);

    while (minSpanningTree.getNumVertex() < network.getNumVertex()) {
        std::cout << "Minimum Spanning tree size " << minSpanningTree.getNumVertex() << std::endl;
        std::cout << "Network size " << network.getNumVertex() << std::endl;
        int minWeight = std::numeric_limits<int>::max();
        int minVertex = -1;
        int minEdge = -1;

        for (auto vertex : minSpanningTree.getVertexSet()) {
            auto vertexOriginalGraph = network.findVertex(vertex->getInfo());
            for (auto edge : vertexOriginalGraph->getAdj()) {
                if (already_in.find(edge->getDest()->getInfo()) == already_in.end()){
                    if (edge->getWeight() < minWeight) {
                        minWeight = edge->getWeight();
                        minVertex = vertexOriginalGraph->getInfo();
                        minEdge = edge->getDest()->getInfo();
                    }
                }
            }
        }

        // TODO: check better the haversine distance - graph1 is fully connected

        minSpanningTree.addVertex(minEdge);
        already_in.insert(minEdge);
        minSpanningTree.addBidirectionalEdge(minVertex, minEdge, minWeight);
    }

    return minSpanningTree;
}

double Manager::sumPath(const std::vector<int>& eulerian_circuit, const Graph<int>& mst){
    auto current = mst.findVertex(0);
    double sum = 0.0;
    for (int i = 1; i < eulerian_circuit.size(); i++){
        auto next = eulerian_circuit[i];
        for (auto edge : current->getAdj()){
            if (edge->getDest()->getInfo() == next){
                sum += edge->getWeight();
            }
        }
        current = mst.findVertex(next);
    }

    auto lastVertex = network.findVertex(eulerian_circuit[eulerian_circuit.size() - 1]);

    for (auto edge : lastVertex->getAdj()){
        if (edge->getDest()->getInfo() == 0){
            sum += edge->getWeight();
            break;
        }
    }

    return sum;
}

double Manager::triangularApproximation(){
    auto mst = prim();

    // double the edges to get an eulerian graph
    for (auto v : mst.getVertexSet()){
        for (auto e : v->getAdj()){
            mst.addBidirectionalEdge(v->getInfo(), e->getDest()->getInfo(), e->getDest()->getDist());
        }
    }

    auto path = mst.dfs();

    double sum_path = sumPath(path, mst);

    return sum_path;
}