//
// Created by adamc on 29.11.2023.
//

#include "Menu.h"
#include "FileReader.h"
#include "TabuSearch.h"

Menu::Menu(){
    matrix = nullptr;
    stopCriteria = 0;
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
}