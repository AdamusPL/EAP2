//
// Created by adamc on 07.12.2023.
//

#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(Matrix *matrix, double a, int stopCriteria) {
    this->matrix=matrix;
    this->a = a;
    this->stopCriteria = stopCriteria;
    this->bestObjectiveFunction = this->currentObjectiveFunction = 0;
}

void SimulatedAnnealing::launch(Timer timer) {

    //1. beginning solution generated with greedy algorithm
    generateBegSolutionGreedy(bestSolution, bestObjectiveFunction);
    generateBegSolutionGreedy(currentSolution, currentObjectiveFunction);
//    printSolution();
    int node2, node1;
    int delta;

    //beginning temperature - difference between maximum edge and minimum edge in graph
    T_k = findMax() - findMin();

    while(timer.stopTimer() / 1000000.0 < stopCriteria){ //1. while stop criteria

        for(int k=0; k<matrix->nrV*matrix->nrV/2; k++){ //2. reached number of eras, L=n^2/2

            //3. new y state in neighbourhood node2
            node1 = rand() % (matrix->nrV);
            node2 = rand() % (matrix->nrV); //get two random index of Nodes

            while (node2 == node1) { //we have to get two different indexes
                node2 = rand() % (matrix->nrV);
            }

            newSolution = currentSolution; //copy solution
            std::swap(newSolution[node1], newSolution[node2]); //swap two Nodes from random positions
            newObjectiveFunction = calculateRoute(); //calculate objectiveFunction

            //update best solution
            delta = newObjectiveFunction - currentObjectiveFunction;

            if(delta <= 0){ //4. delta = f(y)-f(x)
                currentSolution = newSolution;
                currentObjectiveFunction = newObjectiveFunction;

                delta = newObjectiveFunction - bestObjectiveFunction;

                if(delta <= 0){
                    bestSolution = newSolution;
                    bestObjectiveFunction = newObjectiveFunction;
                    whenFound = timer.stopTimer() / 1000000.0;
                }
            }

            //5. probability of tolerance of accepting worse solution
            else if(exp(-delta/T_k) >= static_cast<double>(rand()%100+1) / 100.0){ //if e^(-delta/T) >= random[0,1]
                currentSolution = newSolution;
                currentObjectiveFunction = newObjectiveFunction;
//                printSolution();
            }

        }
        //6. Decrease temperature
        T_k = a * T_k;
    }

    std::cout << "STOP! " << stopCriteria << " seconds passed" << std::endl;

}

int SimulatedAnnealing::findMin(){
    int min = INT_MAX;
    for (int i = 0; i < matrix->nrV; ++i) {
        for (int j = 0; j < matrix->nrV; ++j) {
            if(matrix->adjMatrix[i][j] < min && i!=j){
                min = matrix->adjMatrix[i][j];
            }
        }
    }
    return min;
}

int SimulatedAnnealing::findMax(){
    int max = 0;
    for (int i = 0; i < matrix->nrV; ++i) {
        for (int j = 0; j < matrix->nrV; ++j) {
            if(matrix->adjMatrix[i][j] > max && i!=j){
                max = matrix->adjMatrix[i][j];
            }
        }
    }
    return max;
}


int SimulatedAnnealing::calculateRoute(){
    int objectiveFunction = 0;

    for (int i = 1; i < newSolution.size(); ++i) {
        objectiveFunction+=matrix->adjMatrix[newSolution[i - 1]][newSolution[i]];
    }

    objectiveFunction+=matrix->adjMatrix[newSolution[newSolution.size() - 1]][newSolution[0]];

    return objectiveFunction;
}

void SimulatedAnnealing::generateBegSolutionGreedy(std::vector<int> &solution, int &objectiveFunction){

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

            if(matrix->adjMatrix[solution[i - 1]][j] < min && !visited[j]){
                min = matrix->adjMatrix[solution[i - 1]][j];
                node = j;
            }

        }

        solution.push_back(node);
        visited[node] = true;
        objectiveFunction += min;
    }

    objectiveFunction+=matrix->adjMatrix[solution[solution.size() - 1]][solution[0]]; //we come back to the beginning node

//    printSolution();

}


void SimulatedAnnealing::printSolution(){
    for (int i = 0; i < bestSolution.size(); ++i) {
        std::cout << bestSolution[i] << "->";
    }

    std::cout << bestSolution[0];
    std::cout<<std::endl;
    std::cout << bestObjectiveFunction << std::endl;

}
