#include <iostream>
#include "FileReader.h"
#include "Matrix.h"
#include "Timer.h"
#include "Menu.h"

int main() {
    int option=0;
    Menu menu;

    while(option!=5){ //menu

        std::cout << std::endl;
        std::cout << "1. Read data from file" << std::endl;
        std::cout << "2. Read stop criteria" << std::endl;
        std::cout << "3. Choose neighbourhood for Tabu Search" << std::endl;
        std::cout << "4. Launch Tabu Search" << std::endl;
        std::cout << "5. Set temperature coefficient for Simulated Annealing" << std::endl;
        std::cout << "6. Launch Simulated Annealing" << std::endl;
        std::cout << "7. Save solution to .txt file" << std::endl;
        std::cout << "8. Read solution path from .txt file and calculate the route" << std::endl;

        std::cin >> option;
        std::cout << std::endl;

        switch (option) {
            case 1:
                menu.option1();
                break;

            case 2:
                menu.option2();
                break;

            case 3:
                menu.option3();
                break;

            case 4:
                menu.option4();
                break;

            case 5:
                menu.option5();
                break;

            case 6:
                menu.option6();
                break;

            case 7:
                menu.option7();
                break;

            case 8:
                menu.option8();
                break;

        }

    }

}

