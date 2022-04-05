#include "../ECC.h"

int main() {
    ECC* ecc = new ECC(NIST192);
    
    string message = "Hello ECC";

    auto encrypted = ecc->encrypt(message);

    string decrypted = ecc->decrypt(encrypted);

    cout << "Message: " << message << endl;

    cout << "Decrypted: " << decrypted << endl;
}
