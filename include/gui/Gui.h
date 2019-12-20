//
// Created by kotik on 25.11.2019.
//

#ifndef TASK_MANAGER_GUI_H
#define TASK_MANAGER_GUI_H

#include <iostream>
#include <memory>

#include "entities/Request.h"
#include "entities/Response.h"
#include "gui/Display.h"
#include "gui/Gui.h"
#include "gui/Parser.h"
#include "gui/ServiceConnector.h"
#include "gui/State.h"

template <typename TParser = Parser, typename TDisplay = Display, typename TServiceConnector = ServiceConnector, typename TState = State>
class Gui {
private:
    std::unique_ptr<TParser> parser;
    TDisplay * display;
    std::unique_ptr<TServiceConnector> serviceConnector;
    std::unique_ptr<TState> state;

    std::string readCommand() const;
    void sendCommand(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
    void modifyRequest(std::shared_ptr<Request> request, std::unique_ptr<TState> &state);
    void readResponse(std::shared_ptr<Response> response, std::unique_ptr<TState> &state);
    void getInformation(std::shared_ptr<Request> request);
public:
    Gui();
    bool runGui();
};

#endif //TASK_MANAGER_GUI_H
