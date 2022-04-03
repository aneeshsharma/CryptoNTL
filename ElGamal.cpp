#include "ElGamal.h"
#include "util.h"
#include <NTL/ZZ.h>
#include <tuple>

ElGamal::ElGamal(int bitLength) {
    GenGermainPrime(q, bitLength);
    p = 2 * q + 1;

    g = 1;
    
    ZZ h;

    while (g == 1) {
        h = RandomBnd(p);
        g = PowerMod(h, (p - 1) / q, p);
    }

    do {
        x = RandomBnd(q);
    } while (GCD(x, p) != 1);

    y = PowerMod(g, x, p);
}

tuple<ZZ, ZZ> ElGamal::encryptZZ(ZZ message) {
    ZZ k;
    do {
        k = RandomBnd(q);
    } while (GCD(k, p) != 1);

    ZZ c1, c2;

    c1 = PowerMod(g, k, p);
    c2 = MulMod(message, PowerMod(y, k, p), p);

    return {c1, c2};
}

ZZ ElGamal::decryptZZ(tuple<ZZ, ZZ> encrypted) {
    ZZ c1 = get<0>(encrypted);
    ZZ c2 = get<1>(encrypted);

    return MulMod(c2, PowerMod(c1, -x, p), p);
}

tuple<ZZ, ZZ> ElGamal::encrypt(string message) {
    ZZ messageAsZZ = encodeToZZ(message);

    return encryptZZ(messageAsZZ);
}

string ElGamal::decrypt(tuple<ZZ, ZZ> encrypted) {
    ZZ messageAsZZ = decryptZZ(encrypted);

    return decodeFromZZ(messageAsZZ);
}

tuple<ZZ, ZZ, ZZ, ZZ> ElGamal::getEncryptionKey() {
    return {p, q, g, y};
}

tuple<ZZ, ZZ, ZZ, ZZ> ElGamal::getDecryptionKey() {
    return {p, q, g, x};
}
