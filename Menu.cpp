//
// Created by Davide Teixeira on 14/05/2024.
//

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
        std::cout << "\nChoose an option:";
        std::cin >> option;

        switch (option) {

            case 0:
                std::cout << "Exiting... :)" << std::endl;
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

            default:
                std::cout << "Invalid option" << std::endl;
                break;

        }
    }
}

void Menu::t22(){
    std::vector<int> path;
    double sum_path = manager.triangularApproximation(0, path);
    printPath(path);
    std::cout << "Sum Path is: " << sum_path << std::endl;
}

void Menu::t23_1(){
    std::vector<int> path;
    double sum_path = manager.nearestNeighbour(0, path, true);
    printPath(path);
    std::cout << "Sum Path is: " << sum_path << std::endl;
};

void Menu::t23_2(){
    std::vector<int> path;
    double sum_path = manager.nearestNeighbour(0, path, true);
    printPath(path);
    std::cout << "Sum Path is: " << sum_path << std::endl;
}

void Menu::t24_1(){
    std::vector<int> path;
    int ini = getInitialVertex();
    double sum_path = manager.nearestNeighbour(ini, path, false);
    printPath(path);
    std::cout << "Sum Path is: " << sum_path << std::endl;
}

void Menu::t24_2(){
    std::vector<int> path;
    int ini = getInitialVertex();
    double sum_path = manager.twoOptTSP(ini, path, false);
    printPath(path);
    std::cout << "Sum Path is: " << sum_path << std::endl;
}

void Menu::printPath(const std::vector<int>& path){
    int i = 0;
    for (auto v : path){
        std::cout << v << " -> ";
        if (i % 20 == 19) std::cout << std::endl;
        i++;
    }
    std::cout << path[0] << std::endl;
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