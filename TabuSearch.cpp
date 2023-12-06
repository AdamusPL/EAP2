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

    //1. Choose beginning solution x_0
    generateBegSolutionGreedy();

    //2. Neighbourhood
    int x;
    int newObjectiveFunction;
    int numberOfSwaps = 0; //just to check
    std::pair<int, std::pair<int,int>> bestSolution;

    //make a min heap from it
    // <newObjectiveFunctionValue, <indexOfSwappedNode1, indexOfSwappedNode2>>
    std::priority_queue<std::pair<int, std::pair<int,int>>> priorityQueue;

    while(true) { //it never ends, only stop criteria can stop it
        for (int i = 0; i < matrix->nrV; ++i) {

            if (timer.stopTimer() / 1000000.0 >= stopCriteria) {
                std::cout << "STOP!" << std::endl;
                return;
            }

            x = rand() % (matrix->nrV); //get random number

            while (x == i) { //we should get different number of node than in which we are now
                x = rand() % (matrix->nrV);
            }

            std::swap(solution[i], solution[x]);
            newObjectiveFunction = calculateRoute();

            if (newObjectiveFunction < objectiveFunction) {
                priorityQueue.emplace(newObjectiveFunction,std::make_pair(i, x));
            }

            std::swap(solution[i], solution[x]); //come back to previous solution

        }

        if(!priorityQueue.empty()) {
            bestSolution = priorityQueue.top();

            //update solution and objective function with new best solution
            std::swap(solution[bestSolution.second.first], solution[bestSolution.second.second]);
            objectiveFunction = bestSolution.first;
            numberOfSwaps++;

            printSolution();
            std::cout<<"Swap: "<<solution[bestSolution.second.first]<<" z "<<solution[bestSolution.second.second] <<std::endl;
            std::cout<<"Wykonano swapow: "<<numberOfSwaps<<std::endl;

            while(!priorityQueue.empty()){
                priorityQueue.pop(); //empty the queue
            }
        }

    }

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
//method to generate beginning solution
void TabuSearch::generateBegSolutionRandom(){

    std::vector<bool> visited; //vector helping to generate permutation

    for (int i = 0; i < matrix->nrV; ++i) { //filling the vector
        visited.push_back(false);
    }

    srand(time(NULL)); //initialize the seed
    int x;

    for (int i = 0; i < matrix->nrV; ++i) {
        x = rand()%(matrix->nrV); //get random number

        while(visited[x]){ //if it exists in solution, generate once again
            x = rand()%(matrix->nrV);
        }

        solution.push_back(x);
        visited[x] = true; //we visit every node once

        if(i>0){
            objectiveFunction+=matrix->adjMatrix[solution[i-1]][solution[i]]; //calculate objective function
        }

    }

    objectiveFunction+=matrix->adjMatrix[solution[solution.size()-1]][solution[0]]; //we come back to the beginning node

    printSolution();

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

    printSolution();

}

void TabuSearch::printSolution(){
    for (int i = 0; i < solution.size(); ++i) {
        std::cout << solution[i] << "->";
    }

    std::cout << solution[0];
    std::cout<<std::endl;
    std::cout<<objectiveFunction<<std::endl;

}