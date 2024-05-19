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
    Graph<int> network;
    std::unordered_map<int, std::pair<double, double>> coordinates;
    double haversine(double latitudeFirst, double longitudeFirst, double latitudeSecond, double longitudeSecond);
    double distance(int vertex1, int vertex2, bool isFullyConnected = true);
    double computeDelta(const std::vector<int>& tour, int i, int j, bool isFullyConnected = true);

public:

    std::string getName() const;

    int getGraphSize() const;

    Manager(std::string name, std::string dataset);

    Graph<int> prim();

    double triangularApproximation(int initial, std::vector<int>& eulerian_circuit);

    double nearestNeighbour(int initial, std::vector<int>& eulerian_circuit, bool isFullyConnected = true);

    double sumPath(int initial, const std::vector<int>& eulerian_circuit, bool isFullyConnected = true);

    void twoOpt(std::vector<int>& tour, bool isFullyConnected = true);

    double twoOptTSP(int initial, std::vector<int>& eulerian_circuit, bool isFullyConnected = true);

};


#endif //DA_PROJ2_MANAGER_H
