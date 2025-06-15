#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include "gameObject.h"
#include "gameObjectFactory.h"
#include "unit.h"
#include "view.h"
#include "controller.h"
#include "AnsiPrint.h"
#include "environment.h"
/**
 * Print my id
 * */
void
PrintMyID(std::string studId) {

    std::string str = "ID: " + studId;
    std::cout << AnsiPrint(str.c_str(),YELLOW,RED, true, true) << std::endl << std::endl;
}



int main(){
    // TODO 
    // Integrate the Simple MVC Pattern to run the program.
    srand(time(0));
    View win;
    Controller window(win);
    //window.update(new Block(5, 5, Vec2(-1, -1), 1, 1, BLUE, "a", "Stone"));
    window.run();

    // TODO
    // change to your student ID.
    PrintMyID("113703024");
}
