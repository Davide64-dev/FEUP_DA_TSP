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
        std::cout << "1 - T4.1 - Backtracking Algorithm" << std::endl;
        std::cout << "2 - T4.2 - Triangular Approximation Heuristic" << std::endl;

        std::cout << "4 - T4.4 - Real World Graphs" << std::endl;
        std::cout << "\nChoose an option:";
        std::cin >> option;

        switch (option) {

            case 0:
                std::cout << "Exiting... :)" << std::endl;
                break;

            case 2:
                t42();
                break;

            case 4:
                t44();
                break;

            default:
                std::cout << "Invalid option" << std::endl;
                break;

        }
    }
}

void Menu::t42(){
    int i = 0;

    std::vector<int> path;

    double sum_path = manager.triangularApproximation(path);

    for (auto v : path){
        std::cout << v << " -> ";
        if (i % 20 == 19) std::cout << std::endl;
        i++;
    }

    std::cout << 0 << std::endl;

    std::cout << "Sum Path is: " << sum_path << std::endl;
}

void Menu::t44(){
    // TODO: Just the nearest neighbour heuristic here

    std::vector<int> path;
    int i = 0;

    double sum_path = manager.nearestNeighbour(path);

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