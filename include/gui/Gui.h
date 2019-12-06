//
// Created by kotik on 25.11.2019.
//

#ifndef TASK_MANAGER_GUI_H
#define TASK_MANAGER_GUI_H

#include <memory>
#include <iostream>

#include "Request.h"
#include "Response.h"
#include "Display.h"
#include "Parser.h"
#include "Gui.h"
#include "ServiceConnector.h"
#include "State.h"


class Gui {
private:
    std::unique_ptr<Parser> parser;
    Display * display;
    std::unique_ptr<ServiceConnector> serviceConnector;
    std::unique_ptr<State> state;

    std::string readCommand() const;
    void sendCommand(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
    void modifyRequest(std::shared_ptr<Request> request);
    void readResponse(std::shared_ptr<Response> response);
    void getInformation(std::shared_ptr<Request> request);
public:
    Gui();
    bool runGui();
};

#endif //TASK_MANAGER_GUI_H
