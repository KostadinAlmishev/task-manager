//
// Created by daniil on 07.12.2019.
//

#include "gtest/gtest.h"
#include "encoder/Encoder.h"

TEST(Encoder_test, key_gen_test){
Decryptor decryptor;
Encryptor encryptor;
KeyGen keyGen = KeyGen(decryptor, encryptor);
EXPECT_EQ(decryptor.GetPublicKey().mod, encryptor.GetPublicKey().mod);
EXPECT_EQ(decryptor.GetPublicKey().exp, encryptor.GetPublicKey().exp);
}

TEST(Encoder_test, test_decode_encode){
Decryptor decryptor = Decryptor();
Encryptor encryptor= Encryptor();
std::string test = "fhdakjkjllk";
KeyGen keyGen=KeyGen(decryptor, encryptor);
auto tmp = encryptor.Execute(test);

EXPECT_EQ(test, decryptor.Execute(tmp) );
}

