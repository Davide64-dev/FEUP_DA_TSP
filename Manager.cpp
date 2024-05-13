//
// Created by Davide Teixeira on 12/05/2024.
//

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

    minSpanningTree.addVertex(network.findVertex(0)->getInfo());

    while (minSpanningTree.getNumVertex() < network.getNumVertex()) {
        int minWeight = std::numeric_limits<int>::max();
        int minVertex = -1;
        int minEdge = -1;

        for (auto vertex : minSpanningTree.getVertexSet()) {
            for (auto edge : vertex->getAdj()) {
                if (minSpanningTree.findVertex(edge->getDest()->getInfo()) == nullptr) {
                    if (edge->getWeight() < minWeight) {
                        minWeight = edge->getWeight();
                        minVertex = vertex->getInfo();
                        minEdge = edge->getDest()->getInfo();
                    }
                }
            }
        }

        // If no direct edge is found, calculate Haversine distance
        if (minWeight == std::numeric_limits<int>::max()) {
            // Retrieve coordinates of the vertices
            double lat1 = coordinates[minVertex].first;
            double lon1 = coordinates[minVertex].second;
            double lat2 = coordinates[minEdge].first;
            double lon2 = coordinates[minEdge].second;

            // Calculate Haversine distance
            double distance = haversine(lat1, lon1, lat2, lon2);

            // Update minWeight and minEdge
            minWeight = distance;
        }

        minSpanningTree.addVertex(minEdge);
        minSpanningTree.addBidirectionalEdge(minVertex, minEdge, minWeight);
    }

    return minSpanningTree;
}
