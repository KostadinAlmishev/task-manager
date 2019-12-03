//
// Created by kotik on 25.11.2019.
//

#include "Gui.h"
#include "Display.h"
#include <iostream>
#include <string>


Gui::Gui() {
    display = Display::instance(100, 100);
}

bool Gui::runGui() {
    bool isRunning = true;

    while (isRunning) {
        std::string command;
        command = readCommand();
        EntityContainer * entityContainer = parser->parse(command);

        if (entityContainer->isQuit) isRunning = false;
    }

    return true;
}

std::string Gui::readCommand() {
    return display->getCommandFromUser();
}
EntityContainer * Gui::parse(std::string) {
    return nullptr;
}
bool Gui::sendCommand(EntityContainer * entityContainer) {
    return true;
}
void Gui::printBody(std::string body) {
    display->printText(body);
}