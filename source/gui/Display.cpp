#include <iostream>

#include "gui/Display.h"
#include "entities/Project.h"
#include "entities/Task.h"
#include "entities/User.h"


Display * Display::p_instance = NULL;

Display::Display() {

}

std::string Display::getCommandFromUser() {
    std::string str;
    std::cout << std::endl << "Enter your command: ";
    str = getText();
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

void Display::printUser(std::shared_ptr<User> user) {
    std::cout << "User \"" << user->getName() << "\"" << std::endl
              << "Email: " << user->getEmail() << std::endl
              << "Id: " << user->getId() << std::endl
              << "Status: \"" << user->getStatus() << "\"" << std::endl;
}

std::string Display::getText() {
    std::string str;
    do {
        getline(std::cin, str);
    } while (!StrFunc::isEmpty(str));
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


void Display::getInformationTaskSave(std::shared_ptr<Task> task) {
    printText("Project ID to which task will belong: ");
    task->setProjectId(getLong());
    printText("Name of a task: ");
    task->setName(getText());
    printText("Description: ");
    task->setDescription(getText());
}

void Display::getInformationTaskUpdate(std::shared_ptr<Task> task) {
    printText("New name of a task: ");
    task->setName(getText());
    printText("New description: ");
    task->setDescription(getText());
}

void Display::getInformationUserSave(std::shared_ptr<User> user) {
    printText("User name: ");
    user->setName(getText());
    printText("Email: ");
    user->setEmail(getText());
    printText("Password: ");
    user->setPassword(getText());
    user->setStatus("user");

}

void Display::getInformationUserUpdate(std::shared_ptr<User> user) {
    printText("New password: ");
    user->setPassword(getText());
}

void Display::getInformationProjectSave(std::shared_ptr<Project> project) {

}

void Display::getInformationProjectUpdate(std::shared_ptr<Project> project) {

}

void Display::getPasswordAndName(std::shared_ptr<User> user) {
    printText("\n   Sign in\n");
    printText("User name: ");
    user->setName(getText());
    printText("Password: ");
    std::string str = getText();
    printText("Password again: ");
    if (getText() == str) user->setPassword(str);
    user->setStatus("user");
}


