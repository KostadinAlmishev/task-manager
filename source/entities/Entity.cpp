//
// Created by kotik on 03.12.2019.
//

#include "entities/Entity.h"

long Entity::getId() const noexcept {
    return id;
}

void Entity::setId(long id) noexcept {
    this->id = id;
}
