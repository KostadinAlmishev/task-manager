//
// Created by Konstantin Pronin on 07.11.2019.
//
#include <vector>

#include <gtest/gtest.h>

#include "../mocks.h"

TEST(notifier_test, add_subscriber_test) {
  std::vector<Subscriber *> subscribers;
  MockSubscriber subscriber;
  NotificationManager notifier(subscribers);

  notifier.subscribe(subscriber);

  ASSERT_EQ(1, subscribers.size());
}

TEST(notifier_test, delete_subscriber_test) {
  std::vector<Subscriber *> subscribers;
  MockSubscriber subscriber;
  subscribers.push_back(&subscriber);
  NotificationManager notifier(subscribers);

  notifier.unsubscribe(subscriber);

  ASSERT_EQ(0, subscribers.size());
}

TEST(notifier_test, notify_subscribers) {
  std::vector<Subscriber *> subscribers;
  MockSubscriber subscriber;
  MockDbConfig conf;
  MockDbConnector mockConnector(conf);
  MockDbCommand command(&mockConnector);
  Entity entity;
  subscribers.push_back(&subscriber);
  NotificationManager notifier(subscribers);

  notifier.notifyAll(entity, command);

  EXPECT_CALL(subscriber, update(::testing::Eq(entity), ::testing::Eq(command))).Times(1);
}