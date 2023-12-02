//
// Created by adamc on 29.11.2023.
//

#include "TabuSearch.h"
#include <random>

TabuSearch::TabuSearch(Matrix* matrix){
    this->matrix=matrix;
}

void TabuSearch::launch(){

    //1. Choose beginning solution x_0
    std::vector<std::pair<bool, int>> visited = generateBegSolution();

    //2. 

}

//method to generate beginning solution
std::vector<std::pair<bool, int>> TabuSearch::generateBegSolution(){

    std::vector<std::pair<bool, int>> visited; //vector to help to decide

    for (int i = 0; i < matrix->nrV; ++i) { //filling the vector
        visited.push_back(std::make_pair(false,i));
    }

    srand(time(NULL)); //initialize the seed
    int x;

    for (int i = 0; i < matrix->nrV; ++i) {
        x = rand()%(matrix->nrV); //get random number

        while(visited[x].first){ //if it exists in solution, generate once again
            x = rand()%(matrix->nrV);
        }

        solution.push_back(x);
        visited[x].first = true; //we visit every node once

    }

    for (int i = 0; i < solution.size(); ++i) {
        std::cout << solution[i] << "->";
    }

    std::cout << solution[0];
    std::cout<<std::endl;

}