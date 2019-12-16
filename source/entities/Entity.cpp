//
// Created by daniil on 16.11.2019.
//



#include "entities/Entity.h"

long Entity::getId() const noexcept {
    return id;
}

void Entity::setId(long id) noexcept {
    this->id = id;
}
