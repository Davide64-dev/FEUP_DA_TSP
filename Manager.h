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
    double computeDelta(const std::vector<int>& tour, int i, int j);

public:

    std::string getName() const;

    Manager(std::string name, std::string dataset);

    Graph<int> prim();

    void backtracking(int vertex, std::vector<int>& path, std::vector<bool>& visited, double& min_path_weight, double curr_path_weight, std::vector<int>& best_path);

    double backtrackingTSP(int initial, std::vector<int>& eulerian_circuit);

    double triangularApproximation(int initial, std::vector<int>& eulerian_circuit);

    double nearestNeighbour(int initial, std::vector<int>& eulerian_circuit);

    double sumPath(int initial, const std::vector<int>& eulerian_circuit);

    void twoOpt(std::vector<int>& tour);

    double twoOptTSP(int initial, std::vector<int>& eulerian_circuit);

};


#endif //DA_PROJ2_MANAGER_H
