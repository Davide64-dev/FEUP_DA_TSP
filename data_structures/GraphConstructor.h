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
    std::string edgesFile;
    std::string verticiesFile;

    void parseAndAddVertex(std::string line);

    void parseAndAddEdge(std::string line);

public:
    GraphConstructor(std::string edgesFile, std::string verticiesFile);

    GraphConstructor();

    Graph<std::string> createGraph();
};

#endif //DA_PROJ1_GRAPHCONSTRUCTOR_H