//
// Created by adamc on 29.11.2023.
//

#include "Menu.h"
#include "FileReader.h"
#include "TabuSearch.h"
#include "SimulatedAnnealing.h"

Menu::Menu(){
    matrix = nullptr;
    stopCriteria = 0;
    a = 0;
    objectiveFunction = 0;
}

void Menu::option1() {
    FileReader fileReader;

    if(matrix != nullptr){ //free memory if previous matrix still exist
        delete matrix;
    }

    matrix = fileReader.read(); //read matrix data from .txt file and change pointer to it
}

void Menu::option2() {
    std::cout<<"Give the stop criteria (in seconds):"<<std::endl;
    std::cin>>stopCriteria;
}

void Menu::option3() {

}

void Menu::option4(){

    if(matrix == nullptr){
        std::cout<<"No data hasn't been read yet"<<std::endl;
        return;
    }

    if(stopCriteria == 0){
        std::cout<<"Stop criteria hasn't been set yet"<<std::endl;
        return;
    }

    TabuSearch tabuSearch = TabuSearch(matrix, stopCriteria);
    timer.startTimer();
    tabuSearch.launch(timer);

    solution = tabuSearch.solution;
    objectiveFunction = tabuSearch.objectiveFunction;
    printSolution();
}

void Menu::option5(){
    std::cout<<"Give the temperature coefficient change (0,1):"<<std::endl;
    std::cin >> a;

    coolingOption = 0;
    std::cout << "1. Geometric cooling" <<std::endl;
    std::cout << "2. Exponential cooling" <<std::endl;
    std::cout << "3. Logaritmic cooling" <<std::endl;

    while(coolingOption!=1 && coolingOption!=2 && coolingOption!=3) {
        std::cin >> coolingOption;
    }
}

void Menu::option6() {
    if(matrix == nullptr){
        std::cout<<"No data hasn't been read yet"<<std::endl;
        return;
    }

    if(stopCriteria == 0){
        std::cout<<"Stop criteria hasn't been set yet"<<std::endl;
        return;
    }

    if(a == 0){
        std::cout<<"Temperature coefficient hasn't been set yet"<<std::endl;
        return;
    }

    SimulatedAnnealing simulatedAnnealing = SimulatedAnnealing(matrix, a, stopCriteria, coolingOption);
    timer.startTimer();
    simulatedAnnealing.launch(timer);

    solution = simulatedAnnealing.solution;
    objectiveFunction = simulatedAnnealing.objectiveFunction;
    printSolution();
}

void Menu::option7() {

    if(solution.empty() || objectiveFunction == 0){
        std::cout << "None of the algorithms has been run yet" << std::endl;
        return;
    }

    std::string filename;
    std::cout << "Give the name of file:" <<std::endl;
    std::cin >> filename;

    std::fstream file;
    file.open(filename, std::ios::out);

    file << matrix->nrV << std::endl; //number of nodes

    for(int i=0; i<solution.size(); i++){
        file << solution[i] << std::endl; //path
    }

    file << solution[0] << std::endl; //cycle
    file.close();

}

void Menu::option8() {

    if(matrix == nullptr){
        std::cout<<"Matrix hasn't been read yet"<<std::endl;
        return;
    }

    std::string filename;
    std::cout << "Give the name of file:" <<std::endl;
    std::cin >> filename;

    std::fstream file;
    file.open(filename, std::ios::in);

    //read data from file
    int numberOfNodes;
    int data;
    file >> numberOfNodes;

    for(int i=0; i < numberOfNodes - 1; i++){
        file >> data;
        solution.push_back(data);
    }

    file.close();

    //calculate route
    for(int i=1; i < matrix->nrV; i++){
        objectiveFunction += matrix->adjMatrix[solution[i-1]][solution[i]];
    }

    objectiveFunction += matrix->adjMatrix[solution[solution.size()-1]][solution[0]];

    Menu::printSolution();

}

void Menu::printSolution(){
    for (int i = 0; i < solution.size(); ++i) {
        std::cout << solution[i] << "->";
    }

    std::cout << solution[0];
    std::cout<<std::endl;
    std::cout<<objectiveFunction<<std::endl;
}