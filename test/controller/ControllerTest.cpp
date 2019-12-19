#include "gtest/gtest.h"
#include "controller/Controller.h"

TEST(ControllerTest, TaskGetById) {
    for (int id = -10; id < 10000; id += rand() % 10) {
        Controller controller;
        auto request = std::make_shared<Request>();
        auto response = std::make_shared<Response>();
        request->mode = requestMode::GET;
        request->code = requestCode::TASK;
        request->findBy = requestFindBy::ID;
        request->task = std::make_shared<Task>();
        request->task->setId(id);
        controller.checkRequest(request, response);

        if (!response->isError) {
            EXPECT_EQ(response->mode, responseMode::PRINT);
            EXPECT_EQ(response->code, responseCode::TASK);
            EXPECT_EQ(response->task->getId(), id);
        }
        else {
            EXPECT_EQ(response->errorBody, "there is no task with such ID");
        }
    }
}

TEST(ControllerTest, Save) {
    for (int i = 0; i < 100; i++) {
        Controller controller;
        auto request = std::make_shared<Request>();
        auto response = std::make_shared<Response>();
        request->mode = requestMode::SAVE;
        request->code = requestCode::TASK;
        request->task = std::make_shared<Task>();
        request->task->setCreatorId(0);
        controller.checkRequest(request, response);

        if (response->isError) {
            EXPECT_EQ(response->errorBody, "error while adding task");
        }
    }
}




//TEST(ControllerTest, UpdateById) {
//    TEST(ControllerTest, TaskGetById) {
//        for (int id = -10; id < 100; id++) {
//            Controller controller;
//            auto request = std::make_shared<Request>();
//            auto response = std::make_shared<Response>();
//            request->mode = requestMode::GET;
//            request->code = requestCode::TASK;
//            request->findBy = requestFindBy::ID;
//            request->task = std::make_shared<Task>();
//            request->task->setId(id);
//            controller.checkRequest(request, response);
//
//            if (!response->isError) {
//                EXPECT_EQ(response->mode, responseMode::PRINT);
//                EXPECT_EQ(response->code, responseCode::TASK);
//                EXPECT_EQ(response->task->getId(), id);
//            }
//            else {
//                EXPECT_EQ(response->errorBody, "there is no task with such ID");
//            }
//        }
//    }
//}