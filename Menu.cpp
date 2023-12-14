//
// Created by adamc on 29.11.2023.
//

#include "Menu.h"
#include "FileReader.h"
#include "TabuSearch.h"
#include "SimulatedAnnealing.h"
#include "FileWriter.h"

Menu::Menu(){
    matrix = nullptr;
    stopCriteria = 0;
    a = 0;
    objectiveFunction = 0;
}

void Menu::option1() {

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

    TabuSearch* tabuSearch = new TabuSearch(matrix, stopCriteria);
    timer.startTimer();
    tabuSearch->launch(timer);

    solution = tabuSearch->solution;
    objectiveFunction = tabuSearch->objectiveFunction;
    printSolution();
    delete tabuSearch;
}

void Menu::option5(){
    std::cout<<"Give the temperature coefficient change (0,1):"<<std::endl;
    std::cin >> a;
}


void Menu::option6() {

    if(stopCriteria == 0){
        std::cout<<"Stop criteria hasn't been set yet"<<std::endl;
        return;
    }

    if(a == 0){
        std::cout<<"Temperature coefficient hasn't been set yet"<<std::endl;
        return;
    }

    int methodT = 3;
    std::cout << "1. Manual tests" << std::endl;
    std::cout << "2. Automatic tests" << std::endl;
    std::cin>>methodT;

    if(methodT == 1){
        manualTests();
    }

    else if(methodT == 2){
        automaticTests();
    }

}

void Menu::manualTests(){
    if(matrix == nullptr){
        std::cout<<"No data hasn't been read yet"<<std::endl;
        return;
    }

    SimulatedAnnealing* simulatedAnnealing = new SimulatedAnnealing(matrix, a, stopCriteria);
    timer.startTimer();
    simulatedAnnealing->launch(timer);

    solution = simulatedAnnealing->bestSolution;
    objectiveFunction = simulatedAnnealing->bestObjectiveFunction;
    printSolution();

    std::cout << "Exp(-1/T_k) = "<< exp(-1/simulatedAnnealing->T_k) << std::endl;
    std::cout << "T_k = "<< simulatedAnnealing->T_k << std::endl;
    std::cout << "Solution found in: " << simulatedAnnealing->whenFound << std::endl;

    delete simulatedAnnealing;
}

void Menu::automaticTests(){

    FileWriter* fileWriter = new FileWriter();

    for(int i=0; i<10; i++){
        SimulatedAnnealing* simulatedAnnealing = new SimulatedAnnealing(matrix, a, stopCriteria);
        timer.startTimer();
        simulatedAnnealing->launch(timer);

        simulatedAnnealing->printSolution();
        std::cout << "Exp(-1/T_k) = "<< exp(-1/simulatedAnnealing->T_k) << std::endl;
        std::cout << "T_k = "<< simulatedAnnealing->T_k << std::endl;

        fileWriter->resultsTime[i] = simulatedAnnealing->whenFound;
        fileWriter->resultsRoute[i] = simulatedAnnealing->bestObjectiveFunction;

        delete simulatedAnnealing;
    }

    std::string graph; //f.e. ftv55
    int i=0;
    while(fileReader.filename[i]!='.'){
        graph+=fileReader.filename[i];
        i++;
    }

    fileWriter->write("SA", graph);

    delete fileWriter;

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
        file << solution[i] << " "; //path
    }

    file << solution[0] << std::endl; //cycle
    file.close();

}

void Menu::option8() {
    if(!solution.empty()){
        solution.clear();
        objectiveFunction = 0;
    }

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