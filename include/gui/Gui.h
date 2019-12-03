//
// Created by kotik on 25.11.2019.
//

#ifndef TASK_MANAGER_GUI_H
#define TASK_MANAGER_GUI_H


#include <iostream>
#include "EntityContainer.h"
#include "Display.h"
#include "Parser.h"
#include "Gui.h"



class Gui {
private:
    Parser * parser;
    Display * display;

    std::string readCommand();
    EntityContainer * parse(std::string);
    bool sendCommand(EntityContainer * entityContainer);
    void printBody(std::string body);
public:
    Gui();
    bool runGui();
};

#endif //TASK_MANAGER_GUI_H
