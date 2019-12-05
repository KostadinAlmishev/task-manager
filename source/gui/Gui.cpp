//
// Created by kotik on 25.11.2019.
//

#include "Gui.h"
#include "Display.h"
#include "ServiceConnector.h"
#include "Response.h"
#include "Request.h"

#include <iostream>
#include <string>
#include <memory>


Gui::Gui() {
    parser = std::make_unique<Parser>();
    display = Display::instance();
    serviceConnector = std::make_unique<ServiceConnector>();
}

bool Gui::runGui() {
    while (true) {
        std::string command = readCommand();;
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

        modifyRequest(request);
        auto response = std::make_shared<Response>();
        sendCommand(request, response);
        readResponse(response);
    }

    return true;
}

std::string Gui::readCommand() const {
    return display->getCommandFromUser();
}

void Gui::sendCommand(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    serviceConnector->sendCommand(request, response);
}

void Gui::modifyRequest(std::shared_ptr<Request> request) {
    if (request->mode == requestMode::UPDADE || request->mode == requestMode::SAVE) {
        requestInformation(request);
    }
}

void Gui::readResponse(std::shared_ptr<Response> response) {
    if (response->isError) {
        display->printError(response->errorBody);
    }
    else if (response->code == responseCode::TASK) {
        display->printTask(response->task);
    }
}

void Gui::requestInformation(std::shared_ptr<Request> request) {
    switch (request->code) {
        case requestCode::TASK:
            requestInformationTask(request);
            break;
        case requestCode::PROJECT:
            requestInformationProject(request);
            break;
        case requestCode::USER:
            requestInformationUser(request);
            break;
    }
}

void Gui::requestInformationTask(std::shared_ptr<Request> request) {
    switch (request->mode) {
        case requestMode::SAVE:
            display->printText("Project ID to which task will belong: ");
            request->task->setProjectId(display->getLong());
            display->printText("Name of a task: ");
            request->task->setName(display->getText());
            display->printText("Description: ");
            request->task->setDescription(display->getText());
            break;
        case requestMode::UPDADE:
            display->printText("New name of a task: ");
            request->task->setName(display->getText());
            display->printText("New description: ");
            request->task->setDescription(display->getText());
            break;
    }
}

void Gui::requestInformationUser(std::shared_ptr<Request> request) {
    switch (request->mode) {
        case requestMode::SAVE:

            break;
        case requestMode::UPDADE:

            break;
    }
}

void Gui::requestInformationProject(std::shared_ptr<Request> request) {
    switch (request->mode) {
        case requestMode::SAVE:

            break;
        case requestMode::UPDADE:

            break;
    }
}





