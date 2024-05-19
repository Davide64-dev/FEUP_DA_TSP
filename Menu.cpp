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

        std::cout << "4 - T2.4 - Real World Graphs - Nearest Neighbour" << std::endl;
        std::cout << "5 - T2.4 - Real World Graphs - Nearest Neighbour + 2opt" << std::endl;
        std::cout << "\nChoose an option:";
        std::cin >> option;

        switch (option) {

            case 0:
                std::cout << "Exiting... :)" << std::endl;
                break;

            case 1:
                t41();
                break;

            case 2:
                t42();
                break;

            case 4:
                t44();
                break;

            case 5:
                t44_2();
                break;

            default:
                std::cout << "Invalid option" << std::endl;
                break;

        }
    }
}

void Menu::t41(){
    std::cout << ":: TSP :: Backtracking Algorithm ::" << std::endl;
    std::cout << ":: Dataset: " << manager.getName() << std::endl;

    std::vector<int> path;
    int i = 0;

    double min_weight = manager.backtrackingTSP(0, path);

    std::cout << "\nPath: " << std::endl;

    for (auto v : path){
        std::cout << v << " -> ";
        if (i % 20 == 19) std::cout << std::endl;
        i++;
    }

    std::cout << 0 << std::endl;

    std::cout << "\nMin Path Weight: " << min_weight << std::endl;
}

void Menu::t42(){
    int i = 0;

    std::vector<int> path;

    double sum_path = manager.triangularApproximation(0, path);

    for (auto v : path){
        std::cout << v << " -> ";
        if (i % 20 == 19) std::cout << std::endl;
        i++;
    }

    std::cout << 0 << std::endl;

    std::cout << "Sum Path is: " << sum_path << std::endl;
}

void Menu::t44(){
    std::vector<int> path;
    int i = 0;

    double sum_path = manager.nearestNeighbour(0, path);

    for (auto v : path){
        std::cout << v << " -> ";
        if (i % 20 == 19) std::cout << std::endl;
        i++;
    }
    std::cout << 0 << std::endl;

    std::cout << "Sum Path is: " << sum_path << std::endl;
}

void Menu::t44_2(){
    std::vector<int> path;
    int i = 0;

    double sum_path = manager.twoOptTSP(0, path);

    for (auto v : path){
        std::cout << v << " -> ";
        if (i % 20 == 19) std::cout << std::endl;
        i++;
    }
    std::cout << 0 << std::endl;

    std::cout << "Sum Path is: " << sum_path << std::endl;
}

void Menu::start() {
    printIntro();

    mainMenu();
}