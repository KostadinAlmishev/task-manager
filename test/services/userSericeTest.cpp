//
// Created by daniil on 07.12.2019.
//

#include "gtest/gtest.h"
#include "entities/User.h"
#include "services/UserService.h"
#include <random>
#include <time.h>
std::string GenRandomString( int length){
    srand(time(0));
    std::string str;
    str.resize(length);
    for(int i = 0 ; i < length; i++)
        str[i] = rand()%90+65;
    return str;
}

TEST(UserService_test, Test_Login_and_test_repeat_login){
User user;
PasswordEncoder passwordEncoder;
auto randStr=  GenRandomString(50);
user.setName(randStr);
user.setPassword(passwordEncoder.Encode(randStr));
UserService userService;
EXPECT_TRUE(userService.Login(user, randStr).Valid);
EXPECT_FALSE(userService.Login(user, randStr).Valid);

}

TEST(UserService_test, Test_Logout){
    auto randStr=  GenRandomString(50);
    User user;
    PasswordEncoder passwordEncoder;
    user.setName(randStr);
    user.setPassword(passwordEncoder.Encode(randStr));
    UserService userService;
EXPECT_FALSE(userService.Logout(user).Valid);
EXPECT_TRUE(userService.Login(user, randStr).Valid);
EXPECT_TRUE(userService.Logout(user).Valid);
}

TEST(UserService_test, Test_set_new_password){
    User user;
    user.setName("test");
    auto randStr=  GenRandomString(50);
    UserService userService;
   
    EXPECT_TRUE(userService.SetNewUserPassword(user, randStr).Valid);
    EXPECT_TRUE(userService.Login(user, randStr).Valid);
}

TEST(UserService_test, Test_change_password){
    User user;
    user.setName("test");
    auto randStr=  GenRandomString(50);
    UserService userService;
    EXPECT_TRUE(userService.SetNewUserPassword(user, randStr).Valid);
    EXPECT_TRUE(userService.ChangePassword(user, randStr, "test").Valid);
}

TEST(UserService_test, Test_privileges){
    User userA, userU;
    userA.setStatus("admin");
    userU.setStatus("user");
    userA.setName("admin");
    userU.setName("user");
    auto tmp1 = GenRandomString(50);
    auto tmp2 = GenRandomString(50);
    UserService userService;
    EXPECT_TRUE( userService.SetNewUserPassword(userA, tmp1).Valid);
    EXPECT_TRUE(userService.SetNewUserPassword(userU, tmp2).Valid);
    EXPECT_TRUE(userService.Login(userA, tmp1).Valid);
    EXPECT_TRUE(userService.Login(userU, tmp2).Valid);
    EXPECT_TRUE(userService.CheckPriveleges(userA, "testAdmin1").Valid);
    EXPECT_TRUE(userService.CheckPriveleges(userA, "testAdmin2").Valid);
    EXPECT_TRUE(userService.CheckPriveleges(userU, "testUser1").Valid);
    EXPECT_TRUE(userService.CheckPriveleges(userU, "testUser1").Valid);
    EXPECT_FALSE(userService.CheckPriveleges(userU, "testAdmin1").Valid);
    EXPECT_FALSE(userService.CheckPriveleges(userU, "testAdmin2").Valid);
}