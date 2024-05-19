//
// Created by Davide Teixeira on 14/05/2024.
//

#ifndef DA_PROJ2_MENU_H
#define DA_PROJ2_MENU_H


#include "Manager.h"

class Menu {
private:
    Manager manager;
    void mainMenu();
    void t22();
    void t23_1();
    void t23_2();
    void t24_1();
    void t24_2();
    void printPath(const std::vector<int>& path);

    int getInitialVertex();

    void runAllAlgorithmsAndLogIntoFile();
    void printIntro();

public:
    Menu(Manager manager);
    void start();

};


#endif //DA_PROJ2_MENU_H
