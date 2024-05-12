//
// Created by Davide Teixeira on 07/03/2024.
//

#include "GraphConstructor.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <unordered_map>


GraphConstructor::GraphConstructor(std::string edgesFile, std::string verticiesFile) : edgesFile(edgesFile), verticiesFile(verticiesFile) {};

GraphConstructor::GraphConstructor() : edgesFile("../Extra_Fully_Connected_Graphs/nodes.csv"), verticiesFile("../Extra_Fully_Connected_Graphs/edges_25.csv") {};

