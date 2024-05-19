#include <iostream>
#include "data_structures/GraphConstructor.h"
#include "Manager.h"
#include "Menu.h"

std::string selectDataset(){
    int option = -1;

    std::cout << "\n\t:::: MENU ::::" << std::endl;
    std::cout << "1 - shipping" << std::endl;
    std::cout << "2 - stadiums" << std::endl;
    std::cout << "3 - tourism" << std::endl;
    std::cout << "4 - graph1" << std::endl;
    std::cout << "5 - graph2" << std::endl;
    std::cout << "6 - graph3" << std::endl;
    std::cout << "\nSelect Dataset: ";
    std::cin >> option;


    switch(option){
        case 1:
            return "shipping";
        case 2:
            return "stadiums";
        case 3:
            return "tourism";
        case 4:
            return "graph1";
        case 5:
            return "graph2";
        case 6:
            return "graph3";
        default:
            return selectDataset();
    }

}

int main() {

    std::string dataset = selectDataset();

    Manager manager = Manager("TSP Hero", dataset);

    Menu menu = Menu(manager);

    menu.start();

    return 0;
}


