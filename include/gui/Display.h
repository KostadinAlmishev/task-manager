#ifndef TASK_MANAGER_DISPLAY_H
#define TASK_MANAGER_DISPLAY_H

#include <iostream>
#include "Request.h"

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
    bool isStrEmpty(std::string str);
    long getLong();
    void printText(std::string body);
    void printError(std::string body);
    void printTask(std::shared_ptr<Task> task);
};



#endif //TASK_MANAGER_DISPLAY_H
