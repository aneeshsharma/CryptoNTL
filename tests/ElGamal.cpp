#include "../ElGamal.h"

int main() {
    ElGamal* el = new ElGamal(512);

    string message = "Hello El'Gamal!";

    tuple<ZZ, ZZ> encrypted = el->encrypt(message);

    string decrypted = el->decrypt(encrypted);

    cout << "Message: " << message << endl;
    cout << "Encrypted: c1: " << get<0>(encrypted) << ", c2: " << get<1>(encrypted) << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}
