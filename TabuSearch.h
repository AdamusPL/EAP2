//
// Created by adamc on 29.11.2023.
//

#ifndef PEA2_TABUSEARCH_H
#define PEA2_TABUSEARCH_H

#include <iostream>
#include <list>
#include <vector>
#include "Matrix.h"

class TabuSearch {
public:
    TabuSearch(Matrix* matrix);
    //attribute - 
    //cadence - how long element is stored on tabuList
    std::list<std::pair<int,int>> tabuList; //attribute + cadence
    std::vector<int> solution;
    int bestSolution;
    void launch();
    std::vector<std::pair<bool, int>> generateBegSolution();
    Matrix* matrix;


};


#endif //PEA2_TABUSEARCH_H
