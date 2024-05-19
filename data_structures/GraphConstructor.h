//
// Created by Davide Teixeira on 07/03/2024.
//

#ifndef DA_PROJ1_GRAPHCONSTRUCTOR_H
#define DA_PROJ1_GRAPHCONSTRUCTOR_H

#include "Graph.h"
#include <string>

/**
 * @class GraphConstructor
 * @brief Class responsible for constructing the graph.
 */
class GraphConstructor {
private:
    std::string dataset; /**< Dataset Name */
    std::string edgesFile;  /**< File Containing edges info */
    std::string verticiesFile; /**< File Containing verticies info */

    /**
     * @brief Parses a vertex to add it to the graph.
     * @param line Line containing vertex data.
     * @return int vertex
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    int parseFirstVertex(std::string line);

    /**
     * @brief Parses a vertex to add it to the graph.
     * @param line Line containing vertex data.
     * @return int vertex
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    int parseSecondVertex(std::string line);

    int n_verticies = 0; /**< Number of vertices */

    /**
     * @brief Parses an edge to add it to the graph.
     * @param line Line containing edge data.
     * @return double edge weight
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    double parseEdge(std::string line, int& first, int& second);

public:

    /**
     * @brief Constructor of the Graph
     * @param dataset Dataset containing graph's information
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    GraphConstructor(std::string dataset);

    /**
     * @brief default constructor
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    GraphConstructor() = default;

    /**
     * @brief Creates a graph with the dataset's information
     * @return Graph graph with the file's data
     * @par Complexity
       *   - Time: O(V+E)
       *   - Space: O(V+E)
     */
    Graph<int> createGraph();

    /**
     * @brief Creates an unordered_map to map the vertex index with its geographical coordinates
     * @return unordered_map that maps a vertex to its geographical coordinates
     * @par Complexity
       *   - Time: O(V)
       *   - Space: O(V)
     */
    std::unordered_map<int, std::pair<double, double>> getCoordinates();

};

#endif //DA_PROJ1_GRAPHCONSTRUCTOR_H