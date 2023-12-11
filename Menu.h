//
// Created by adamc on 29.11.2023.
//

#ifndef PEA2_MENU_H
#define PEA2_MENU_H


#include "Matrix.h"
#include "Timer.h"
#include <fstream>
#include <vector>

class Menu {
public:

    Menu();
    void option1();
    void option2();
    void option3();
    void option4();
    void option5();
    void option6();
    void option7();
    void option8();
    void printSolution();

    std::vector<int> solution;
    int objectiveFunction;
    Matrix* matrix;
    int stopCriteria;
    double a;
    int coolingOption;
    Timer timer;
};


#endif //PEA2_MENU_H
