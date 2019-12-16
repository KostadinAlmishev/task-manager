//
// Created by daniil on 11.12.2019.
//

#ifndef TASK_MANAGER_REQUEST_H
#define TASK_MANAGER_REQUEST_H

enum class requestMode {
    _EMPTY,
    SAVE,
    UPDATE,
    DELETE,
    GET,
    AUTHORIZATION,
    DEAUTHORIZATION,
};

enum class requestCode {
    _EMPTY,
    TASK,
    PROJECT,
    USER,
};

enum class requestFindBy {
    _EMPTY,
    ID,
    NAME,
};

#endif //TASK_MANAGER_REQUEST_H
