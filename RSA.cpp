#include "RSA.h"
#include "util.h"
#include <NTL/ZZ.h>
#include <cstdlib>

RSA::RSA(int bit_length) {
    this->bitLength = bit_length;

    ZZ p, q, n, tot_n;

    RandomPrime(p, bit_length/2);
    RandomPrime(q, bit_length/2);

    mul(n, p, q);
    mul(tot_n, p - 1, q - 1);

    // private and public key components
    ZZ e, d;

    do {
        RandomBits(e, bit_length);
    } while (GCD(e, tot_n) != 1);

    InvMod(d, e, tot_n);

    this->e = e;
    this->d = d;
    this->n = n;
}

tuple<ZZ, ZZ> RSA::getPrivateKey() {
    return {d, n};
}

tuple<ZZ, ZZ> RSA::getPublicKey() {
    return {e, n};
}

ZZ RSA::encryptPublicZZ (ZZ message) {
    ZZ result = PowerMod(message, e, n); return result;
}

ZZ RSA::decryptPublicZZ (ZZ encrypted) {
    ZZ result = PowerMod(encrypted, e, n);
    return result;
}

ZZ RSA::encryptPrivateZZ (ZZ message) {
    ZZ result = PowerMod(message, d, n);
    return result;
}

ZZ RSA::decryptPrivateZZ (ZZ encrypted) {
    ZZ result = PowerMod(encrypted, d, n);
    return result;
}

ZZ RSA::encryptPublic(string message) {
    ZZ messageAsZZ = encodeToZZ(message);

    ZZ encrypted = encryptPublicZZ(messageAsZZ);

    return encrypted;
}

string RSA::decryptPrivate(ZZ encrypted) {
    ZZ messageAsZZ = decryptPrivateZZ(encrypted);

    string message = decodeFromZZ(messageAsZZ);

    return message;
}

ZZ RSA::encryptPrivate(string message) {
    ZZ messageAsZZ = encodeToZZ(message);

    ZZ encrypted = encryptPrivateZZ(messageAsZZ);

    return encrypted;
}

string RSA::decryptPublic(ZZ encrypted) {
    ZZ messageAsZZ = decryptPublicZZ(encrypted);

    string message = decodeFromZZ(messageAsZZ);

    return message;
}

ZZ RSA::sign(string message) {
    string h = hashString(message);
    return encryptPrivate(h);
}

bool RSA::verify(string message, ZZ signature) {
    string h = hashString(message);
    
    string recved_h = decryptPublic(signature);

    return h == recved_h;
}
