//
// Created by Davide Teixeira on 14/05/2024.
//

#include <fstream>
#include <condition_variable>
#include "Menu.h"

Menu::Menu(Manager manager) : manager(manager) {};

void Menu::printIntro() {
    std::cout << "\n+-----------------------------------+\n";
    std::cout << "|                                   |\n";
    std::cout << "|        DA PROJECT 2 - G05_2       |\n";
    std::cout << "|                                   |\n";
    std::cout << "+-----------------------------------+\n";
}

void Menu::mainMenu(){
    int option = -1;

    while (option != 0) {

        std::cout << "\n\t:::: MENU ::::" << std::endl;
        std::cout << "0 - Exit" << std::endl;
        std::cout << "1 - T2.1 - Backtracking Algorithm" << std::endl;
        std::cout << "2 - T2.2 - Triangular Approximation Heuristic" << std::endl;
        std::cout << "3 - T2.3 - Nearest Neighbour" << std::endl;
        std::cout << "4 - T2.3 - Nearest Neighbour + 2opt" << std::endl;
        std::cout << "5 - T2.4 - Real World Graphs - Nearest Neighbour" << std::endl;
        std::cout << "6 - T2.4 - Real World Graphs - Nearest Neighbour + 2opt" << std::endl;
        std::cout << "7 - Run all Algorithms and log to file" << std::endl;
        std::cout << "\nChoose an option:";
        std::cin >> option;

        switch (option) {

            case 0:
                std::cout << "Exiting... :)" << std::endl;
                break;

            case 1:
                t21();
                break;

            case 2:
                t22();
                break;

            case 3:
                t23_1();
                break;
            case 4:
                t23_2();
                break;

            case 5:
                t24_1();
                break;

            case 6:
                t24_2();
                break;

            case 7:
                runAllAlgorithmsAndLogIntoFile();
                break;

            default:
                std::cout << "Invalid option" << std::endl;
                break;

        }
    }
}

void Menu::t21(){
    std::cout << ":: TSP :: Backtracking Algorithm ::" << std::endl;

    Manager tempManager = manager;
    tempManager.replaceGraphToNew();
    std::vector<int> path;

    double min_weight = manager.backtrackingTSP(0, path);

    printPath(path);
    std::cout << "Sum Path is: " << min_weight << std::endl;
}


void Menu::t22(){
    std::cout << ":: TSP :: Triangular Approximation Heuristic ::" << std::endl;
    Manager tempManager = manager;
    tempManager.replaceGraphToNew();
    std::vector<int> path;
    double sum_path = tempManager.triangularApproximation(0, path);
    printPath(path);
    std::cout << "Sum Path is: " << sum_path << std::endl;
}

void Menu::t23_1(){
    std::cout << ":: TSP :: Nearest Neighbour ::" << std::endl;
    Manager tempManager = manager;
    tempManager.replaceGraphToNew();
    std::vector<int> path;
    double sum_path = tempManager.nearestNeighbour(0, path, true);
    printPath(path);
    std::cout << "Sum Path is: " << sum_path << std::endl;
};

void Menu::t23_2(){
    std::cout << ":: TSP :: Nearest Neighbour + 2opt ::" << std::endl;
    Manager tempManager = manager;
    tempManager.replaceGraphToNew();
    std::vector<int> path;
    double sum_path = tempManager.twoOptTSP(0, path, true);
    printPath(path);
    std::cout << "Sum Path is: " << sum_path << std::endl;
}

void Menu::t24_1(){
    std::cout << ":: TSP :: Real World Graphs - Nearest Neighbour ::" << std::endl;
    Manager tempManager = manager;
    tempManager.replaceGraphToNew();
    std::vector<int> path;
    int ini = getInitialVertex();
    double sum_path = tempManager.nearestNeighbour(ini, path, false);
    printPath(path);
    std::cout << "Sum Path is: " << sum_path << std::endl;
}

void Menu::t24_2(){
    std::cout << ":: TSP :: Real World Graphs - Nearest Neighbour + 2opt ::" << std::endl;
    Manager tempManager = manager;
    tempManager.replaceGraphToNew();
    std::vector<int> path;
    int ini = getInitialVertex();
    double sum_path = tempManager.twoOptTSP(ini, path, false);
    printPath(path);
    std::cout << "Sum Path is: " << sum_path << std::endl;
}

void Menu::runAllAlgorithmsAndLogIntoFile(){
    std::vector<std::string> datasets = {"25", "50", "75", "100", "200", "300", "400", "500", "600", "700",
                                         "800", "900", "graph1"};

    std::ofstream logFile("../algorithm_times.csv");

    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return;
    }

    logFile << "Dataset,Triangular Output,Triangular Time,Nearest Neighbour Output,Nearest Neighbour time"
               ",Nearest Neighbour + 2opt Output,Nearest Neighbour + 2opt Time,"
               "Real World Nearest Neighbour Output,Real World Nearest Neighbour Time,"
               "Real World Nearest Neighbour + 2opt Output,Real World Nearest Neighbour Time" << std::endl;

    for (auto dataset : datasets){
        Manager manager = Manager(dataset, dataset);

        std::cout << dataset << ", " << manager.getGraphSize() << std::endl;

        std::vector<int> eulerian_circuit = {};
        auto start = std::chrono::high_resolution_clock::now();
        double triangular_output = manager.triangularApproximation(0, eulerian_circuit);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> triangular = end - start;

        eulerian_circuit = {};
        manager = Manager(dataset, dataset);
        start = std::chrono::high_resolution_clock::now();
        double nearest_neighbour_output = manager.nearestNeighbour(0, eulerian_circuit, true);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> nearest_neighbour = end - start;

        eulerian_circuit = {};
        manager = Manager(dataset, dataset);
        start = std::chrono::high_resolution_clock::now();
        double nearest_neighbour_2opt_output = manager.twoOptTSP(0, eulerian_circuit, true);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> nearest_neighbour_2opt = end - start;

        eulerian_circuit = {};
        manager = Manager(dataset, dataset);
        start = std::chrono::high_resolution_clock::now();
        double real_world_nearest_output = manager.nearestNeighbour(5, eulerian_circuit, false);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> real_world_nearest_neighbour = end - start;

        eulerian_circuit = {};
        manager = Manager(dataset, dataset);
        start = std::chrono::high_resolution_clock::now();
        double real_world_nearest_output_2opt = manager.twoOptTSP(5, eulerian_circuit, false);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> real_world_nearest_neighbour_2opt = end - start;


        if (dataset == "graph1") dataset = "1000";

        logFile << dataset << "," << triangular_output << "," << triangular.count() << "," <<
                   nearest_neighbour_output << "," << nearest_neighbour.count()  << ","
                   << nearest_neighbour_2opt_output << "," << nearest_neighbour_2opt.count() << ","
                   << real_world_nearest_output << "," << real_world_nearest_neighbour.count()  << ","
                   << real_world_nearest_output_2opt << "," << real_world_nearest_neighbour_2opt.count() << std::endl;

    }
}

void Menu::printPath(const std::vector<int>& path){
    std::cout << "\nPath: " << std::endl;
    int i = 0;
    for (auto v : path){
        std::cout << v << " -> ";
        if (i % 20 == 19) std::cout << std::endl;
        i++;
    }
    std::cout << path[0] << "\n" << std::endl;
}

int Menu::getInitialVertex() {
    int num;
    std::cout << "Insert first vertex: ";
    std::cin >> num;
    return num;
}

void Menu::start() {
    printIntro();

    mainMenu();
}