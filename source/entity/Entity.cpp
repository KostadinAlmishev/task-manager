//
// Created by Konstantin Pronin on 01.12.2019.
//

#include <entities/Entity.h>

Entity::Entity(long id) : _id(id) {}

long Entity::getId() const noexcept {
  return _id;
}

void Entity::setId(long id) noexcept {
  _id = id;
}
bool Entity::operator==(const Entity &rhs) const {
  return _id == rhs._id;
}

