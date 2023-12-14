//
// Created by adamc on 07.12.2023.
//

#ifndef PEA2_SIMULATEDANNEALING_H
#define PEA2_SIMULATEDANNEALING_H


#include <vector>
#include "Timer.h"
#include "Matrix.h"
#include <cmath>

class SimulatedAnnealing {
public:
    SimulatedAnnealing(Matrix*, double, int);
    Matrix* matrix;

    std::vector<int> bestSolution;
    std::vector<int> newSolution;
    std::vector<int> currentSolution;
    int bestObjectiveFunction;
    int newObjectiveFunction;
    int currentObjectiveFunction;

    int stopCriteria;
    double whenFound;
    double a;
    double T_k;
    void launch(Timer timer);

    int calculateRoute();
    void generateBegSolutionGreedy(std::vector<int>&, int&);
    void printSolution();

    int findMin();
    int findMax();

};


#endif //PEA2_SIMULATEDANNEALING_H
