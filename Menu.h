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
    void t42();
    void t44();
    void printIntro();

public:
    Menu(Manager manager);
    void start();

};


#endif //DA_PROJ2_MENU_H
