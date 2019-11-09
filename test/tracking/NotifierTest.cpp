//
// Created by Konstantin Pronin on 07.11.2019.
//
#include <vector>

#include <gtest/gtest.h>

#include "../mocks.h"

TEST(notifier_test, add_subscriber_test) {
  std::vector<Subscriber *> subscribers;
  MockSubscriber subscriber;
  Notifier notifier(subscribers);

  notifier.subscribe(subscriber);

  ASSERT_EQ(1, subscribers.size());
}

TEST(notifier_test, delete_subscriber_test) {
  std::vector<Subscriber *> subscribers;
  MockSubscriber subscriber;
  subscribers.push_back(&subscriber);
  Notifier notifier(subscribers);

  notifier.unsubscribe(subscriber);

  ASSERT_EQ(0, subscribers.size());
}

TEST(notifier_test, notify_subscribers) {
  std::vector<Subscriber *> subscribers;
  MockSubscriber subscriber;
  MockDbConfig conf;
  MockDbCommand command(DbConnector::getInstance(conf));
  MockEntity entity;
  subscribers.push_back(&subscriber);
  Notifier notifier(subscribers);

  notifier.notifyAll(entity, command);

  EXPECT_CALL(subscriber, update(entity, command)).Times(1);
}