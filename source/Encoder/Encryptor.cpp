//
// Created by daniil on 11.11.2019.
//

#include "include/Encoder/Encryptor.h"

std::string Encryptor::Execute(std::string input) {
    std::vector<uint8_t > temp;
    for( auto i =0;i<input.size(); i++)
        temp.push_back(input[i]);
    temp = process_bytes(temp, true);
    std::string str;
    str.resize(temp.size());
    for( auto i =0;i<temp.size(); i++)
        str[i]= temp[i];
    return str;
}