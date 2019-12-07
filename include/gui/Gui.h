//
// Created by kotik on 25.11.2019.
//

#ifndef TASK_MANAGER_GUI_H
#define TASK_MANAGER_GUI_H

#include <memory>
#include <iostream>

#include "entities/Request.h"
#include "entities/Response.h"
#include "gui/Display.h"
#include "gui/Parser.h"
#include "gui/Gui.h"
#include "gui/ServiceConnector.h"
#include "gui/State.h"


class Gui {
private:
    std::unique_ptr<Parser> parser;
    Display * display;
    std::unique_ptr<ServiceConnector> serviceConnector;
    std::unique_ptr<State> state;

    std::string readCommand() const;
    void sendCommand(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
    void modifyRequest(std::shared_ptr<Request> request, std::unique_ptr<State> &state);
    void readResponse(std::shared_ptr<Response> response, std::unique_ptr<State> &state);
    void getInformation(std::shared_ptr<Request> request);
public:
    Gui();
    bool runGui();
};

#endif //TASK_MANAGER_GUI_H
