//
// Created by adamc on 12/12/2023.
//

#include "FileWriter.h"

FileWriter::FileWriter(){
    resultsTime = new double[10];
    resultsTemperature = new double[10];
    resultsE = new double[10];
    resultsRoute = new int[10];
}

FileWriter::~FileWriter(){
    delete []resultsTime;
    delete []resultsTemperature;
    delete []resultsE;
    delete []resultsRoute;
}

void FileWriter::write(std::string type, std::string inputName){

    std::fstream file;
    std::string saveFileName = type+"_"+inputName+".txt";

    file.open(saveFileName, std::ios::out);

    for (int i = 0; i < 10; i++) {
        file << resultsTime[i] << " " << resultsRoute[i] << " " << resultsE[i] << " " << resultsTemperature[i] << std::endl;
    }

    file.close();
}
