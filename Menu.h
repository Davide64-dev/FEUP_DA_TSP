//
// Created by Davide Teixeira on 14/05/2024.
//

#ifndef DA_PROJ2_MENU_H
#define DA_PROJ2_MENU_H


#include "Manager.h"

/**
 * @class Menu
 * @brief Class for handling user interface and menu functionalities.
 */
class Menu {
private:
    Manager manager;  /**< Instance of the Manager class. */

    /**
     * @brief Starts the main menu
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
    */
    void mainMenu();

    /**
     * @brief Performs task T 2.2 - Triangular Inequality
     * @par Complexity
       *   - Time: O((V+E)logV)
       *   - Space: O(V+E)
    */
    void t22();

    /**
     * @brief Performs tak T 2.3 - A chosen heuristic (Nearest Neighbour)
     * @par Complexity
       *   - Time: O(V^2)
       *   - Space: O(V)
     */
    void t23_1();

    /**
     * @brief Performs tak T 2.3 - A chosen heuristic (Nearest Neighbour + 2 OPT)
     * @par Complexity
       *   - Time: O(V^2)
       *   - Space: O(V)
     */
    void t23_2();

    /**
     * @brief Performs tak T 2.4 - Real World TSP - Nearest Neighbour
     * @par Complexity
       *   - Time: O(V+E)
       *   - Space: O(V)
     */
    void t24_1();

    /**
     * @brief Performs tak T 2.3 - A chosen heuristic (Nearest Neighbour + 2 OPT)
     * @par Complexity
       *   - Time: O(V^2)
       *   - Space: O(V)
     */
    void t24_2();

    /**
     * @brief Prints the eulerian circuit in a user-friendly-way
     * @param path Path to be printed
     * @par Complexity
       *   - Time: O(V)
       *   - Space: O(1)
     */
    void printPath(const std::vector<int>& path);

    /**
     * @brief Function to get the users input initial vertex
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    int getInitialVertex();

    /**
     * @brief Auxiliary function that runs the code in different datasets and outputs the result and the execution time to a file "algorithm_times.csv"
     * @par Complexity
       *   - Time: O(n)
       *   - Space: O(1)
     */
    void runAllAlgorithmsAndLogIntoFile();

    /**
     * @brief Prints the menu's intro
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    void printIntro();

public:
    /**
     * @brief Constructor for Menu class.
     * @param manager Instance of the Manager class.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    Menu(Manager manager);

    /**
     * @brief Starts the menu system.
     * @par Complexity
        *   - Time: O(1)
        *   - Space: O(1)
     */
    void start();

};


#endif //DA_PROJ2_MENU_H
