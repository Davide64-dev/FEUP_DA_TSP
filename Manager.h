//
// Created by Davide Teixeira on 12/05/2024.
//

#ifndef DA_PROJ2_MANAGER_H
#define DA_PROJ2_MANAGER_H

#include <string>
#include "data_structures/GraphConstructor.h"

/**
 * @class Manager
 * @brief Class for managing TSP network operations.
 */
class Manager {
private:
    std::string name; /**< Name of the manager. */
    GraphConstructor constructor; /**< Graph constructor instance. Responsible for constructing the graph */
    Graph<int> network; /**< Network graph */
    std::unordered_map<int, std::pair<double, double>> coordinates;  /**< Map of vertices - Maps the vertices to its geographical coordinates */

    /**
     * @brief Calculates the distance between two geographical points using the haversine distance algorithm
     * @param latitudeFirst Latitude of the first point
     * @param longitudeFirst Longitude of the first point
     * @param latitudeSecond Latitude of the second point
     * @param longitudeSecond Longitude of the second point
     * @return The distance between two points
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    double haversine(double latitudeFirst, double longitudeFirst, double latitudeSecond, double longitudeSecond);

    /**
     * @brief Calculates the distance between two points of the graph - If an edge exists, the distance is the weight of the edge. If not, the distance is the haversine distance
     * @param vertex1 First vertex
     * @param vertex2 Second Vertex
     * @param isFullyConnected Flag indicating if the graph is fully connected or not
     * @return Distance between the two vertices
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    double distance(int vertex1, int vertex2, bool isFullyConnected = true);

    /**
     * @brief Computes the change in the total distance of a tour if a segment between nodes i and j is reversed.
     *
     * This function calculates the change (delta) in the total distance of a tour if the segment between
     * the indices i and j is reversed. It is used in optimization algorithms such as 2-opt for the
     * Traveling Salesman Problem (TSP) to determine if reversing a segment reduces the total tour distance.
     *
     * @param tour A vector of integers representing the sequence of nodes in the current tour.
     * @param i The index of the first node in the tour where a modification is being considered.
     * @param j The index of the second node in the tour where a modification is being considered.
     * @param isFullyConnected A boolean flag indicating whether the graph is fully connected or not.
     *                         This parameter might influence the behavior of the distance function.
     * @return The change (delta) in the total distance if the segment between i and j is reversed.
     *
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    double computeDelta(const std::vector<int>& tour, int i, int j, bool isFullyConnected = true);

public:

    /**
     * @brief Getter of the name of the manager
     * @return name of the manager
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    std::string getName() const;

    /**
     * @brief Replaces the manager's graph with a new one using the constructor
     * @par Complexity
       *   - Time: O(V + E)
       *   - Space: O(V + E)
     */
    void replaceGraphToNew();

    /**
     * @brief Getter of the graph size
     * @return Graph Size
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    int getGraphSize() const;

    /**
     * @brief Creates a new Manager with a given dataset
     * @param name Name of the manager
     * @param dataset Dataset with graph's data
     * @par Complexity
       *   - Time: O(V+E)
       *   - Space: O(V+E)
     */
    Manager(std::string name, std::string dataset);

    /**
     * @brief Performs Prim's algorithm to the graph
     * @return MCST using prim's algorithm
     * @par Complexity
       *   - Time: O((V+E)logV)
       *   - Space: O(V+E)
     */
    Graph<int> prim();

    /**
     * @brief Performs triangular approximation algorithm for the TSP problem
     * @param initial Initial vertex
     * @param eulerian_circuit Param output with the eulerian circuit
     * @return the sum of the TSP path
     * @par Complexity
       *   - Time: O((V+E)logV)
       *   - Space: O(V+E)
     */
    double triangularApproximation(int initial, std::vector<int>& eulerian_circuit);

    /**
     * @brief Performs the Nearest Neighbour Approximation algorithm for the TSP problem
     * @param initial Initial Vertex
     * @param eulerian_circuit Param output with the eulerian circuit
     * @param isFullyConnected Flag indicating if the graph is fully connected
     * @return the sum of the TSP path
     * @par Complexity
       *   - Time: O(V+E)
       *   - Space: O(V)
     */
    double nearestNeighbour(int initial, std::vector<int>& eulerian_circuit, bool isFullyConnected = true);

    /**
     * @brief Calculates the total sum of a path
     * @param initial Initial vertex
     * @param eulerian_circuit Param output with the eulerian circuit
     * @param isFullyConnected Flag indicating if the graph is fully connected
     * @return the sum of the TSP path
     * @par Complexity
       *   - Time: O(V)
       *   - Space: O(1)
     */
    double sumPath(int initial, const std::vector<int>& eulerian_circuit, bool isFullyConnected = true);

    /**
     * @brief Calculates the 2 optimization
     * @param tour Initial tour - outputs the final tour also
     * @param isFullyConnected Flag indicating if the graph is fully connected
     * @par Complexity
       *   - Time: O(V^2)
       *   - Space: O(1)
     */
    void twoOpt(std::vector<int>& tour, bool isFullyConnected = true);

    /**
     * @brief Calculates the 2 optimization for the TSP problem
     * @param initial Initial Vertex
     * @param eulerian_circuit Outputs the final tour optimized
     * @param isFullyConnected Flag indicating if the graph is fully connected
     * @return the sum of the TSP path
     * @par Complexity
       *   - Time: O(V^2)
       *   - Space: O(V)
     */
    double twoOptTSP(int initial, std::vector<int>& eulerian_circuit, bool isFullyConnected = true);

};


#endif //DA_PROJ2_MANAGER_H
