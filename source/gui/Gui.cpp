#include <iostream>
#include <memory>
#include <string>

#include "gui/Display.h"
#include "gui/Gui.h"
#include "gui/ServiceConnector.h"
#include "gui/State.h"
#include "entities/Response.h"
#include "entities/Request.h"


template <typename TParser, typename TDisplay, typename TServiceConnector, typename TState>
Gui<TParser, TDisplay, TServiceConnector, TState>::Gui() {
    parser = std::make_unique<TParser>();
    display = TDisplay::instance();
    serviceConnector = std::make_unique<TServiceConnector>();
    state = std::make_unique<TState>();
}

template <typename TParser, typename TDisplay, typename TServiceConnector, typename TState>
bool Gui<TParser, TDisplay, TServiceConnector, TState>::runGui() {
    while (true) {
        std::string command = state->isAuthorized() ? readCommand() : "sign-in";
        auto request = std::make_shared<Request>();
        auto parseError = std::make_shared<ParseError>();
        parser->parse(command, request, parseError);
        if (parseError->isQuit) {
            display->printText(parseError->quitBody + "\n");
            break;
        }
        if (parseError->isError) {
            display->printError(parseError->errorBody);
            continue;
        }
        modifyRequest(request, state);
        auto response = std::make_shared<Response>();
        sendCommand(request, response);
        readResponse(response, state);
    }

    return true;
}


template <typename TParser, typename TDisplay, typename TServiceConnector, typename TState>
std::string Gui<TParser, TDisplay, TServiceConnector, TState>::readCommand() const {
    return display->getCommandFromUser();
}

template <typename TParser, typename TDisplay, typename TServiceConnector, typename TState>
void Gui<TParser, TDisplay, TServiceConnector, TState>::sendCommand(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    serviceConnector->sendCommand(request, response);
}

template <typename TParser, typename TDisplay, typename TServiceConnector, typename TState>
void Gui<TParser, TDisplay, TServiceConnector, TState>::modifyRequest(std::shared_ptr<Request> request, std::unique_ptr<TState> &state) {
    switch (request->mode) {
        case requestMode::UPDATE:
            getInformation(request);
            break;
        case requestMode::SAVE:
            getInformation(request);
            break;
        case requestMode::AUTHORIZATION:
            display->getPasswordAndName(request->user);
            break;
    }
}

template <typename TParser, typename TDisplay, typename TServiceConnector, typename TState>
void Gui<TParser, TDisplay, TServiceConnector, TState>::readResponse(std::shared_ptr<Response> response, std::unique_ptr<TState> &state) {
    if (response->isError) {
        display->printError(response->errorBody);
    }
    else {
        switch (response->mode) {
            case responseMode::SUCCESSFULL_AUTHORIZATION:
                state->authorize(response->user);
                break;
            case responseMode::SUCCESSFULL_DEAUTHORIZATION:
                state->deauthorize();
                break;
            case responseMode::PRINT: {
                switch (response->code) {
                    case responseCode::TASK:
                        display->printTask(response->task);
                        break;
                    case responseCode::USER:
                        display->printUser(response->user);
                        break;
                    case responseCode::PROJECT:

                        break;
                }
                break;
            }
        }

    }
}

template <typename TParser, typename TDisplay, typename TServiceConnector, typename TState>
void Gui<TParser, TDisplay, TServiceConnector, TState>::getInformation(std::shared_ptr<Request> request) {
    switch (request->code) {
        case requestCode::TASK:
            switch (request->mode) {
                case requestMode::UPDATE: {
                    display->getInformationTaskUpdate(request->task);
                    break;
                }
                case requestMode::SAVE:
                    display->getInformationTaskSave(request->task);
                    break;
            }
            break;
        case requestCode::PROJECT:
            switch (request->mode) {
                case requestMode::UPDATE: {
                    display->getInformationProjectUpdate(request->project);
                    break;
                }
                case requestMode::SAVE:
                    display->getInformationProjectSave(request->project);
                    break;
            }
            break;
        case requestCode::USER:
            switch (request->mode) {
                case requestMode::UPDATE: {
                    display->getInformationUserUpdate(request->user);
                    break;
                }
                case requestMode::SAVE:
                    display->getInformationUserSave(request->user);
                    break;
            }
            break;
    }
}







