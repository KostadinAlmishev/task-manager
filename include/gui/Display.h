#ifndef TASK_MANAGER_DISPLAY_H
#define TASK_MANAGER_DISPLAY_H

#include <iostream>
#include <memory>

#include "entities/Entity.h"
#include "entities/Project.h"
#include "entities/Task.h"
#include "entities/User.h"
#include "stringFunctions/StringFunctions.h"


class Display {
private:
    static Display * p_instance;
    Display();
    Display(const Display& other) = delete;
    Display& operator=(const Display&) = delete;
public:

    static Display * instance() {
        if(!p_instance) {
            p_instance = new Display();
        }
        return p_instance;
    }


    std::string getCommandFromUser();
    std::string getText();
    long getLong();
    void printText(std::string body);
    void printError(std::string body);
    void printTask(std::shared_ptr<Task> task);
    void printUser(std::shared_ptr<User> user);
    void getInformationTaskSave(std::shared_ptr<Task> task);
    void getInformationTaskUpdate(std::shared_ptr<Task> task);
    void getInformationUserSave(std::shared_ptr<User> user);
    void getInformationUserUpdate(std::shared_ptr<User> user);
    void getInformationProjectSave(std::shared_ptr<Project> project);
    void getInformationProjectUpdate(std::shared_ptr<Project> project);
    void getPasswordAndName(std::shared_ptr<User> user);
};



#endif //TASK_MANAGER_DISPLAY_H
