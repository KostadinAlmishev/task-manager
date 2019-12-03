//
// Created by kotik on 25.11.2019.
//

#ifndef TASK_MANAGER_DISPLAY_H
#define TASK_MANAGER_DISPLAY_H

#include <iostream>

class Display {
private:
    size_t _width;
    size_t _height;


    static Display * p_instance;

    Display(int width, int height);
    Display(const Display& other) = delete;
    Display& operator=(const Display&) = delete;
public:

    static Display * instance(size_t width, size_t height) {
        if(!p_instance) {
            p_instance = new Display(width, height);
        }
        return p_instance;
    }

    std::string getCommandFromUser();
    void printText(std::string body);
    size_t width() const;
    size_t height() const;
};



#endif //TASK_MANAGER_DISPLAY_H
