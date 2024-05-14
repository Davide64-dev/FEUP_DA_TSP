#include <iostream>
#include "data_structures/GraphConstructor.h"
#include "Manager.h"

int main() {
    auto manager = Manager("temp", "graph1");
    auto sum_path = manager.triangularApproximation();

    std::cout << "Sum Path is: " << sum_path << std::endl;
    return 0;
}
