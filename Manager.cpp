//
// Created by Davide Teixeira on 12/05/2024.
//

#include <unordered_set>
#include "Manager.h"

std::string Manager::getName() const{
    return name;
}

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

int Manager::getGraphSize() const{
    return network.getNumVertex();
}

Manager::Manager(std::string name, std::string dataset) : name(name) {
    constructor = GraphConstructor(dataset);
    network = constructor.createGraph();
    coordinates = constructor.getCoordinates();
}

Graph<int> Manager::prim() {
    Graph<int> minSpanningTree;

    // Priority queue to store edges based on weight
    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<>> pq;

    // Start with any vertex (here, 0)
    minSpanningTree.addVertex(0);

    std::unordered_set<int> visited;
    visited.insert(0);

    // Add all adjacent edges of the starting vertex to the priority queue
    auto startVertex = network.findVertex(0);
    for (auto edge : startVertex->getAdj()) {
        pq.push({edge->getWeight(), {0, edge->getDest()->getInfo()}});
    }

    while (minSpanningTree.getNumVertex() < network.getNumVertex()) {
        // Get the minimum weight edge from the priority queue
        auto minEdge = pq.top();
        pq.pop();

        int weight = minEdge.first;
        int srcVertex = minEdge.second.first;
        int destVertex = minEdge.second.second;

        // If the destination vertex is already visited, skip
        if (visited.find(destVertex) != visited.end()) {
            continue;
        }

        // Add the destination vertex to the minimum spanning tree
        minSpanningTree.addVertex(destVertex);
        minSpanningTree.addBidirectionalEdge(srcVertex, destVertex, weight);

        // Mark destination vertex as visited
        visited.insert(destVertex);

        // Add all adjacent edges of the destination vertex to the priority queue
        auto vertex = network.findVertex(destVertex);
        for (auto edge : vertex->getAdj()) {
            int nextVertex = edge->getDest()->getInfo();
            if (visited.find(nextVertex) == visited.end()) {
                pq.push({edge->getWeight(), {destVertex, nextVertex}});
            }
        }
    }

    return minSpanningTree;
}

double Manager::sumPath(int initial, const std::vector<int>& eulerian_circuit, bool isFullyConnected){
    auto current = network.findVertex(initial);
    double sum = 0.0;
    for (int i = 1; i < eulerian_circuit.size(); i++){
        auto next = eulerian_circuit[i];
        for (auto edge : current->getAdj()){
            if (edge->getDest()->getInfo() == next){
                sum += distance(next, current->getInfo(), isFullyConnected);
            }
        }
        current = network.findVertex(next);
    }

    auto lastVertex = network.findVertex(eulerian_circuit[eulerian_circuit.size() - 1]);

    sum += distance(lastVertex->getInfo(), initial, isFullyConnected);

    return sum;
}

double Manager::nearestNeighbour(int initial, std::vector<int>& eulerian_circuit, bool isFullyConnected){
    auto current = network.findVertex(initial);
    current->setVisited(true);
    eulerian_circuit.push_back(initial);
    double sum = 0.0;

    while (eulerian_circuit.size() < network.getNumVertex()){
        current->setVisited(true);
        auto min = INT_MAX;
        auto minNext = -1;
        for (auto e : current->getAdj()){
            if (!e->getDest()->isVisited()) {
                auto dist = distance(e->getDest()->getInfo(), current->getInfo(), isFullyConnected);
                if (dist < min) {
                    min = dist;
                    minNext = e->getDest()->getInfo();
                }
            }
        }
        current = network.findVertex(minNext);
        if (current == nullptr) break;
        std::cout << "Current circuit size: " << eulerian_circuit.size() << std::endl;
        std::cout << "Next vertex: " << minNext << std::endl;
        eulerian_circuit.push_back(minNext);
        sum += min;
    }

    sum += distance(initial, current->getInfo(), isFullyConnected);


    return sum;
}

double Manager::triangularApproximation(int initial, std::vector<int>& eulerian_circuit){
    auto mst = prim();

    // double the edges to get an eulerian graph
    for (auto v : mst.getVertexSet()){
        for (auto e : v->getAdj()){
            mst.addBidirectionalEdge(v->getInfo(), e->getDest()->getInfo(), e->getDest()->getDist());
        }
    }

    eulerian_circuit = mst.dfs(initial);

    double sum_path = sumPath(initial, eulerian_circuit);

    return sum_path;
}

void Manager::twoOpt(std::vector<int>& tour, bool isFullyConnected) {
    std::cout << "two opt called\n";
    int max = 100;
    int count = 0;
    bool improved = true;
    while (improved && count < max) {
        improved = false;
        for (int i = 1; i < tour.size() - 2; i++) {
            for (int j = i + 1; j < tour.size() - 1; j++) {
                double delta = computeDelta(tour, i, j, isFullyConnected);
                if (delta < 0) {
                    reverse(tour.begin() + i, tour.begin() + j + 1);
                    improved = true;
                }
            }
        }
        count++;
    }
}

double Manager::distance(int vertex1, int vertex2, bool isFullyConnected) {

    auto actualVertex = network.findVertex(vertex1);

    auto edge = actualVertex->getSpecificAdj(vertex2);
    if (edge != nullptr)return edge->getWeight();

    if (isFullyConnected) {
        double lat1 = coordinates[vertex1].first;
        double lon1 = coordinates[vertex1].second;
        double lat2 = coordinates[vertex2].first;
        double lon2 = coordinates[vertex2].second;
        return haversine(lat1, lon1, lat2, lon2);
    }

    return INT_MAX;
}

double Manager::computeDelta(const std::vector<int>& tour, int i, int j, bool isFullyConnected) {
    double delta = 0.0;

    delta += distance(tour[i - 1], tour[j]) + distance(tour[i], tour[j + 1], isFullyConnected);
    delta -= distance(tour[i - 1], tour[i]) + distance(tour[j], tour[j + 1], isFullyConnected);

    return delta;
}

double Manager::twoOptTSP(int initial, std::vector<int>& eulerian_circuit, bool isFullyConnected) {

    // Get an initial solution, e.g., using nearest neighbor heuristic
    nearestNeighbour(initial, eulerian_circuit, isFullyConnected);

    // Improve the initial solution using 2-opt heuristic
    twoOpt(eulerian_circuit, isFullyConnected);

    // Calculate the total distance after improvement
    double total_distance = sumPath(initial, eulerian_circuit, isFullyConnected);

    return total_distance;
}