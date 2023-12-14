//
// Created by adamc on 29.11.2023.
//

#include "TabuSearch.h"
#include "Cmp.h"
#include <random>
#include <queue>

TabuSearch::TabuSearch(Matrix* matrix, int stopCriteria){
    this->matrix = matrix;
    objectiveFunction = 0;
    this->stopCriteria = stopCriteria;
}

void TabuSearch::launch(Timer timer){

    //1. Choose beginning bestSolution x_0
    generateBegSolutionGreedy();

    //2. Neighbourhood
    int x;
    int newObjectiveFunction;
    int numberOfSwaps = 0; //just to check
    std::pair<int, std::pair<int,int>> bestSolution;

    //make a min heap from it
    // <newObjectiveFunctionValue, <indexOfSwappedNode1, indexOfSwappedNode2>>
    std::priority_queue<std::pair<int, std::pair<int,int>>> priorityQueue;

    while(timer.stopTimer() / 1000000.0 < stopCriteria) { //until it reaches stopCriteria (specified time in seconds)
        for (int i = 0; i < matrix->nrV; ++i) {

            x = rand() % (matrix->nrV); //get random number

            while (x == i) { //we should get different number of node than in which we are now
                x = rand() % (matrix->nrV);
            }

            std::swap(solution[i], solution[x]);
            newObjectiveFunction = calculateRoute();

            if (newObjectiveFunction < objectiveFunction) {
                priorityQueue.emplace(newObjectiveFunction,std::make_pair(i, x));
            }

            std::swap(solution[i], solution[x]); //come back to previous bestSolution

        }

        if(!priorityQueue.empty()) {
            bestSolution = priorityQueue.top();

            //update bestSolution and objective function with new best bestSolution
            std::swap(solution[bestSolution.second.first], solution[bestSolution.second.second]);
            objectiveFunction = bestSolution.first;
//            numberOfSwaps++;

//            printSolution();
//            std::cout<<"Swap: "<<bestSolution[bestSolution.second.first]<<" z "<<bestSolution[bestSolution.second.second] <<std::endl;
//            std::cout<<"Wykonano swapow: "<<numberOfSwaps<<std::endl;

            while(!priorityQueue.empty()){
                priorityQueue.pop(); //empty the queue
            }
        }

    }

    std::cout << "Score: " << objectiveFunction << std::endl;
    std::cout << "STOP! " << stopCriteria << " seconds passed" << std::endl;

}

int TabuSearch::calculateRoute(){
    int objectiveFunction = 0;

    for (int i = 1; i < solution.size(); ++i) {
        objectiveFunction+=matrix->adjMatrix[solution[i-1]][solution[i]];
    }

    objectiveFunction+=matrix->adjMatrix[solution[solution.size()-1]][solution[0]];

    return objectiveFunction;
}

//has to be greedy
//method to generate beginning bestSolution
void TabuSearch::generateBegSolutionRandom(){

    std::vector<bool> visited; //vector helping to generate permutation

    for (int i = 0; i < matrix->nrV; ++i) { //filling the vector
        visited.push_back(false);
    }

    srand(time(NULL)); //initialize the seed
    int x;

    for (int i = 0; i < matrix->nrV; ++i) {
        x = rand()%(matrix->nrV); //get random number

        while(visited[x]){ //if it exists in bestSolution, generate once again
            x = rand()%(matrix->nrV);
        }

        solution.push_back(x);
        visited[x] = true; //we visit every node once

        if(i>0){
            objectiveFunction+=matrix->adjMatrix[solution[i-1]][solution[i]]; //calculate objective function
        }

    }

    objectiveFunction+=matrix->adjMatrix[solution[solution.size()-1]][solution[0]]; //we come back to the beginning node

//    printSolution();

}

void TabuSearch::generateBegSolutionGreedy(){

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

void TabuSearch::printSolution(){
    for (int i = 0; i < solution.size(); ++i) {
        std::cout << solution[i] << "->";
    }

    std::cout << solution[0];
    std::cout<<std::endl;
    std::cout<<objectiveFunction<<std::endl;

}