//
// Created by daniil on 07.12.2019.
//
#include "gtest/gtest.h"

#include "validator/IValidator.h"
#include "encoder/Encoder.h"

TEST(Validator_test, test){
Validator validator;
Encryptor encryptor;
Decryptor decryptor;
KeyGen keyGen(encryptor, decryptor);
auto tmp = encryptor.Execute("test");
EXPECT_TRUE( validator.CheckValidation("test", tmp));
}
