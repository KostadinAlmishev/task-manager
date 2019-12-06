//
// Created by daniil on 09.11.2019.
//

#include "include/Encoder/KeyGen.h"

KeyGen::KeyGen(ICrypto & left, ICrypto & right) {
    uint64_t  phi = (p-1)*(q-1);
    uint64_t n = p*q;
    uint64_t e=   65537;
    uint64_t d = invmod(e, phi);

    left.publicKey = Key(e, n );
    left.privateKey = Key( d, n);

    right.publicKey = Key(e, n );
    right.privateKey = Key( d, n);
}

int64_t KeyGen::invmod(int64_t a, int64_t m) {
    int64_t x, y;
    gcdex(a, m, x, y);
    x = (x % m + m) % m;
    return x;
}

int64_t KeyGen::gcdex(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int64_t x1, y1;
    int64_t d = gcdex(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
