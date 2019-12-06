//
// Created by daniil on 16.11.2019.
//
#include "gtest/gtest.h"
#include "Encoder/Encoder.h"
#include "validator/IValidator.h"
#include "Entity/User.h"
#include "Services/UserService.h"
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
    std::string test = "test";
    KeyGen keyGen=KeyGen(decryptor, encryptor);
    auto tmp = encryptor.Execute(test);

    EXPECT_EQ(test, decryptor.Execute(tmp) );
}


TEST(Validator_test, test){
    Validator validator;
    Encryptor encryptor;
    auto tmp = encryptor.Execute("test");
    EXPECT_TRUE( validator.CheckValidation("test", tmp));
}


TEST(UserService_test, Test_Login_and_test_repeat_login){
    User user = User(0,"test", "test", "test");
    UserService userService;
    EXPECT_TRUE(userService.Login(user, "test").Valid);
    EXPECT_FALSE(userService.Login(user, "test").Valid);

}

TEST(UserService_test, Test_Logout){
    User user = User(0,"test", "test", "test");
    UserService userService;
    EXPECT_FALSE(userService.Logout(user).Valid);
    EXPECT_TRUE(userService.Login(user, "test").Valid);
    EXPECT_TRUE(userService.Logout(user).Valid);
}