//
// Created by adamc on 12/12/2023.
//

#include <fstream>
#include <cstring>
#include <iostream>

class FileWriter {
public:
    FileWriter();
    ~FileWriter();
    double *resultsTime;
    int *resultsRoute;
    void write(std::string, std::string);
};