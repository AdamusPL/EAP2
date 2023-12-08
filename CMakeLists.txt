cmake_minimum_required(VERSION 3.25)
project(PEA2)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA2 main.cpp Menu.cpp Menu.h FileReader.cpp FileReader.h Matrix.cpp Matrix.h Timer.cpp Timer.h TabuSearch.cpp TabuSearch.h Cmp.h SimulatedAnnealing.cpp SimulatedAnnealing.h)
