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
    std::vector<int> solution;
    int objectiveFunction;
    int stopCriteria;
    double a;
    double T_k;
    void launch(Timer timer);

    int calculateRoute();
    void generateBegSolutionGreedy();
    int generateSolutionGreedyTheWorst();
    void printSolution();

    void generateBegSolutionRandom();
    int bestRandom;
    std::vector<int> bestRandomSolution;
    int findMin();
    int findMax();

};


#endif //PEA2_SIMULATEDANNEALING_H
