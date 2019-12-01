//
// Created by Konstantin Pronin on 29.11.2019.
//

#include <utility>
#include <algorithm>

#include "managers/NotificationManager.h"

NotificationManager::NotificationManager(std::vector<std::shared_ptr<Subscriber>> subscribers) :
    _subscribers(std::move(subscribers)) {}

void NotificationManager::notifyAll(Entity &user, Entity &info) const {
  for (auto &it : _subscribers) {
    it->update(user, info);
  }
}

void NotificationManager::subscribe(Subscriber &subscriber) {
  _subscribers.push_back(std::make_shared<Subscriber>(subscriber));
}

void NotificationManager::unsubscribe(Subscriber &subscriber) {
  _subscribers.erase(std::remove(_subscribers.begin(), _subscribers.end(), subscriber), _subscribers.end());
}
