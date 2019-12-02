//
// Created by kotik on 25.11.2019.
//

#ifndef TASK_MANAGER_GUI_H
#define TASK_MANAGER_GUI_H

//#include "Services.h"

#include <iostream>
#include "EntityContainer.h"

class Gui {
private:
//    Parser * parser;
//    ServiceConnector * serviceConnector;

    std::string readCommand();
    EntityContainer * parse(std::string);
    bool sendCommand(EntityContainer * entityContainer);
    //    methods of getting info from back
public:
    bool runGui();
};

#endif //TASK_MANAGER_GUI_H
