//
// Created by daniil on 09.11.2019.
//

#ifndef TASK_MANAGER_KEYGEN_H
#define TASK_MANAGER_KEYGEN_H


#include <stdint-gcc.h>
#include "ICrypto.h"
class KeyGen {
private:
    const uint64_t p = 3557;
    const uint64_t q =  2579;
    int64_t invmod(int64_t a, int64_t m); //обратное по модулю
    int64_t gcdex(int64_t a, int64_t b, int64_t &x, int64_t &y);//расширеный квклид
public:
    KeyGen(ICrypto&, ICrypto&);
};




#endif //TASK_MANAGER_KEYGEN_H
