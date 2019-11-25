//
// Created by kotik on 25.11.2019.
//

#include "Display.h"


Display * Display::p_instance = NULL;

Display::Display(int width, int height) {
    _width = width;
    _height = height;
}
std::string Display::getCommandFromUser() {
    std::string str = "some text from user";
    return str;
}
void Display::printText(std::string body) {
    std::cout << body;
}
size_t Display::width() const {
    return _width;
}
size_t Display::height() const {
    return _height;
}