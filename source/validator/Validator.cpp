//
// Created by daniil on 16.11.2019.
//
#include "include/validator/IValidator.h"
#include "Entity/User.h"


bool Validator::CheckValidation(std::string inputPassword,  std::string EncodedPassword) {

        std::string tmp = passwordEncoder.Encode(inputPassword);
        if( inputPassword != passwordEncoder.Decode(tmp)  ) {
            std::cerr << "Not valid Encoder/Decoder, maybe not linked\n";
            return false;
        }



    auto decoded = passwordEncoder.Decode(EncodedPassword);

    return decoded == inputPassword;


}

std::string
Validator::ReinstallPassword(std::string newPassword, std::string inputPassword, std::string EncodedPassword) {
    if( !CheckValidation(inputPassword, EncodedPassword) ) return "";
    return passwordEncoder.Encode(newPassword);
}

