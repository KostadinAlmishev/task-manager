//
// Created by daniil on 09.11.2019.
//

#include "include/Encoder/Decryptor.h"
std::string Decryptor::Execute(std::string input){
    std::vector<uint8_t > temp;
    for( auto i =0;input[i]!='\0'; i++)
        temp.push_back(input[i]);
    temp = this->process_bytes(temp, false);
    std::string str;
    str.resize(temp.size()-1);
    for( auto i =0;i<str.size(); i++)
        str[i]= temp[i];
    return str;
}