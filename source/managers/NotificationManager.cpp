//
// Created by Konstantin Pronin on 29.11.2019.
//

#include <utility>
#include <algorithm>
#include <memory>

#include "managers/NotificationManager.h"

NotificationManager::NotificationManager(std::vector<std::shared_ptr<Subscriber>> subscribers) :
    _subscribers(std::move(subscribers)) {}

void NotificationManager::notifyAll(Entity &user, Entity &info) const {
  for (auto &it : _subscribers) {
    it->update(user, info);
  }
}

void NotificationManager::subscribe(std::shared_ptr<Subscriber> subscriber) {
  _subscribers.push_back(subscriber);
}

void NotificationManager::unsubscribe(std::shared_ptr<Subscriber> subscriber) {
  _subscribers.erase(std::remove(_subscribers.begin(), _subscribers.end(), subscriber), _subscribers.end());
}
