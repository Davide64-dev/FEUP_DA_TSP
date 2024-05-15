//
// Created by Davide Teixeira on 12/05/2024.
//

#ifndef DA_PROJ2_MANAGER_H
#define DA_PROJ2_MANAGER_H

#include <string>
#include "data_structures/GraphConstructor.h"

class Manager {
private:
    std::string name;
    GraphConstructor constructor;

public:
    Graph<int> network;

    std::unordered_map<int, std::pair<double, double>> coordinates;

    std::string getName();

    Manager(std::string name, std::string dataset);

    double haversine(double latitudeFirst, double longitudeFirst, double latitudeSecond, double longitudeSecond);

    Graph<int> prim();

    double triangularApproximation(std::vector<int>& eulerian_circuit);

    double nearestNeighbour(std::vector<int>& eulerian_circuit);

    double sumPath(const std::vector<int>& eulerian_circuit, const Graph<int>& mst);

};


#endif //DA_PROJ2_MANAGER_H
