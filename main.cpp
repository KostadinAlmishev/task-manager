#include "gtest/gtest.h"

#include <iostream>
#include <string.h>

#include "Display.h"
#include "Gui.h"
#include "Parser.h"
#include "ServiceConnector.h"
#include "Entities.h"


int main(int argc, char *argv[])
{
    std::cout << "Hello world" << std::endl;

    Gui gui;
    gui.runGui();


    return 0;
}