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


GraphConstructor::GraphConstructor(std::string dataset) : dataset(dataset){

    if (dataset == "shipping"){
        verticiesFile = "";
        edgesFile = "../Datasets/Toy-Graphs/shipping.csv";
    }

    else if (dataset == "stadiums"){
        verticiesFile = "";
        edgesFile = "../Datasets/Toy-Graphs/stadiums.csv";
    }

    else if (dataset == "tourism"){
        verticiesFile = "";
        edgesFile = "../Datasets/Toy-Graphs/tourism.csv";
    }

    else if (dataset == "graph1"){
        verticiesFile = "../Datasets/Real_world_Graphs/graph1/nodes.csv";
        edgesFile = "../Datasets/Real_world_Graphs/graph1/edges.csv";
    }

    else if (dataset == "graph2"){
        verticiesFile = "../Datasets/Real_world_Graphs/graph2/nodes.csv";
        edgesFile = "../Datasets/Real_world_Graphs/graph2/edges.csv";
    }

    else if (dataset == "graph3"){
        verticiesFile = "../Datasets/Real_world_Graphs/graph3/nodes.csv";
        edgesFile = "../Datasets/Real_world_Graphs/graph3/edges.csv";
    }

    // TODO: Make here the extra fully connected graphs
}

Graph<int> GraphConstructor::createGraph(){

    Graph<int> res = Graph<int>();
    std::string line;
    if (verticiesFile == ""){


        std::ifstream inVerticies(edgesFile);
        getline(inVerticies, line); // for jumping header
        while(getline(inVerticies, line)){
            int FirstVertex = parseFirstVertex(line);
            int SecondVertex = parseSecondVertex(line);
            if (res.findVertex(FirstVertex) == nullptr)
                res.addVertex(FirstVertex);
            if (res.findVertex(SecondVertex) == nullptr)
                res.addVertex(SecondVertex);
        }
    }

    else{
        std::ifstream inVerticies(verticiesFile);
        getline(inVerticies, line);
        while(getline(inVerticies, line)){
            int FirstVertex = parseFirstVertex(line);
            res.addVertex(FirstVertex);
        }
    }

    // Parsing the edges
    std::ifstream inEdges(edgesFile);
    getline(inEdges, line); // for jumping header
    while(getline(inEdges, line)){
        int first, second;
        double weight = parseEdge(line, first, second);
        res.addBidirectionalEdge(first, second, weight);
    }

    return res;

}

int GraphConstructor::parseFirstVertex(std::string line){
    std::vector<std::string> lineParsed;
    std::string word;
    std::istringstream iss(line);
    while(getline(iss, word, ',')){
        lineParsed.push_back(word);
    }
    return std::stoi(lineParsed[0]);
}

int GraphConstructor::parseSecondVertex(std::string line){
    std::vector<std::string> lineParsed;
    std::string word;
    std::istringstream iss(line);
    while(getline(iss, word, ',')){
        lineParsed.push_back(word);
    }
    return  std::stoi(lineParsed[1]);
}

double GraphConstructor::parseEdge(std::string line, int& first, int& second){
    std::vector<std::string> lineParsed;
    std::string word;
    std::istringstream iss(line);
    while(getline(iss, word, ',')){
        lineParsed.push_back(word);
    }

    first = std::stoi(lineParsed[0]);
    second = std::stoi(lineParsed[1]);
    return  std::stod(lineParsed[2]);
}

std::unordered_map<int, std::pair<double, double>> GraphConstructor::getCoordinates(){
    std::unordered_map<int, std::pair<double, double>> res;
    std::ifstream inVerticies(verticiesFile);
    std::string line;
    getline(inVerticies, line); // for jumping header
    while(getline(inVerticies, line)){
        std::istringstream iss(line);
        std::string word;
        std::vector<std::string> lineParsed;
        while(getline(iss, word, ',')){
            lineParsed.push_back(word);
        }
        int node = std::stoi(lineParsed[0]);
        double latitude = std::stod(lineParsed[1]);
        double longidute = std::stod(lineParsed[2]);
        std::pair<double, double> temp = {latitude, longidute};
        res[node] = temp;
    }

    return res;
}