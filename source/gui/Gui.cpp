//
// Created by kotik on 25.11.2019.
//

#include "Gui.h"
#include "Display.h"
#include "ServiceConnector.h"
#include "Response.h"
#include "Request.h"
#include "State.h"

#include <iostream>
#include <string>
#include <memory>


Gui::Gui() {
    parser = std::make_unique<Parser>();
    display = Display::instance();
    serviceConnector = std::make_unique<ServiceConnector>();
    state = std::make_unique<State>();
}

bool Gui::runGui() {
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

std::string Gui::readCommand() const {
    return display->getCommandFromUser();
}

void Gui::sendCommand(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    serviceConnector->sendCommand(request, response);
}

void Gui::modifyRequest(std::shared_ptr<Request> request, std::unique_ptr<State> &state) {
    switch (request->mode) {
        case requestMode::UPDADE:
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

void Gui::readResponse(std::shared_ptr<Response> response, std::unique_ptr<State> &state) {
    if (response->isError) {
        display->printError(response->errorBody);
    }
    else {
        switch (response->code) {
            case responseCode::TASK:
                display->printTask(response->task);
                break;
            case responseCode::USER:
                display->printUser(response->user);
                break;
            case responseCode::PROJECT:

                break;
            case responseCode::SUCCESSFULL_AUTHORIZATION:
                state->authorize(response->user);
                break;

        }
    }
}

void Gui::getInformation(std::shared_ptr<Request> request) {
    switch (request->code) {
        case requestCode::TASK:
            switch (request->mode) {
                case requestMode::UPDADE: {
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
                case requestMode::UPDADE: {
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
                case requestMode::UPDADE: {
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







