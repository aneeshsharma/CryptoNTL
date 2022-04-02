#include "../RSA.h"
#include <NTL/ZZ.h>
#include <iostream>

using namespace std;
using namespace NTL;

int main() {
    RSA* rsa = new RSA(512);

    string message = "hello";

    ZZ encrypted = rsa->encryptPublic(message);

    string decrypted = rsa->decryptPrivate(encrypted);

    tuple<ZZ, ZZ> private_key = rsa->getPrivateKey();

    tuple<ZZ, ZZ> public_key = rsa->getPublicKey();

    cout << "Public key (" << get<0>(public_key) << ", " << get<1>(public_key) << ")" << endl;
    cout << "Private key (" << get<0>(private_key) << ", " << get<1>(private_key) << ")" << endl;

    cout << "Message: " << message << endl;
    cout << "Encrypted: " <<  encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}
