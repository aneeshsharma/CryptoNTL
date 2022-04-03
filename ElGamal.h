#include <NTL/ZZ.h>
#include <cstddef>
#include <tuple>
#include <vector>

using namespace std;
using namespace NTL;

#ifndef __ELGAMAL_H_
#define __ELGAMAL_H_

class ElGamal {
    private:
        int bitLength;
        ZZ p, q, g, x, y;
    public:
        ElGamal(int bitLength);
        tuple<ZZ, ZZ> encrypt(string message); 
        string decrypt(tuple<ZZ, ZZ> encrypted);
        tuple<ZZ, ZZ, ZZ, ZZ> getEncryptionKey();
        tuple<ZZ, ZZ, ZZ, ZZ> getDecryptionKey();
    private:
        tuple<ZZ, ZZ> encryptZZ(ZZ message);
        ZZ decryptZZ(tuple<ZZ, ZZ> encrypted);
};

#endif
