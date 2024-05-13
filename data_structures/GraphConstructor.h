//
// Created by Davide Teixeira on 07/03/2024.
//

#ifndef DA_PROJ1_GRAPHCONSTRUCTOR_H
#define DA_PROJ1_GRAPHCONSTRUCTOR_H

#include "Graph.h"
#include <unordered_map>
#include <string>

class GraphConstructor {
private:
    std::string dataset;
    std::string edgesFile;
    std::string verticiesFile;

    int parseFirstVertex(std::string line);
    int parseSecondVertex(std::string line);

    double parseEdge(std::string line, int& first, int& second);

public:
    GraphConstructor(std::string dataset);

    GraphConstructor() = default;

    Graph<int> createGraph();

    std::unordered_map<int, std::pair<double, double>> getCoordinates();

};

#endif //DA_PROJ1_GRAPHCONSTRUCTOR_H