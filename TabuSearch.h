//
// Created by adamc on 29.11.2023.
//

#ifndef PEA2_TABUSEARCH_H
#define PEA2_TABUSEARCH_H

#include <iostream>
#include <list>
#include <vector>
#include "Matrix.h"
#include "Timer.h"

class TabuSearch {
public:
    TabuSearch(Matrix* matrix, int stopCriteria);
    //attribute - 
    //cadence - how long element is stored on tabuList
    std::list<std::pair<int,int>> tabuList; //attribute + cadence
    std::vector<int> solution;
    int objectiveFunction;
    void launch(Timer timer);
    void generateBegSolution();
    int calculateRoute();
    void printSolution();
    Matrix* matrix;
    int stopCriteria;

};


#endif //PEA2_TABUSEARCH_H
