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
        //std::cout << "Minimum Spanning tree size " << minSpanningTree.getNumVertex() << std::endl;
        //std::cout << "Network size " << network.getNumVertex() << std::endl;
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
    auto current = network.findVertex(0);
    double sum = 0.0;
    for (int i = 1; i < eulerian_circuit.size(); i++){
        auto next = eulerian_circuit[i];
        for (auto edge : current->getAdj()){
            if (edge->getDest()->getInfo() == next){
                sum += edge->getWeight();
            }
        }
        current = network.findVertex(next);
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

double Manager::nearestNeighbour(std::vector<int>& eulerian_circuit){
    auto current = network.findVertex(0);
    current->setVisited(true);
    eulerian_circuit.push_back(0);
    double sum = 0.0;

    while (eulerian_circuit.size() < network.getNumVertex()){
        auto min = INT_MAX;
        auto minNext = -1;
        for (auto e : current->getAdj()){
            if (e->getWeight() < min && !e->getDest()->isVisited()){
                min = e->getWeight();
                minNext = e->getDest()->getInfo();
            }
        }
        current = network.findVertex(minNext);
        current->setVisited(true);
        eulerian_circuit.push_back(minNext);
        sum += min;
    }

    for (auto edge : current->getAdj()){
        if (edge->getDest()->getInfo() == 0){
            sum += edge->getWeight();
            break;
        }
    }


    return sum;
}

double Manager::triangularApproximation(std::vector<int>& eulerian_circuit){
    auto mst = prim();

    // double the edges to get an eulerian graph
    for (auto v : mst.getVertexSet()){
        for (auto e : v->getAdj()){
            mst.addBidirectionalEdge(v->getInfo(), e->getDest()->getInfo(), e->getDest()->getDist());
        }
    }

    eulerian_circuit = mst.dfs();

    double sum_path = sumPath(eulerian_circuit, mst);

    return sum_path;
}

void Manager::twoOpt(std::vector<int>& tour) {
    bool improved = true;
    while (improved) {
        improved = false;
        for (int i = 1; i < tour.size() - 2; i++) {
            for (int j = i + 1; j < tour.size() - 1; j++) {
                double delta = computeDelta(tour, i, j);
                if (delta < 0) {
                    reverse(tour.begin() + i, tour.begin() + j + 1);
                    improved = true;
                }
            }
        }
    }
}

double Manager::distance(int vertex1, int vertex2) {
    // Use your haversine function or any other distance function here
    // For example:

    auto actualVertex = network.findVertex(vertex1);

    for (auto edge : actualVertex->getAdj()){
        if (edge->getDest()->getInfo() == vertex2) return edge->getWeight();
    }

    double lat1 = coordinates[vertex1].first;
    double lon1 = coordinates[vertex1].second;
    double lat2 = coordinates[vertex2].first;
    double lon2 = coordinates[vertex2].second;
    return haversine(lat1, lon1, lat2, lon2);
}

double Manager::computeDelta(const std::vector<int>& tour, int i, int j) {
    double delta = 0.0;

    delta += distance(tour[i - 1], tour[j]) + distance(tour[i], tour[j + 1]);
    delta -= distance(tour[i - 1], tour[i]) + distance(tour[j], tour[j + 1]);

    return delta;
}

double Manager::twoOptTSP(std::vector<int>& eulerian_circuit) {
    // Get an initial solution, e.g., using nearest neighbor heuristic
    double initial_distance = nearestNeighbour(eulerian_circuit);

    // Improve the initial solution using 2-opt heuristic
    twoOpt(eulerian_circuit);

    // Calculate the total distance after improvement
    double total_distance = sumPath(eulerian_circuit, network);

    return total_distance;
}