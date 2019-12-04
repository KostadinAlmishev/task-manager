//
// Created by daniil on 09.11.2019.
//

#ifndef TASK_MANAGER_PASSWORDENCODER_H
#define TASK_MANAGER_PASSWORDENCODER_H

#include "include/Encoder/Encoder.h"

class IPasswordEncoder{
protected:
    ICrypto *encryptor = new Encryptor();
    ICrypto *decryptor = new Decryptor();
    KeyGen keyGen = KeyGen(*encryptor, *decryptor);
public:
    virtual std::string Decode(std::string) = 0;
    virtual std::string Encode(std::string) = 0;
};
class PasswordEncoder: public IPasswordEncoder{
public:
    virtual std::string Decode(std::string);
    virtual std::string Encode(std::string);
};

#endif //TASK_MANAGER_PASSWORDENCODER_H