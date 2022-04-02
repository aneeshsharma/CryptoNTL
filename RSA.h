#include <NTL/ZZ.h>
#include <cstddef>

using namespace std;
using namespace NTL;

#ifndef __RSA_H_
#define __RSA_H_

class RSA {
    private:
        int bit_length;
        ZZ n, e, d;
    public:
        RSA(int bit_length);
        string encrypt(string message); 
        string decrypt(string encrypted);
    private:
        ZZ encrypt(ZZ message);
        ZZ decrypt(ZZ encrypted);
};

#endif
