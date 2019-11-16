cmake_minimum_required(VERSION 3.15)
project(task_manager)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(googletest/googletest/include)
include_directories(cmake-build-debug)
include_directories(dev-daniil)
add_subdirectory(dev-daniil)
add_executable(${PROJECT_NAME} main.cpp dev-daniil/Encoder/Decryptor.cpp dev-daniil/Encoder/Decryptor.h
        dev-daniil/Encoder/Decryptor.cpp
        dev-daniil/Encoder/Decryptor.h
        dev-daniil/Encoder/ICrypto.h
        dev-daniil/PasswordEncoder.cpp
        dev-daniil/PasswordEncoder.h
        dev-daniil/IValidator.h
        dev-daniil/Encoder/KeyGen.cpp
        dev-daniil/Encoder/KeyGen.h
        main.cpp
        dev-daniil/Encoder/Key.h dev-daniil/Encoder/Encryptor.cpp dev-daniil/Encoder/Encryptor.h dev-daniil/Encoder/Encoder.h Entity/Entity.cpp Entity/Entity.h dev-daniil/Validator.cpp Entity/User.cpp Entity/User.h Entity/Project.cpp Entity/Project.h Entity/Task.cpp Entity/Task.h)