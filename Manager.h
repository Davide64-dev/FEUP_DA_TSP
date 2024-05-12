//
// Created by Davide Teixeira on 12/05/2024.
//

#ifndef DA_PROJ2_MANAGER_H
#define DA_PROJ2_MANAGER_H

#include <string>
#include "data_structures/GraphConstructor.h"

class Manager {
private:
    std::string name;
    GraphConstructor constructor;

public:
    Graph<int> network;

    std::string getName();

    Manager(std::string name, std::string dataset);

    double haversine(double latitudeFirst, double longitudeFirst, double latitudeSecond, double longitudeSecond);

    Graph<int> prim();


};


#endif //DA_PROJ2_MANAGER_H
