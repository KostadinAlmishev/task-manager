////
//// Created by Konstantin Pronin on 07.11.2019.
//
//#include <functional>
//#include <memory>
//
//#include <gtest/gtest.h>
//
//#include "entities/User.h"
//#include "managers/HistoryManager.h"
//#include "../mocks.h"
//
//TEST(history_manager_test, test_push) {
//  std::shared_ptr<Entity> entity = std::make_shared<User>();
//
//  HistoryManager history([](std::shared_ptr<Entity> entity) { entity->setId(1); }, []() { return nullptr; });
//
//  history.push(entity);
//
//  ASSERT_EQ(1, entity->getId());
//}
//
//TEST(history_manager_test, test_pop) {
//  HistoryManager history([](std::shared_ptr<Entity>) {}, []() {
//    User entity;
//    entity.setId(2);
//    return std::make_shared<User>(entity);
//  });
//
//  auto result = history.pop();
//
//  ASSERT_EQ(2, result->getId());
//}