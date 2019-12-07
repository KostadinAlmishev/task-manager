//
// Created by daniil on 09.11.2019.
//

#ifndef TASK_MANAGER_ICRYPTO_H
#define TASK_MANAGER_ICRYPTO_H

#include "Key.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <climits>
#include <stack>
#include <random>


//decrypt  encrypt interface
class ICrypto {
protected:
    Key publicKey;
    Key privateKey;

    std::vector<uint64_t> resize(const std::vector<uint64_t> &data, uint8_t in_size, uint8_t out_size);
    uint64_t sqr(uint64_t x) { return x * x; }
    uint64_t binpow(uint64_t a, uint64_t e, uint64_t mod = LLONG_MAX);
    std::vector<uint8_t> process_bytes(std::vector<uint8_t> data, bool encrypt);
    uint8_t get_chunk_size(Key k) { return 32 - __builtin_clz(k.mod);}
public:

    virtual Key GetPublicKey() = 0;
    virtual std::string Execute(std::string) = 0;


friend class KeyGen;
};


#endif //TASK_MANAGER_ICRYPTO_H
