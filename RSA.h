#include <NTL/ZZ.h>
#include <cstddef>
#include <tuple>
#include <vector>

using namespace std;
using namespace NTL;

#ifndef __RSA_H_
#define __RSA_H_

class RSA {
    private:
        int bitLength;
        ZZ n, e, d;
    public:
        RSA(int bitLength);
        ZZ encryptPublic(string message); 
        string decryptPublic(ZZ encrypted);
        ZZ encryptPrivate(string message); 
        string decryptPrivate(ZZ encrypted);
        tuple<ZZ, ZZ> getPublicKey();
        tuple<ZZ, ZZ> getPrivateKey();
        ZZ sign(string message);
        bool verify(string message, ZZ signature);
    private:
        ZZ encryptPublicZZ(ZZ message);
        ZZ decryptPublicZZ(ZZ encrypted);
        ZZ encryptPrivateZZ(ZZ message);
        ZZ decryptPrivateZZ(ZZ encrypted);
};

#endif
