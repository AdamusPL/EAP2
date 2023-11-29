//
// Created by adamc on 29.11.2023.
//

#include "Menu.h"
#include "FileReader.h"

Menu::Menu(){
    matrix = nullptr;
}

void Menu::option1() {
    FileReader fileReader;

    if(matrix != nullptr){ //free memory if previous matrix still exist
        delete matrix;
    }

    matrix = fileReader.read(); //read matrix data from .txt file and change pointer to it
}

void Menu::option2() {

}

void Menu::option3() {

}

void Menu::option4(){

}