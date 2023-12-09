//
// Created by adamc on 07.12.2023.
//

#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(Matrix *matrix, double a, int stopCriteria) {
    this->matrix=matrix;
    this->a = a;
    this->stopCriteria = stopCriteria;
}

void SimulatedAnnealing::launch(Timer timer) {

    //1. random beginning solution
    generateBegSolutionGreedy();
    int x, i;
    int newObjectiveFunction;
    int delta;
    T_k = 1; //beginning temperature equals 1 (it's maximum)

    while(timer.stopTimer() / 1000000.0 < stopCriteria){

        while(timer.stopTimer() / 1000000.0 < stopCriteria) { //2. reached number of eras
            //3. new y state in neighbourhood x
            i = rand() % (matrix->nrV);
            x = rand() % (matrix->nrV); //get random number

            while (x == i) { //we should get different number of node than in which we are now
                x = rand() % (matrix->nrV);
            }

            std::swap(solution[i], solution[x]);
            newObjectiveFunction = calculateRoute();

            delta = newObjectiveFunction - objectiveFunction; //delta = f(x)-f(y)

            if (delta <= 0) { //we update objectiveFunction
                objectiveFunction = newObjectiveFunction;
//                printSolution();
            }

            //probability of tolerance of accepting worse solution
            else if(exp(-delta/T_k) >= static_cast<double>(rand()%100+1) / 100.0){ //if e^(-delta/T) >= random[0,1]
                objectiveFunction = newObjectiveFunction;
//                printSolution();
            }

            else{ //we come back to previous solution
                std::swap(solution[i], solution[x]);
            }

            //4. Decrease temperature
            T_k = a * T_k;

        }
    }

    std::cout << "Cost: " << objectiveFunction << std::endl;
    std::cout << "STOP! " << stopCriteria << " seconds passed" << std::endl;

}

int SimulatedAnnealing::calculateRoute(){
    int objectiveFunction = 0;

    for (int i = 1; i < solution.size(); ++i) {
        objectiveFunction+=matrix->adjMatrix[solution[i-1]][solution[i]];
    }

    objectiveFunction+=matrix->adjMatrix[solution[solution.size()-1]][solution[0]];

    return objectiveFunction;
}

void SimulatedAnnealing::generateBegSolutionGreedy(){

    std::vector<bool> visited; //vector helping to generate permutation

    for (int i = 0; i < matrix->nrV; ++i) { //filling the vector
        visited.push_back(false);
    }

    solution.push_back(0);
    visited[0] = true;

    srand(time(NULL)); //initialize the seed
    int min;
    int node;

    for (int i = 1; i < matrix->nrV; ++i) {

        min = INT_MAX;

        for (int j = 1; j < matrix->nrV; ++j) {

            if(matrix->adjMatrix[solution[i-1]][j] < min && !visited[j]){
                min = matrix->adjMatrix[solution[i-1]][j];
                node = j;
            }

        }

        solution.push_back(node);
        visited[node] = true;
        objectiveFunction += min;
    }

    objectiveFunction+=matrix->adjMatrix[solution[solution.size()-1]][solution[0]]; //we come back to the beginning node

//    printSolution();

}

void SimulatedAnnealing::printSolution(){
    for (int i = 0; i < solution.size(); ++i) {
        std::cout << solution[i] << "->";
    }

    std::cout << solution[0];
    std::cout<<std::endl;
    std::cout<<objectiveFunction<<std::endl;

}