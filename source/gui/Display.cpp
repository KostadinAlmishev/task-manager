//
// Created by kotik on 25.11.2019.
//

#include "Display.h"
#include <iostream>

Display * Display::p_instance = NULL;

Display::Display() {

}

std::string Display::getCommandFromUser() {
    std::string str;
    std::cout << std::endl << "Enter your command: ";
    std::getline(std::cin, str);
    return str;
}
void Display::printText(std::string body) {
    std::cout << body;
}

void Display::printError(std::string body) {
    std::cout << "Error: " << body << std::endl;
}

void Display::printTask(std::shared_ptr<Task> task) {
    std::cout << "Task \"" << task->getName() << "\"" << std::endl
        << "Description: " << task->getDescription() << std::endl
        << "Id: " << task->getId()
        << "   Creator id: " << task->getCreatorId()
        << "   Project id: " << task->getProjectId() << std::endl;
}



std::string Display::getText() {
    std::string str;
    do {
        getline(std::cin, str);
    } while (!isStrEmpty(str));
    return str;
}

long Display::getLong() {
    long num;
    while (true) {
        try {
            num = std::stol(getText());
            break;
        }
        catch(const std::exception &ex) {
            std::cout << "You must enter an integer: ";
        }
    }
    return num;
}

bool Display::isStrEmpty(std::string str) {
    auto it = str.begin();
    for (; it != str.end(); it++) {
        if (*it != ' ' && *it != '\n') return true;
    }
    return false;
}
