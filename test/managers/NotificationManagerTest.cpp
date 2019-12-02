//
// Created by Konstantin Pronin on 07.11.2019.
//
#include <vector>
#include <memory>

#include <gtest/gtest.h>

#include "../mocks.h"
#include "entity/User.h"

TEST(notifier_test, notify_subscribers) {
  auto *mock = new MockSubscriber();
  std::shared_ptr<Subscriber> subscriber(mock);
  NotificationManager notifier;
  User user, entity;

  notifier.subscribe(subscriber);
  notifier.notifyAll(user, entity);

  EXPECT_CALL(*mock, update(::testing::_, ::testing::_)).Times(1);
  delete mock;
}

TEST(notifier_test, delete_subscriber_test) {
  auto *mock = new MockSubscriber();
  std::shared_ptr<Subscriber> subscriber(mock);
  NotificationManager notifier;
  User user, entity;

  notifier.subscribe(subscriber);
  notifier.unsubscribe(subscriber);
  notifier.notifyAll(user, entity);

  EXPECT_CALL(*mock, update(::testing::_, ::testing::_)).Times(0);
  delete mock;
}
